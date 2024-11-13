#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include "entity.h"

class asteroid : public entity
{
	static sf::Texture asteroids_texture_;


public:

	asteroid(sf::Vector2f& direction);
};


#endif // ASTEROIDS_H
