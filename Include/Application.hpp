#ifndef BOOK_APPLICATION_HPP
#define BOOK_APPLICATION_HPP

#include <World.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class Application
{
	public:
								Application();
		void					run();


	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		window_;
		TextureHolder			textures_;
		FontHolder				fonts_;

        StateStack				stateStack_;

		sf::Text				statisticsText_;
		sf::Time				statisticsUpdateTime_;
		std::size_t				statisticsNumFrames_;
};

#endif // BOOK_APPLICATION_HPP
