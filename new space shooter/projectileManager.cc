#include "projectileManager.h"

#include <iostream>

projectileManager::projectileManager()
{
	LaserSound_.loadFromFile("assets\\sound\\laserSound.wav");
	Laser_.setBuffer(LaserSound_);
	Laser_.setVolume(50);
}

std::vector<projectile>& projectileManager::GetEntities()
{
	return projectiles_;
}

void projectileManager::Spawn(sf::Vector2f spawn_position, projectileType type, sf::Vector2f direction)
{
	projectiles_.emplace_back(type, direction);
	projectiles_.back().setPosition(spawn_position);
	if(lastShotTime.getElapsedTime().asSeconds() >= 0.3)
	{
		Laser_.play();
		lastShotTime.restart();
	}
}

void projectileManager::Refresh(const sf::Vector2u& window_size, float dt)
{
	auto removed_elt = std::remove_if(
		projectiles_.begin(),
		projectiles_.end(),
		[](const projectile& p) {return p.IsDead(); });

		if (removed_elt != projectiles_.end())
		{
			projectiles_.erase(removed_elt, projectiles_.end());
		}

	for(projectile& p : projectiles_)
	{
		p.Move(window_size, dt);
	}
}

void projectileManager::get_hit_box()
{
	for(projectile& p : projectiles_)
	{
		p.get_hit_box();
	}
}

void projectileManager::CheckCollisions(std::vector<asteroid>& asteroids)
{
	for(auto& p : projectiles_)
	{
		
		for( auto& a : asteroids)
		{
			a.get_hit_box();
			if (p.IsDead() == false && a.IsDead() == false && p.get_hit_box().intersects(a.get_hit_box()))
			{
				p.SetDeath();
				a.SetDeath();
			}
		}
	}
}

void projectileManager::CheckCollisions(std::vector<spaceShip>& enemyShips)
{
	for (auto& p : projectiles_)
	{

		for (auto& s : enemyShips)
		{
			s.get_hit_box();
			if (p.IsDead() == false && s.IsDead() == false && p.get_hit_box().intersects(s.get_hit_box()))
			{
				p.SetDeath();
				s.EnemyDamaged(1);
			}
		}
	}
}


void projectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const projectile& p : projectiles_)
	{
		target.draw(p);
	}
}
