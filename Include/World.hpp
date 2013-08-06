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
		void								addEnemies();
		void								addEnemy(Minion::Type type, float relX, float relY);
		void								spawnEnemies();
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;


	private:
		enum Layer
		{
			Background,
			Feild,
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
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		FontHolder&							mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;

		std::vector<SpawnPoint>				mEnemySpawnPoints;
		std::vector<Minion*>				mActiveEnemies;
};

#endif // BOOK_WORLD_HPP
