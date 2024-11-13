#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H
#include <vector>

#include "asteroid.h"



class asteroidManager : public sf::Drawable
{
	std::vector<asteroid> asteroids_;
	double spawn_dt_ = 0;

public:

	//projectileManager(); //TODO add sound

	std::vector<asteroid>& GetEntities();
	
	void Spawn(sf::Vector2f spawn_position, sf::Vector2f direction);
	void Refresh(const sf::Vector2u& window_size, float dt);
	//void CheckCollisions(); //TODO check for the enemy, and the asteroid

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // ASTEROIDMANAGER_H
