#include <Minion.hpp>
#include <DataTables.hpp>
#include <Utility.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<MinionData> Table = initializeMinionData();
}

Minion::Minion(Type type, const TextureHolder& textures, const FontHolder& fonts)
: SceneNode(Category::Minion)
, type_(type)
, isMarkedForRemoval_(false)
, sprite_(textures.get(Table[type].texture))
, hitpoints_(Table[type].hitpoints)
, travelledDistance_(0.f)
, directionIndex_(0)
{
	centerOrigin(sprite_);

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	healthDisplay_ = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	updateTexts();
}

void Minion::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void Minion::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Minion has been destroyed: Possibly drop pickup, mark for removal
	if (isDestroyed())
	{
		isMarkedForRemoval_ = true;
		return;
	}

	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);

	// Update texts
	updateTexts();
}

unsigned int Minion::getCategory() const
{
    return Category::Minion;
}

sf::FloatRect Minion::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

bool Minion::isMarkedForRemoval() const
{
	return isMarkedForRemoval_;
}

void Minion::updateMovementPattern(sf::Time dt)
{
	// Minion: Movement pattern
	const std::vector<Direction>& directions = Table[type_].directions;
	if (!directions.empty())
	{
		// Moved long enough in current direction: Change direction
		if (travelledDistance_ > directions[directionIndex_].distance)
		{
			directionIndex_ = (directionIndex_ + 1) % directions.size();
			travelledDistance_ = 0.f;
		}

		// Compute velocity from direction
		float radians = toRadian(directions[directionIndex_].angle);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);

		travelledDistance_ += getMaxSpeed() * dt.asSeconds();

		move(velocity_ * dt.asSeconds());
	}
}

float Minion::getMaxSpeed() const
{
	return Table[type_].speed;
}

void Minion::updateTexts()
{
	healthDisplay_->setString(toString(getHitpoints()) + " HP");
	healthDisplay_->setPosition(0.f, 50.f);
	healthDisplay_->setRotation(-getRotation());
}


void Minion::setVelocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

void Minion::setVelocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

sf::Vector2f Minion::getVelocity() const
{
	return velocity_;
}

void Minion::accelerate(sf::Vector2f velocity)
{
	velocity_ += velocity;
}

void Minion::accelerate(float vx, float vy)
{
	velocity_.x += vx;
	velocity_.y += vy;
}

int Minion::getHitpoints() const
{
	return hitpoints_;
}

void Minion::damage(int points)
{
	assert(points > 0);

	hitpoints_ -= points;
}

void Minion::destroy()
{
	hitpoints_ = 0;
}

bool Minion::isDestroyed() const
{
	return hitpoints_ <= 0;
}
