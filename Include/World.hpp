#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Minion.hpp>
#include <SceneNode.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
	public:
		explicit							World(sf::RenderWindow& window, FontHolder& fonts);
		void								update(sf::Time dt);
		void								draw();

		CommandQueue&						getCommandQueue();

	private:
		void								loadTextures();
		void								handleCollisions();

		void								buildScene();
		void								addMinions();
		void								addMinion(Minion::Type type, float relX, float relY);
		void								spawnMinions();
		void                                destroyEntitiesOutsideView();
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;


	private:
		enum Layer
		{
			Background,
			Field,
			LayerCount
		};

		struct SpawnPoint
		{
			SpawnPoint(Minion::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			Minion::Type type;
			float x;
			float y;
		};


	private:
		sf::RenderWindow&					window_;
		sf::View							worldView_;
		TextureHolder						textures_;
		FontHolder&							fonts_;

		SceneNode							sceneGraph_;
		std::array<SceneNode*, LayerCount>	sceneLayers_;
		CommandQueue						commandQueue_;

		sf::FloatRect						worldBounds_;

		std::vector<SpawnPoint>				minionSpawnPoints_;
		std::vector<Minion*>				activeMinions_;
};

#endif // BOOK_WORLD_HPP
