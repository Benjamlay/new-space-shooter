#include "asteroidManager.h"

#include <iostream>

std::vector<asteroid>& asteroidManager::GetEntities()
{
	return asteroids_;
}

void asteroidManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f direction)
{
	asteroids_.emplace_back(direction);
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
		a.Rotate();
	}
}

void asteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const asteroid& a : asteroids_)
	{
		target.draw(a);
	}
}
