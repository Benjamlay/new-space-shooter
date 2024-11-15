#include "enemyManager.h"

#include <iostream>
#include <random>


std::vector<spaceShip>& enemyManager::GetEntities()
{
	return enemy_ships_;
}

void enemyManager::Spawn(sf::Vector2f spawn_position, ShipType type)
{
	enemy_ships_.emplace_back(type);
	enemy_ships_.back().setPosition(spawn_position);
}

void enemyManager::Refresh(const float dt, const sf::Vector2u& window_size, projectileManager& enemy_missiles_manager)
{

		auto removed_elt = std::remove_if(
			enemy_ships_.begin(),
			enemy_ships_.end(),
			[](const spaceShip& e) {return e.IsDead(); }
		);

		if (removed_elt != enemy_ships_.end())
		{
			enemy_ships_.erase(removed_elt, enemy_ships_.end());
		}


		for (auto& e : enemy_ships_)
		{
			e.enemyRefresh(dt);
			e.Move(window_size, dt);

			if (e.IsShootReady())
			{
				enemy_missiles_manager.Spawn(e.GetPosition(), projectileType::bad_guy,  {200, 800});
				enemy_missiles_manager.Spawn(e.GetPosition(), projectileType::bad_guy, { -200, 800 });
			}
			
		}
}

void enemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& e : enemy_ships_)
	{
		target.draw(e);
	}
}


