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
    music_.setLoop(true);
    music_.play();
    ShootPlayercooldown = 1.f;
	meteor_spawn_interval = 0.5f;
	ship_spawn_interval = 3.f;
	dt = 0.f;
    bool IsDead = false;
    background2.setPosition(0, -680);
    difficulty = 0;
    score_ = 0.f;
} 

bool Game::Loop(bool& playagain)
{
    spaceShip ship(ShipType::good_guy);
    ship.setPosition(300, 650);
    Setup();
    sf::Font font2;
    font2.loadFromFile("assets\\text\\text1.ttf");

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
                return false;
            }
        }

        

        if(!IsDead)
        {
            ShootPlayercooldown += dt;
            score_ += 2 * dt;
            // commandes du vaisseau ______________________________________________________________________________________________________

            ship.playerMove(dt, window_);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (ShootPlayercooldown > 0.15f)
                {
                    projectiles_.Spawn(ship.getPosition(), projectileType::good_guy, {});
                    ShootPlayercooldown = 0;
                }
            }

            //background defilant :________________________________________________________________________________________________________

            background1.backgroundMoving(background2, dt);
            background2.backgroundMoving(background1, dt);

            // draw hitbox to see if it works _____________________________________________________________________________________________

            ship.get_hit_box();

            // faire apparaitre des asteroides ____________________________________________________________________________________________

            if (asteroidsclock.getElapsedTime().asSeconds() >= meteor_spawn_interval)
            {
                asteroids_.Spawn(sf::Vector2f(rand() % window_.getSize().x, -31.f));
                asteroidsclock.restart();
            }

            // faire apparaitre des enemyShips ____________________________________________________________________________________________

            if (Shipclock.getElapsedTime().asSeconds() >= ship_spawn_interval)
            {
                enemyShips.Spawn(sf::Vector2f(rand() % window_.getSize().x, 0.f), ShipType::bad_guy);
                Shipclock.restart();
            }

            ship_spawn_interval -= 0.01f * dt;

            std::cout << ship_spawn_interval << '\n';
            //projectiles touching something ? _____________________________________________________________________________________________

            projectiles_.CheckCollisions(asteroids_.GetEntities());
            projectiles_.CheckCollisions(enemyShips.GetEntities());

            //refresh ______________________________________________________________________________________________________________________

            ship.refresh(dt, asteroids_.GetEntities(), enemy_projectiles_.GetEntities(), enemyShips.GetEntities(), font2, window_);
            enemy_projectiles_.Refresh(window_.getSize(), dt);
            projectiles_.Refresh(window_.getSize(), dt);
            asteroids_.Refresh(window_.getSize(), dt);
            enemyShips.Refresh(dt, window_.getSize(), enemy_projectiles_);

        }

        // draw ________________________________________________________________________________________________________________________
        window_.clear();
        window_.draw(background1);
        window_.draw(background2);
        window_.draw(ship);
        window_.draw(projectiles_);
        window_.draw(enemy_projectiles_);
        window_.draw(asteroids_);
        window_.draw(enemyShips);
       
        //draw player's PV
        sf::Text PvText;
        PvText.setFont(font2);
        PvText.setString("PV : " + std::to_string(ship.GetPv()));
        PvText.setCharacterSize(20);
        PvText.setFillColor(sf::Color::White);
        window_.draw(PvText);

        sf::Text ScoreText;
        ScoreText.setFont(font2);
        ScoreText.setString("Score : " + std::to_string(score_));
        ScoreText.setCharacterSize(20);
        ScoreText.setFillColor(sf::Color::White);
        ScoreText.setPosition(0, 30);
        window_.draw(ScoreText);

        if(ship.GetPv() <= 0)
        {
            IsDead = true;
            sf::Text pauseText("ship is destroyed! ", font2, 50);
            pauseText.setPosition(window_.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window_.getSize().y / 2 - 50);
            sf::Text instructionsText("Press enter to start again \n   Press Escape to exit ", font2, 20);
            instructionsText.setPosition(window_.getSize().x / 2 - instructionsText.getGlobalBounds().width / 2, window_.getSize().y / 2 + 50);

            window_.draw(pauseText);
            window_.draw(instructionsText);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                return playagain = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return playagain = false;
            }
        }

        window_.display();
	}
}
