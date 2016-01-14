#pragma once
#include <allegro.h>
//It's a simple function that blits a brick wall to a location on screen to provide the player with boundaries.
class wall
{
public:
	//The costructor needs to have a position and size settings.
	wall(int x1, int y1, int width, int height);
	~wall(void);
	//Then to allow them to collide with the player I need to e able to read them with these getter functios.
	float getx();
	float gety();
	float geth();
	float getw();

	//Finally I need to blit them to the screen.
	BITMAP imageToScreen(BITMAP *buff);
	
private:
	// And of course I have them saved privately.
	BITMAP * bufferedWall;
	float x;
	float y;
	float w;
	float h;
};

