// new space shooter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "game.h"



int main()
{
	bool playagain;

	do
	{
		playagain = false;
		Game MyGame;
		MyGame.Loop(playagain);

	}while(playagain);
	
}

