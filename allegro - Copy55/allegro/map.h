#pragma once
#include <allegro.h>

class map
{
public:
	map(void);
	~map(void);
	BITMAP mapScreen(BITMAP *buff);//Buff the map tiles to the screen.
	//void generateMap();

private:
	BITMAP * tile;//Holds the tile bitmap.

};

