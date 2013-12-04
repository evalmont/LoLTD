#include <Turret.hpp>
#include <DataTables.hpp>
#include <Utility.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<TurretData> Table = initializeTurretData();
}

Turret::Turret(Type type, const TextureHolder& textures, const FontHolder& fonts)
: SceneNode(Category::Turret)
, type_(type)
, sprite_(textures.get(Table[type].texture))
{
    centerOrigin(sprite_);
}

void Turret::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

void Turret::updateCurrent(sf::Time dt, CommandQueue& commands)
{

}

unsigned int Turret::getCategory() const
{
    return Category::Turret;
}

sf::FloatRect Turret::getBoundingRect() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}
