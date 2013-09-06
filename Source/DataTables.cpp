#include <DataTables.hpp>
#include <Minion.hpp>
//#include <Projectile.hpp>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<MinionData> initializeMinionData()
{
	std::vector<MinionData> data(Minion::TypeCount);

	data[Minion::Standard].hitpoints = 100;
	data[Minion::Standard].speed = 100.f;
	data[Minion::Standard].texture = Textures::Minion01;
	data[Minion::Standard].directions.push_back(Direction(  0.f,  (32.f*6 )));
	data[Minion::Standard].directions.push_back(Direction(+90.f,  (32.f*18)));
	data[Minion::Standard].directions.push_back(Direction(  0.f,  (32.f*6 )));
	data[Minion::Standard].directions.push_back(Direction(-90.f,  (32.f*18)));

	return data;
}
/*
std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Bullet;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Bullet;

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::Missile;

	return data;
}*/
