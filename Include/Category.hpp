#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneFieldLayer		= 1 << 0,
		Minion              = 1 << 1,
		Turret              = 1 << 2,
	};
}

#endif // BOOK_CATEGORY_HPP
