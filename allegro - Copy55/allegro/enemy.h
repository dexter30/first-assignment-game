#pragma once
#include "pawn.h"

//This is the enemy class that will have the information for the enemies.
class enemy :
	public pawn
{
public:
	//The constructor will have 
	enemy(int x1, int y1, bool whichway = false);
	~enemy(void);
	//This function updates the buffer that you feed in.
	BITMAP newScreen(BITMAP *buff);
	//This function moves the position of the pawn
	void movement();
	//This function checks it's area to sense if the player is near by.
	bool sensePlayer(int x2, int y2);
	//Finally this is a debugging command to check the limits of the enemies.

private:
	//These are the private positions of the pawn.
	float startX;
	float startY;
	bool isMovingUp; //This variable will decide which way the enemy is going
	int boundaries;//The variable of the enemies size.
	bool direction; //If this is true then the object will go left or right if this is false it will go vertically.

};

