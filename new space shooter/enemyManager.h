#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H


#include <SFML/Graphics.hpp>

#include "projectileManager.h"
#include "spaceShip.h"


class enemyManager : public sf::Drawable
{
	std::vector<spaceShip> enemy_ships_;
	double spawn_dt_ = 0;


public:

	std::vector<spaceShip>& GetEntities();
	void Spawn(sf::Vector2f spawn_position, ShipType type, sf::Vector2f direction);
	void Refresh(const float dt, const sf::Vector2u& window_size, projectileManager& enemy_missiles_manager);
	//void Checkcollisions(std::vector<projectile>& projectiles); not useful

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // ENEMYMANAGER_H
