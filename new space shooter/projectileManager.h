#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H
#include <vector>

#include "asteroid.h"
#include "projectile.h"
#include "spaceShip.h"
#include <SFML/Audio.hpp>

class projectileManager : public sf::Drawable
{

	std::vector<projectile> projectiles_;
	sf::SoundBuffer LaserSound_;
	sf::Sound Laser_;

public:

	projectileManager();
	std::vector<projectile>& GetEntities();
	void Spawn(sf::Vector2f spawn_position, projectileType type, sf::Vector2f direction);
	void Refresh(const sf::Vector2u& window_size, float dt);
	void get_hit_box();
	void CheckCollisions(std::vector<asteroid>& asteroids);
	void CheckCollisions(std::vector<spaceShip>& enemyShips);
	//TODO check for the enemy, and the asteroid
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};


#endif // PROJECTILEMANAGER_H
