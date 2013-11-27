#include <World.hpp>
#include <Foreach.hpp>
#include <SpriteNode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>


World::World(sf::RenderWindow& window, FontHolder& fonts)
: window_(window)
, fonts_(fonts)
, worldView_(window.getDefaultView())
, textures_()
, sceneGraph_()
, sceneLayers_()
, worldBounds_(0.f, 0.f, worldView_.getSize().x - 200, worldView_.getSize().y) // - 200 to account for the GUI
, minionSpawnPoints_()
, activeMinions_()
, timeSinceLastSpawn_(sf::seconds(0.0f))
{
	loadTextures();
	buildScene();

	// Prepare the view
	worldView_.setCenter( worldView_.getSize().x / 2.f, worldView_.getSize().y / 2.f);
}

void World::update(sf::Time dt)
{
	// Setup commands to destroy entities
	destroyEntitiesOutsideView();

	// Forward commands to scene graph
	while (!commandQueue_.isEmpty())
		sceneGraph_.onCommand(commandQueue_.pop(), dt);

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Remove all destroyed entities, create new ones
	sceneGraph_.removeNodes();
	spawnMinions(dt);

	// Regular update step
	sceneGraph_.update(dt, commandQueue_);
}

void World::draw()
{
	window_.setView(worldView_);
	window_.draw(sceneGraph_);
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue_;
}

void World::loadTextures()
{
   	textures_.load(Textures::Background,		"Media/Textures/EmptyGrid_32x24_Black.png");

   	textures_.load(Textures::Minion01,          "Media/Textures/Minion01.png");
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
	sceneGraph_.checkSceneCollision(sceneGraph_, collisionPairs);

/*
	FOREACH(SceneNode::Pair pair, collisionPairs)
	{
	     matchesCategories(pair, type1, type2);
	}
*/
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Field) ? Category::SceneFieldLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		sceneLayers_[i] = layer.get();

		sceneGraph_.attachChild(std::move(layer));
	}

	// Prepare the background
	sf::Texture& texture = textures_.get(Textures::Background);
	sf::IntRect textureRect(worldBounds_);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
	sceneLayers_[Background]->attachChild(std::move(backgroundSprite));

	// Add enemy aircraft
	addMinions();
}

void World::addMinions()
{
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
    addMinion(Minion::Standard,  -50,  (31.f*3.0)-13.0 );
}

void World::addMinion(Minion::Type type, float x, float y)
{
	SpawnPoint spawn(type, x, y);
	minionSpawnPoints_.push_back(spawn);
}

void World::spawnMinions(sf::Time dt)
{
    timeSinceLastSpawn_ += dt;
    if( timeSinceLastSpawn_ >= sf::seconds(1.0f) && !minionSpawnPoints_.empty() )
    {
		SpawnPoint spawn = minionSpawnPoints_.back();

		std::unique_ptr<Minion> minion(new Minion(spawn.type, textures_, fonts_));
		minion->setPosition(spawn.x, spawn.y);

		sceneLayers_[Field]->attachChild(std::move(minion));

		// Enemy is spawned, remove from the list to spawn
		minionSpawnPoints_.pop_back();
		timeSinceLastSpawn_ = sf::seconds(0.0f);
    }
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

	commandQueue_.push(command);
	*/
}

sf::FloatRect World::getViewBounds() const
{
	return worldBounds_;
}

sf::FloatRect World::getBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = getViewBounds();
	printf("Top: %g Height: %g Left: %g Width: %g\n",bounds.top, bounds.height, bounds.left, bounds.width);
	bounds.top -= 100.f;
	bounds.height += 100.f;
	bounds.left -= 100.f;
	bounds.width += 100.f;

	return bounds;
}
