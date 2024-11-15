#include "spaceShip.h"

#include <iostream>

sf::Texture spaceShip::texture_;

constexpr double kShootPeriod = 0.6f;
constexpr double kBurstPeriod = 0.f;


spaceShip::spaceShip(ShipType type) : type_(type)
{
	if (type == ShipType::good_guy)
	{
		texture_sprite_.loadFromFile("assets\\playerShip1_orange.png");
		sprite_.setTexture(texture_sprite_);
	}
	if (type == ShipType::bad_guy)
	{
		texture_.loadFromFile("assets\\playerShip2_blue.png");
		sprite_.setRotation(180);
		sprite_.setTexture(texture_);
		direction_ = { 0, 50 };
	}
	sprite_.setScale(0.5f, 0.5f);
}

void spaceShip::playerMove(float dt, sf::RenderWindow& window_)
{

	sf::Vector2u windowSize = window_.getSize();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->Move(sf::Vector2f(0, -500), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->Move(sf::Vector2f(0, 500), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->Move(sf::Vector2f(-500, 0), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->Move(sf::Vector2f(500, 0), dt);
	}

	sf::Vector2f position = this->getPosition();

	if (position.x > windowSize.x) {
		position.x = 0;
	}
	else if (position.x < 0) {
		position.x = windowSize.x;
	}

	if (position.y > windowSize.y) {
		position.y = 675; 
	}
	else if (position.y < 0) {
		position.y = windowSize.y; 
	}

	this->setPosition(position);

}

bool spaceShip::IsDamaged()
{
	return is_damaged_;
}

void spaceShip::GetDamaged(int damage)
{
	pv_ -= damage;
	is_damaged_ = true;

	if (pv_ <= 0)
	{
		SetDeath();
	}
	damage_cool_down_ = 2.f;

}

void spaceShip::EnemyDamaged(int damage)
{
	enemyPV_ -= damage;
	is_damaged_ = true;

	if (enemyPV_ <= 0)
	{
		SetDeath();
	}
}

int spaceShip::GetPv()
{
	return pv_;
}


void spaceShip::refresh(float dt, std::vector<asteroid>& asteroids_, std::vector<projectile>& enemy_projectiles_, std::vector<spaceShip>& enemyShips, sf::Font font2, sf::RenderWindow& window_)
{

	Checkcollisions(asteroids_);
	Checkcollisions(enemy_projectiles_);
	Checkcollisions(enemyShips);


	if (is_damaged_)
	{
		damage_cool_down_ -= dt;
		

		//devient transparent
		int visibilitySwitch = static_cast<int>(damage_cool_down_ * 10) % 2;
		if (visibilitySwitch == 0) {
			sprite_.setColor(sf::Color(255, 255, 255, 50));
		}
		else {
			sprite_.setColor(sf::Color(255, 255, 255, 255));
		}
	}
	//n'est plus transparent
	if (damage_cool_down_ <= 0)
	{
		is_damaged_ = false;
		sprite_.setColor(sf::Color(255, 255, 255, 255));
	}

	if (pv_ <= 0)
	{
		IsDead_ = true;
	}


}

void spaceShip::enemyRefresh(float dt)
{
	float damage_cool_down_ = 1.f;

	//n'est plus transparent

	shoot_dt_ += dt;
	burst_dt_ += dt;

	if (burst_dt_ >= kBurstPeriod)
	{
		burst_ready_ = !burst_ready_;
		burst_dt_ = 0;
	}

	if (shoot_dt_ >= kShootPeriod && burst_ready_)
	{
		shoot_dt_ = 0;
		is_shoot_ready_ = true;
	}
	else
	{
		is_shoot_ready_ = false;
	}
}

void spaceShip::Checkcollisions(std::vector<asteroid>& asteroids)
{
	for (auto& a : asteroids)
	{
		if (a.IsDead() == false && this->get_hit_box().intersects(a.get_hit_box()))
		{
			a.SetDeath();
			if (!is_damaged_)
			{
				this->GetDamaged(20);
			}

		}
	}
}

void spaceShip::Checkcollisions(std::vector<projectile>& projectiles)
{
	for (auto& a : projectiles)
	{
		if (a.IsDead() == false && this->get_hit_box().intersects(a.get_hit_box()))
		{
			a.SetDeath();
			if (!is_damaged_)
			{
				this->GetDamaged(1);
			}
		}
	}
}

void spaceShip::Checkcollisions(std::vector<spaceShip>& enemyShips)
{

	for (auto& a : enemyShips)
	{
		if (a.IsDead() == false && this->get_hit_box().intersects(a.get_hit_box()))
		{
			a.EnemyDamaged(5);
			if (!is_damaged_)
			{
				this->GetDamaged(5);
			}
		}
	}
}

