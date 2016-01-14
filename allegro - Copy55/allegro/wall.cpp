#include "wall.h"


wall::wall(int x1, int y1, int width, int heigh)
	//Wall properties are set in the constructor.
{
	x = x1;
	y = y1;
	w = width;
	h = heigh;
	
}


wall::~wall(void)
{
	
}

BITMAP wall::imageToScreen(BITMAP *buff)
{
	//We blit the image to the main buffer. 
	bufferedWall = load_bitmap("brickwall.bmp", NULL);
	blit(bufferedWall, buff, 0,0, x, y, w, h);
	destroy_bitmap(bufferedWall);
	return *buff;
}
float wall::getx()
{
	return x;
}

float wall::gety()
{
	return y;
}

float wall::getw()
{
	return w;
}

float wall::geth()
{
	return h;
}