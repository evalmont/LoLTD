#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneFieldLayer		= 1 << 0,
	};
}

#endif // BOOK_CATEGORY_HPP
