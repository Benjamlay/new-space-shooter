#include "spaceShip.h"

#include <iostream>

sf::Texture spaceShip::texture_;

constexpr double kShootPeriod = 0.6f;
constexpr double kBurstPeriod = 0.f;

spaceShip::spaceShip(ShipType type)
{
	texture_sprite_.loadFromFile("assets\\playerShip1_orange.png");
	sprite_.setTexture(texture_sprite_);
	sprite_.setScale(0.5f, 0.5f);
}

spaceShip::spaceShip(ShipType type, sf::Vector2f& direction) : type_(type)
{
	if(type == ShipType::good_guy)
	{
		texture_sprite_.loadFromFile("assets\\playerShip1_orange.png");
		sprite_.setTexture(texture_sprite_);
	}
	if(type == ShipType::bad_guy)
	{
		texture_.loadFromFile("assets\\playerShip2_blue.png");
		sprite_.setRotation(180);
		sprite_.setTexture(texture_);
		direction_ = { 0, 50 };
	}

	
	sprite_.setScale(0.5f, 0.5f);
}

void spaceShip::playerMove(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		this->Move(sf::Vector2f(0, -500), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->Move(sf::Vector2f(0, 500), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->Move(sf::Vector2f(-500, 0), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->Move(sf::Vector2f(500, 0), dt);
	}
}

bool spaceShip::IsDamaged()
{
	return is_damaged_;
}

void spaceShip::GetDamaged(int damage)
{
	pv_ -= damage;
	is_damaged_ = true;

	if(pv_ <= 0)
	{
		SetDeath();
	}
	damage_cool_down_ = 3.f;
	
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

void spaceShip::refresh(float dt)
{
	if (is_damaged_)
	{
		damage_cool_down_ -= dt;
		std::cout << pv_ << '\n';

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

	if(pv_ <= 0)
	{
		SetDeath();
	}
}

void spaceShip::enemyRefresh(float dt)
{
	float damage_cool_down_ = 1.f;

	if (is_damaged_)
	{
		damage_cool_down_ -= dt;
		//std::cout << pv_ << '\n';

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
			this->GetDamaged(20);
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
			this->GetDamaged(1);
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
			this->GetDamaged(5);
		}
	}
}




