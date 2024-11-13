#include "asteroid.h"


sf::Texture asteroid::asteroids_texture_;

asteroid::asteroid(sf::Vector2f& direction)
{
	asteroids_texture_.loadFromFile("assets\\BrownMeteor.png");
	sprite_.setTexture(asteroids_texture_);
	sprite_.setScale(0.75f, 0.75f);
	direction_ = direction;
}
