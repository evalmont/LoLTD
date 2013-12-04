#include <Projectile.hpp>
#include <DataTables.hpp>
#include <Utility.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures, const FontHolder& fonts)
: SceneNode(Category::Projectile)
, type_(type)
, sprite_(textures.get(Table[type].texture))
{
    centerOrigin(sprite_);
}


void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{

}

unsigned int Projectile::getCategory() const
{
    return Category::Projectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}
