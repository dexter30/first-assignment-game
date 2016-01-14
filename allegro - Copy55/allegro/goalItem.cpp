#include "goalItem.h"


goalItem::goalItem(int xi, int yi)
{//We initialise the values
	x = xi;
	y = yi;
	isCollected = false;
	bell = load_sample("bell.wav");
	soundMade = false;
	
}


goalItem::~goalItem(void)
{
}

BITMAP goalItem::newScreen(BITMAP *buff)
{//WE blit it to the screen if it hasn't been collected.
	sprite = load_bitmap("lemon.bmp", NULL);
	if (isCollected == false)
	{
	masked_blit(sprite, buff, 0, 0, x, y,sprite->w, sprite->h);
	}
	destroy_bitmap(sprite);
	
	return *buff;
}

bool goalItem::collisionCheck(int x2, int y2, int w, int h)
{//We return the value depending on whether or not the player has collided.
	if ((x > x2+16 - 1) || 
        (y > y2 + 32 - 1) ||
		(x2 > x + 16 - 1) || 
        (y2> y + 9  - 1))  
	 {
		 return false;
	 }
	 else{
		 isCollected = true;
		 if (soundMade == false)
		 {
		 soundMade = true;
		 int sound = play_sample(bell, 250,0, 1000, 0);
		 }
		 return true;
		 
}
}

bool goalItem::collection()
{
	return isCollected;
}