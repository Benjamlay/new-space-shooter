#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include "entity.h"

class asteroid : public entity
{
	static sf::Texture asteroids_texture_;


public:

	asteroid();
	void Rotate();
	sf::FloatRect Get_hit_box();
	
};


#endif // ASTEROIDS_H
