#include "entity.h"

void entity::Move(const sf::Vector2u& window_size, float dt)
{
	move(direction_ * dt);
	//hitbox_.getPosition();

	sf::Vector2f position = getPosition();
	sf::Vector2f borders = sf::Vector2f(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);

	if (position.x < -1 * borders.x ||
		position.x > window_size.x + borders.x ||
		position.y < -1 * borders.y ||
		position.y > window_size.y + borders.y)
	{
		IsDead_ = true;
	}
}

void entity::Move(sf::Vector2f direction, float dt)
{
	move(direction * dt);
}

sf::FloatRect entity::get_hit_box()
{
	hitbox_ = sprite_.getGlobalBounds();

	hitbox_.left += getPosition().x;
	hitbox_.top += getPosition().y;
	return hitbox_;
}

void entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	
}

bool entity::IsDead() const
{
	return IsDead_;
}

void entity::SetDeath()
{
	IsDead_ = true;
}

sf::RectangleShape entity::draw_hit_box()
{
	sf::RectangleShape hitbox(sf::Vector2f(this->get_hit_box().width, this->get_hit_box().height));
	hitbox.setPosition(this->get_hit_box().left, this->get_hit_box().top);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.f);
	hitbox.setPosition(this->getPosition());

	return hitbox;
}

void entity::SetPosition(float x, float y)
{
	setPosition(x, y);
}

void entity::SetPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}