#include "enemy.h"

enemy::enemy(int x1, int y1, bool whichway)
{
	x = x1;
	y = y1;
	//I need to get the enemy starting position so I can initiate movement along an origin point.
	startY = y1;
	startX = x1;
	//The boundaries are so enemy knows their area of vision.
	boundaries = 80;
	//sprite size is the size of the bitmap used. so the program knows how to properly blit the image.
	spriteSizeX = 32;
	spriteSizeY = 32;
	//Direction is important for the enemy so they know if they are going horizontally or vertically.
	direction = whichway;
}


enemy::~enemy(void)
{

}

bool enemy::sensePlayer(int x2, int y2)
{//When the player is near the enemy this function will return true.

	if ((x > x2 + boundaries - 1) || // is b1 on the right side of b2?
		(y > y2 + boundaries - 1) || // is b1 under b2?
		(x2 > x + boundaries - 1) || // is b2 on the right side of b1?
		(y2 > y + boundaries - 1))   // is b2 under b1?
	{
		return false;
	}
	else
	{
		return true;
	}

}

BITMAP enemy::newScreen(BITMAP *buff)
{//This function blits the enemy to the buffer that is pased in.
	sprite = load_bitmap("ninjasorta.bmp", NULL);

	masked_blit(sprite, buff,animationFrame,0,x-32,y-32,spriteSizeX, spriteSizeY);
	destroy_bitmap(sprite);
	return *buff;
}



void enemy::movement()
{
	//This function will contain commands that will dynamically move the enemy whenever called.

	if(x > startX+ 100 || y > startY + 100)
	{
		isMovingUp = true;
	}

	if (x < startX-50 || y < startY - 50){isMovingUp = false;}

	if (direction == true)
	{
		if(isMovingUp == false)//This increments sprite in the chosen direction the horizontal direction.
		{x+=speed;}
		else{x-=speed;}
	}
	else 
	{
		if(isMovingUp == false)//This increments sprite in the chosen direction the vertical direction.
		{y+=speed;}
		else{y-=speed;}
	}


}