#include <World.hpp>
#include <Foreach.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>


World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mFonts(fonts)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mEnemySpawnPoints()
, mActiveEnemies()
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f);
}

void World::update(sf::Time dt)
{
	// Setup commands to destroy entities
	destroyEntitiesOutsideView();

	// Forward commands to scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Remove all destroyed entities, create new ones
	mSceneGraph.removeNodes();
	spawnEnemies();

	// Regular update step
	mSceneGraph.update(dt, mCommandQueue);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    /*
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
	*/

	return false;
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	FOREACH(SceneNode::Pair pair, collisionPairs)
	{
	    // matchesCategories(pair, type1, type2);
	}
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Field) ? Category::SceneFieldLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	//sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);

	// Add the background sprite to the scene
	//std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	//backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	//mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}

void World::addEnemies()
{
}

void World::addEnemy(Minion::Type type, float x, float y)
{
	SpawnPoint spawn(type, x, y);
	mEnemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
    /*
	// Spawn all enemies entering the view area (including distance) this frame
	while ( !mEnemySpawnPoints.empty() )
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();

		std::unique_ptr<Minion> enemy(new Minion(spawn.type, mTextures, mFonts));
		//enemy->setPosition(spawn.x, spawn.y);

		mSceneLayers[Field]->attachChild(std::move(enemy));

		// Enemy is spawned, remove from the list to spawn
		mEnemySpawnPoints.pop_back();
	}
	*/
}

void World::destroyEntitiesOutsideView()
{
    /*
	Command command;
	command.category = Category::Minion;
	command.action = derivedAction<SceneNode>([this] (SceneNode& sN, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(sN.getBoundingRect()))
			sN.destroy();
	});

	mCommandQueue.push(command);
	*/
}

sf::FloatRect World::getViewBounds() const
{
	return mWorldBounds;
}

sf::FloatRect World::getBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;
	bounds.left -= 100.f;
	bounds.width += 100.f;

	return bounds;
}
