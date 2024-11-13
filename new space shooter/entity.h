#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class entity : public sf::Drawable, public sf::Transformable
{
protected:

	sf::Texture texture_sprite_;
	sf::Sprite sprite_;
	sf::Vector2f direction_;

	sf::FloatRect hitbox_;
	bool IsDead_ = false;

public:

	void Move(const sf::Vector2u& window_size, float dt);
	void Move(sf::Vector2f direction, float dt); //this is only for the player Ship
	sf::FloatRect get_hit_box();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool IsDead() const;
	void SetDeath();
	sf::RectangleShape draw_hit_box();

	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
};


#endif // ENTITY_H
