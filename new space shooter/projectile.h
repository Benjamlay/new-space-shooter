#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "entity.h"


enum class projectileType
{
	good_guy,
	bad_guy
};
class projectile : public entity
{
	projectileType type_;
	static sf::Texture enemy_texture_;
	static sf::Texture ally_texture_;

public:

	projectile(projectileType& type, sf::Vector2f& direction);
	sf::Vector2f getDirection();
};


#endif // PROJECTILE_H
