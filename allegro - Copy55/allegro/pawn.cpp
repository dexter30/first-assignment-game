#include "pawn.h"


pawn::pawn(void)
{

	//Object position
	x = 320;
	y = 200;

	//Player properties
	speed = 3;
	spriteSizeX = 14;
	spriteSizeY = 32;

	//Frame of animation
	animationFrame=0;
	
}


pawn::~pawn(void)
{
	
}
//Getters/Setters
float pawn::getx()
{
	return x;
}

float pawn::gety()
{
	return y;
}

void pawn::setX(float tempx)
{
	x = tempx;
}

void pawn::setY(float tempy)
{
	y = tempy;
}

//The controls we get the current position and simply increment/decrement. Then when the last buffer is cleared we blit to the new position.
void pawn::controls(int x2,int y2, int w, int h)
{
	int oldx = x;
	int oldy = y;
	

	if(key[KEY_D])
	{
		x+=speed;
	}
	if(key[KEY_S])
	{
		y+= speed;
		//The animation frame relates to our bitmap. we have several frames of movement and we simply tell the program to go to the next position.
		animationFrame+=14;
		if (animationFrame>=112)
		{
			animationFrame=0;
		}
		
	}
	if (key[KEY_A])
	{
	x-=speed;
	}
	if (key[KEY_W])
	{
		y-=speed;
		animationFrame+=14;
		if (animationFrame>=112)
		{
			animationFrame=0;
		}
	}
	if (key[KEY_LSHIFT])
	{
		speed = 0.5;
	}
	else
	{
		speed = 2;
	}
	boundary();
	

	//This is my collistion checking function. The values I pass in here are for the walls.
	//If the player intersets with a wall his position is set back a few places.
	if ((x >= x2 +w) ||
		(y >= y2 +h) ||
		(x2 >= x +16) || 
		(y2 >= y +16))   

	{

	}
	else
	{
		
		//y = oldy;
		//I had to add this secondary check because for some reason the program wasn't properly checking when the player was on the right of the wall.
		if(y > y2- 1)
		{
			y+=9;

		}
		if(x > x2 - 1)
		{
			x+=9;
		}
		if(x2 > x )
		{
			x-=9;
		}
		if(y2 > y )
		{
			y-=9;
		}
	}
}

BITMAP pawn::newScreen(BITMAP *buff)
{
	
	
	sprite = load_bitmap("python.bmp", NULL);
	masked_blit(sprite, buff,animationFrame,0,(x),(y),14, 32);
	
	destroy_bitmap(sprite);
	return *buff;
}

void pawn::boundary()
{
	//These are to put the basic boundaries for the screen.

	if (x < 5)	{x=+5;}
	if (y < 5)	{y+=5;}
	if (x > SCREEN_W-10){x-=5;}
	if (y > SCREEN_H-10){y-=5;}

}

bool pawn::hitWall(int x2, int y2, int w, int h)//This does not work.
{
	if ((x > x2 + w - 1) ||
		(y > y2 + h - 1) || 
		(x2 > x + spriteSizeX - 1) || 
		(y2 > y + spriteSizeY - 1))   
	{

		return false;
	}
	return true;


}