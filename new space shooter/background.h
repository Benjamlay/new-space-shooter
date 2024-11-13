#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>


class Background : public sf::Drawable, public sf::Transformable
{
	sf::Sprite sprite_background_;
	sf::Texture texture_background_;

	float speed_ = 50.0f;

	sf::Vector2u textureSize = texture_background_.getSize();
	float imageHeight = static_cast<float>(textureSize.y);

	public:

	Background();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void MoveBackground(sf::Vector2f direction, float dt);
	void backgroundMoving(Background& background2, float dt);

	float GetImageHeight();

};


#endif // BACKGROUND_H
