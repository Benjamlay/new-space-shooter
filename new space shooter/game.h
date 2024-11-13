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

public:
	Game();
	void Loop();
};


#endif // GAME_H
