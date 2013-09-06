#ifndef BOOK_MINION_HPP
#define BOOK_MINION_HPP

#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <TextNode.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Minion : public SceneNode
{
    public:
        enum Type
        {
            Standard,
            TypeCount,
        };
                                Minion(Type type, const TextureHolder& textures, const FontHolder& fonts);

        virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getBoundingRect() const;

        void				    setVelocity(sf::Vector2f velocity);
		void			    	setVelocity(float vx, float vy);
		void			    	accelerate(sf::Vector2f velocity);
		void			    	accelerate(float vx, float vy);
		sf::Vector2f	    	getVelocity() const;
		void                    updateMovementPattern(sf::Time dt);

		int				    	getHitpoints() const;
		void			    	damage(int points);
		void			    	destroy();
		virtual bool		    isDestroyed() const;
		virtual bool 			isMarkedForRemoval() const;

	private:
		void					updateTexts();
		float                   getMaxSpeed() const;

	private:
		Type					type_;
		sf::Sprite				sprite_;
		bool 					isMarkedForRemoval_;

        int                     hitpoints_;
		sf::Vector2f			velocity_;

        float                   travelledDistance_;
		std::size_t				directionIndex_;
		TextNode*				healthDisplay_;
};

#endif // BOOK_MINION_HPP
