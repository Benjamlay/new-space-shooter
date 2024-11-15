#include "game.h"

#include <iostream>

Game::Game()
{
	window_.create(sf::VideoMode(700, 680), "Space Shooter");
    music_Sound_.loadFromFile("assets\\sound\\music.wav");
    music_.setBuffer(music_Sound_);
}

void Game::Setup()
{
    music_.play();
    ShootPlayercooldown = 1.f;
	asteroidsclock;
    Shipclock;
	meteor_spawn_interval = 0.5f;
	ship_spawn_interval = 3.f;
	dt = 0.f;
    bool IsDead = false;
    background2.setPosition(0, -680);
    
} 

void Game::Loop()
{
    spaceShip ship2(ShipType::good_guy);
    ship2.setPosition(300, 200);
    Setup();

	while(window_.isOpen())
	{
        //to close the SFML window _____________________________________________________________________________________________________
        dt = clock.restart().asSeconds();

        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window_.close();
            }

            /*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                isPaused = !isPaused;
            }*/
        }

        if(!IsDead)
        {
            
            ShootPlayercooldown += dt;

            // commandes du vaisseau ______________________________________________________________________________________________________

            ship2.playerMove(dt);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (ShootPlayercooldown > 0.15f)
                {
                    projectiles_.Spawn(ship2.getPosition(), projectileType::good_guy, {});
                    ShootPlayercooldown = 0;
                }
            }

            //background defilant :________________________________________________________________________________________________________

            background1.backgroundMoving(background2, dt);
            background2.backgroundMoving(background1, dt);

            // draw hitbox to see if it works _____________________________________________________________________________________________

            ship2.get_hit_box();

            // faire apparaitre des asteroides ____________________________________________________________________________________________

            if (asteroidsclock.getElapsedTime().asSeconds() >= meteor_spawn_interval)
            {
                asteroids_.Spawn(sf::Vector2f(rand() % window_.getSize().x, -31.f), {});
                asteroidsclock.restart();
            }

            // faire apparaitre des enemyShips ____________________________________________________________________________________________

            if (Shipclock.getElapsedTime().asSeconds() >= ship_spawn_interval)
            {
                enemyShips.Spawn(sf::Vector2f(rand() % window_.getSize().x, 0.f), ShipType::bad_guy, {});
                Shipclock.restart();
            }

            //projectiles touching something ? _____________________________________________________________________________________________

            projectiles_.CheckCollisions(asteroids_.GetEntities());
            projectiles_.CheckCollisions(enemyShips.GetEntities());


            //refresh ______________________________________________________________________________________________________________________

            ship2.refresh(dt, asteroids_.GetEntities(), enemy_projectiles_.GetEntities(), enemyShips.GetEntities());
            enemy_projectiles_.Refresh(window_.getSize(), dt);
            projectiles_.Refresh(window_.getSize(), dt);
            asteroids_.Refresh(window_.getSize(), dt);
            enemyShips.Refresh(dt, window_.getSize(), enemy_projectiles_);

            // draw ________________________________________________________________________________________________________________________

        }

        window_.clear();
        window_.draw(background1);
        window_.draw(background2);
        window_.draw(ship2);
        window_.draw(projectiles_);
        window_.draw(enemy_projectiles_);
        window_.draw(asteroids_);
        window_.draw(enemyShips);

        if(ship2.GetPv() <= 0)
        {
            IsDead = true;
            sf::Font font2;
            font2.loadFromFile("assets\\text\\text1.ttf");
            sf::Text pauseText("ship is destroyed... ", font2, 50);
            pauseText.setPosition(window_.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window_.getSize().y / 2 - 50);

            sf::Text instructionsText("Press enter to start again ", font2, 20);
            instructionsText.setPosition(window_.getSize().x / 2 - instructionsText.getGlobalBounds().width / 2, window_.getSize().y / 2 + 50);

            window_.draw(pauseText);
            window_.draw(instructionsText);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                
            }
        }

       /* if(isPaused)
        {
            sf::Font font;
            font.loadFromFile("assets\\text\\text1.ttf");
            sf::Text pauseText("Game Paused", font, 50);
            pauseText.setPosition(window_.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window_.getSize().y / 2 - 50);

            sf::Text instructionsText("Press Escape to Resume", font, 20);
            instructionsText.setPosition(window_.getSize().x / 2 - instructionsText.getGlobalBounds().width / 2, window_.getSize().y / 2 + 50);

            window_.draw(pauseText);
            window_.draw(instructionsText);
        }*/


        window_.display();
	}
}
