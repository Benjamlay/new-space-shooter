#include "Background.h"

Background::Background()
{
	texture_background_.loadFromFile("assets\\blueBigger.png");
	sprite_background_.setTexture(texture_background_);

}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_background_, states);
}

void Background::MoveBackground(sf::Vector2f direction, float dt)
{
	{
		float speed = speed_;

		setPosition(getPosition() + speed * direction * dt);
	}
}

void Background::backgroundMoving(Background& background2, float dt)
{
	this->MoveBackground(sf::Vector2f(0, 1), dt);
	if (this->getPosition().y >= 680) {
		this->setPosition(0, background2.getPosition().y - 680);
	}
	background2.MoveBackground(sf::Vector2f(0, 1), dt);
	if (background2.getPosition().y >= 680) {
		background2.setPosition(0, this->getPosition().y - 680);
	}
}

float Background::GetImageHeight()
{
	return imageHeight;
}
