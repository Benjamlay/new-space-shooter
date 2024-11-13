#include "game.h"

#include <iostream>

Game::Game()
{
	window_.create(sf::VideoMode(700, 680), "Space Shooter");
}

void Game::Loop()
{
    spaceShip ship2(ShipType::good_guy);
    ship2.setPosition(300, 200);
    background2.setPosition(0, -680);
    float cooldown = 1.f;
    sf::Clock asteroidsclock;
    sf::Clock Shipclock;
    float meteor_spawn_interval = 0.5f;
    float ship_spawn_interval = 6.f;
    float dt = 0.f;

    sf::Clock clock;
    sf::Time timePaused;

    bool isPaused = false;
    bool isDead = false;


	while(window_.isOpen())
	{
        //to close the SFML window _____________________________________________________________________________________________________

        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window_.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                isPaused = !isPaused;
            }
        }

        if(!isPaused)
        {
            dt = clock.restart().asSeconds();
            cooldown += dt;

            // commandes du vaisseau ______________________________________________________________________________________________________

            ship2.playerMove(dt);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (cooldown > 0.15f)
                {
                    projectiles_.Spawn(ship2.getPosition(), projectileType::good_guy, {});
                    cooldown = 0;
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
                asteroids_.Spawn(sf::Vector2f(rand() % window_.getSize().x, -31.f), { 0, 200 });
                asteroidsclock.restart();
            }

            // faire apparaitre des enemyShips ____________________________________________________________________________________________

            if (Shipclock.getElapsedTime().asSeconds() >= ship_spawn_interval)
            {
                enemyShips.Spawn(sf::Vector2f(rand() % window_.getSize().x, 0.f), ShipType::bad_guy, {});
                Shipclock.restart();
                std::cout << "new enemySpaceShip \n";
            }

            //projectiles touching something ? _____________________________________________________________________________________________

            projectiles_.CheckCollisions(asteroids_.GetEntities());
            projectiles_.CheckCollisions(enemyShips.GetEntities());

            //ship touching something ? _____________________________________________________________________________________________________

            ship2.Checkcollisions(asteroids_.GetEntities());
            ship2.Checkcollisions(enemy_projectiles_.GetEntities());
            ship2.Checkcollisions(enemyShips.GetEntities());


            //refresh ______________________________________________________________________________________________________________________

            ship2.refresh(dt);
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
            isDead = true;
            sf::Font font2;
            font2.loadFromFile("assets\\text\\text1.ttf");
            sf::Text pauseText("Dead :( ", font2, 50);
            pauseText.setPosition(window_.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window_.getSize().y / 2 - 50);

            sf::Text instructionsText("Press enter to start again ", font2, 20);
            instructionsText.setPosition(window_.getSize().x / 2 - instructionsText.getGlobalBounds().width / 2, window_.getSize().y / 2 + 50);

            window_.draw(pauseText);
            window_.draw(instructionsText);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                isDead = false;
            }
        }

        if(isPaused)
        {
            sf::Font font;
            font.loadFromFile("assets\\text\\text1.ttf");
            sf::Text pauseText("Game Paused", font, 50);
            pauseText.setPosition(window_.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window_.getSize().y / 2 - 50);

            sf::Text instructionsText("Press Escape to Resume", font, 20);
            instructionsText.setPosition(window_.getSize().x / 2 - instructionsText.getGlobalBounds().width / 2, window_.getSize().y / 2 + 50);

            window_.draw(pauseText);
            window_.draw(instructionsText);
        }
        




        window_.display();


	}
}
