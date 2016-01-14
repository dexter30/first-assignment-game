#pragma once
#include "pawn.h"

//This class is actually quite special. It will actually contain a function that allows it to soar through the screen towards the user.
class shuriken :
	public pawn
{
public:
	//First I set the values in the constructor. I must have a start pint and end point that I pass in from the game.
	shuriken(float ninjax, float ninjay, float enemyX, float enemyY);
	~shuriken(void);
	//Then i blit the star from its current position on screen.
	BITMAP thrownStar(BITMAP * buff, int x2, int y2);
	//The program must know which stars are open at all times.So i have a value that returns it.
	bool getIsAlive();
	//Finally I need to know when the star actualy collides with something so this function alerts the main game when it does.
	bool collisionCheck(int x2, int y2, int w = 32, int h=32);
	
	
private:
	//For this function to fly across the screen in a straight line. I need to kow the start and end positions to do the equation of a straight line
	float startX;
	float startY;
	float endX;
	float endY;
	//DistanceAir is the continually updated X co ordinate that I use.
	float distanceAir;


	//Finally I have some booleans that I need to know in the main game so i may delete.
	bool isAlive;
	bool speedy;

};

