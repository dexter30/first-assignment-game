#pragma once
#include "pawn.h"

//This will be our goal item. The item the player will strive to get to complete the game.
class goalItem :
	public pawn
{
public:
	goalItem(int xi, int yi);//We will provide the position from the text file like the enemy and walls
	~goalItem(void);

	bool collisionCheck(int x2, int y2, int w = 32, int h=32);
	BITMAP newScreen(BITMAP *buff);
	bool collection();
private:
	bool isCollected;
		SAMPLE *bell;
		bool soundMade;
};

