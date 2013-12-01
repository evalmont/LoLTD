#ifndef TURRET_H
#define TURRET_H

#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <TextNode.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Turret : public SceneNode
{
    public:
        enum Type
        {
            Standard,
            TypeCount,
        };
                                Turret(Type type, const TextureHolder& textures, const FontHolder& fonts);

        virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getBoundingRect() const;

    protected:
    private:
        Type                    type_;
        sf::Sprite              sprite_;
};

#endif // TURRET_H
