#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <TextNode.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Projectile : public SceneNode
{
    public:
        enum Type
        {
            Projectile01,
            TypeCount,
        };
                                Projectile(Type type, const TextureHolder& textures, const FontHolder& fonts);

        void	        		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			        updateCurrent(sf::Time dt, CommandQueue& commands);
		unsigned int        	getCategory() const;
		sf::FloatRect	        getBoundingRect() const;
        float                   getMaxSpeed() const;
        int                     getDamage() const;

    private:
        Type                    type_;
        sf::Sprite              sprite_;
        sf::Vector2f            targetDirection_;
};

#endif // PROJECTILE_H
