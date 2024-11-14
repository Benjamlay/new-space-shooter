#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "asteroidManager.h"
#include "background.h"
#include "enemyManager.h"
#include "projectileManager.h"
#include "spaceShip.h"


class Game
{
	sf::RenderWindow window_;
	spaceShip ship1;
	Background background1;
	Background background2;
	projectileManager projectiles_;
	projectileManager enemy_projectiles_;
	asteroidManager asteroids_;
	enemyManager enemyShips;
	sf::Clock clock;

	float ShootPlayercooldown = 1.f;
	sf::Clock asteroidsclock;
	sf::Clock Shipclock;
	float meteor_spawn_interval = 0.5f;
	float ship_spawn_interval = 6.f;
	float dt = 0.f;

	bool IsDead = false;
public:
	Game();
	void Setup();
	void Loop();
};


#endif // GAME_H
