#ifndef BOOK_MINION_HPP
#define BOOK_MINION_HPP

#include <ResourceHolder.hpp>

class Minion
{
    public:
        enum Type
        {
            Standard,
        };
                Minion(Type type, const TextureHolder& textures, const FontHolder& fonts);

};

#endif // BOOK_MINION_HPP
