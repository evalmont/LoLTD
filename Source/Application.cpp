#include <Application.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <StateIdentifiers.hpp>
#include <GameState.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: window_(sf::VideoMode(1024, 768), "LoLTD", sf::Style::Close)
, textures_()
, fonts_()
, stateStack_(State::Context(window_, textures_, fonts_))
, statisticsText_()
, statisticsUpdateTime_()
, statisticsNumFrames_(0)
{
	window_.setKeyRepeatEnabled(false);

    fonts_.load(Fonts::Main, 	"Media/Sansation.ttf");

	textures_.load(Textures::ButtonNormal,		"Media/Textures/ButtonNormal.png");
	textures_.load(Textures::ButtonSelected,	"Media/Textures/ButtonSelected.png");
	textures_.load(Textures::ButtonPressed,		"Media/Textures/ButtonPressed.png");

	statisticsText_.setFont(fonts_.get(Fonts::Main));
	statisticsText_.setPosition(5.f, 5.f);
	statisticsText_.setCharacterSize(10u);

	registerStates();
	stateStack_.pushState(States::Game);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		stateStack_.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window_.close();
	}
}

void Application::update(sf::Time dt)
{
    stateStack_.update(dt);
}

void Application::render()
{
	window_.clear();

	stateStack_.draw();
	window_.setView(window_.getDefaultView());
	window_.draw(statisticsText_);

	window_.display();
}

void Application::updateStatistics(sf::Time dt)
{
	statisticsUpdateTime_ += dt;
	statisticsNumFrames_ += 1;
	if (statisticsUpdateTime_ >= sf::seconds(1.0f))
	{
		statisticsText_.setString("FPS: " + toString(statisticsNumFrames_));

		statisticsUpdateTime_ -= sf::seconds(1.0f);
		statisticsNumFrames_ = 0;
	}
}

void Application::registerStates()
{
	stateStack_.registerState<GameState>(States::Game);
}
