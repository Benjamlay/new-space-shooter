#include "projectile.h"
#include <cmath>

sf::Texture projectile::enemy_texture_;
sf::Texture projectile::ally_texture_;

projectile::projectile(projectileType& type, sf::Vector2f& direction) : type_(type)
{
	if(type == projectileType::good_guy)
	{
		ally_texture_.loadFromFile("assets\\laserRed01.png");
		sprite_.setTexture(ally_texture_);
		sprite_.setOrigin(-45, 50);
		direction_ = {0, -900};
		
	}
	if (type == projectileType::bad_guy)
	{
		enemy_texture_.loadFromFile("assets\\laserBlue01.png");
		sprite_.setTexture(enemy_texture_);
		sprite_.setOrigin(60, 70);
		direction_ = direction;
		float angle = std::atan2(direction.x, direction.y) * 180 / 3.14159265358979323846;
		sprite_.setRotation(-angle);
	}

	
	sprite_.setScale(0.5f, 0.5f);
}

sf::Vector2f projectile::getDirection()
{
	return direction_ = { 0, -1300 };
}
