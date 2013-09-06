#ifndef BOOK_DATATABLES_HPP
#define BOOK_DATATABLES_HPP

#include <ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>
#include <functional>

class Minion;

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct MinionData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	std::vector<Direction>			directions;
};
/*
struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::ID					texture;
};*/

std::vector<MinionData>	initializeMinionData();
//std::vector<ProjectileData>	initializeProjectileData();

#endif // BOOK_DATATABLES_HPP
