#include "shuriken.h"
#include <cmath>




shuriken::shuriken(float ninjax, float ninjay, float enemyX, float enemyY)
{
//We initialise the start and end position because the line equation I am using relys on it. y=mx+c	

	startX = ninjax-16; //The 16 relates to the correction I need to put because allegro blits the bitmap to the top left of the sprite rather than the centre. Which leaves us with a slight error.
		startY = ninjay-16;
		endX = enemyX-16;
		endY = enemyY;
		x = startX;
		isAlive = true;
		float cosattak = acos(y/x);

		/*cosattak= cosattak*(180/3.14159265359);
	if (cosattak < 10)
	{
		speed = 0.2;
	}
	else
	{
		speed = 3;
	}*/
	
}


shuriken::~shuriken(void)
{
	
}

BITMAP shuriken::thrownStar(BITMAP * buff, int x2, int y2)
{
	sprite = load_bitmap("shuriken.bmp", NULL);
	


	if (isAlive == true)
	{

		float dx = endX - startX;
		float dy = endY - startY;
		//This equation gets us a new position relating to the players posiiton and the enemys positoin and places the shuriken along a path between the two.
		y = startY + dy * (x - startX) / dx;
		masked_blit(sprite, buff,0,0,x,y,sprite->w, sprite->h);

		if (endX>startX)//Then depending on the direction we change whether its incrementing or decrementing.(left or right).
		{
			x+= speed;
		}
		else
		{
			x-=speed;
		}

		if (dx==0|| x >640|| y >480|| x<0||y<0)
		{
			isAlive = false;//If it goes off screen we erase it.

		}		

	}
	destroy_bitmap(sprite);//Then we destroy the bitmap to avoid memory leaks.
	return *buff;
	
}

bool shuriken::getIsAlive()
{
	return isAlive;//We tell the mian loop that the shuriken is dead so it can be erased from the vector in another class.
}

bool shuriken::collisionCheck(int x2, int y2, int w, int h)
{//If it collides with anything else we erase it).
	 if ((x > x2+w - 1) || 
        (y > y2 + h - 1) ||
		(x2 > x + 31 - 1) || 
        (y2> y + 28  - 1))  
	 {
		 return false;
	 }
	 else{
		 return true;
}
}