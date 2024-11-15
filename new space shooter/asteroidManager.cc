#include "asteroidManager.h"

#include <iostream>

std::vector<asteroid>& asteroidManager::GetEntities()
{
	return asteroids_;
}

void asteroidManager::Spawn(sf::Vector2f spawn_position)
{
	asteroids_.emplace_back();
	asteroids_.back().setPosition(spawn_position);
}

void asteroidManager::Refresh(const sf::Vector2u& window_size, float dt)
{
	auto removed_elt = std::remove_if(
		asteroids_.begin(),
		asteroids_.end(),
		[](const asteroid& p) {return p.IsDead(); });

	if (removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt, asteroids_.end());
	}

	for (asteroid& a : asteroids_)
	{
		a.Move(window_size, dt);
		//a.Rotate(); //j'ai du enlevé la rotation car je n'arrive pas à faire suivre la hitbox
	}
}

void asteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const asteroid& a : asteroids_)
	{
		target.draw(a);
	}
}
