#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "asteroid.h"
#include "entity.h"
#include "projectile.h"


enum class ShipType
{
	good_guy,
	bad_guy
};


class spaceShip : public entity
{
private:

	ShipType type_;

	bool is_damaged_ = false;
	float damage_cool_down_;
	static sf::Texture texture_;
	int pv_ = 20;

	int enemyPV_ = 15;
	double shoot_dt_ = 0.f;
	double burst_dt_ = 0.f;
	bool burst_ready_ = false;
	bool is_shoot_ready_ = false;

public:

	spaceShip() = default;
	spaceShip(ShipType type);
	spaceShip(ShipType type, sf::Vector2f& direction);
	void playerMove(float dt);

	//about damage
	bool IsDamaged();
	void GetDamaged(int damage);
	void EnemyDamaged(int damage);
	int GetPv();

	// about refresh
	void refresh(float dt, std::vector<asteroid>& asteroids_, std::vector<projectile>& enemy_projectiles_, std::vector<spaceShip>& enemyShips);
	void enemyRefresh(float dt);

	bool IsShootReady() const { return is_shoot_ready_; }
	double ShootDt() const { return shoot_dt_; }
	sf::Vector2f GetPosition() const { return getPosition(); }

	// about collisions
	void Checkcollisions(std::vector<asteroid>& asteroids);
	void Checkcollisions(std::vector<projectile>& projectiles);
	void Checkcollisions(std::vector<spaceShip>& enemyShips);

};


#endif // SPACESHIP_H
