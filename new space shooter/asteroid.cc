#include "asteroid.h"
#include <random>

sf::Texture asteroid::asteroids_texture_;

asteroid::asteroid()
{
	asteroids_texture_.loadFromFile("assets\\BrownMeteor.png");
	sprite_.setTexture(asteroids_texture_);
	sprite_.setScale(0.75f, 0.75f);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> x_variation(-70.0f, 70.0f);
	direction_ = { x_variation(gen), 200 };
}

void asteroid::Rotate()
{
	std::random_device rn_device;
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> uniform_dist_x(0.005, 0.05);

	setRotation(getRotation() + uniform_dist_x(engine));
}

sf::FloatRect asteroid::Get_hit_box()
{
	{
		hitbox_ = sprite_.getGlobalBounds();

		hitbox_.left += this->getPosition().x;
		hitbox_.top += this->getPosition().y;

		return hitbox_;
	}
}
