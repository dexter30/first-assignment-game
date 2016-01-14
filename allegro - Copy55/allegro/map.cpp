#include "map.h"


map::map(void)
{
}


map::~map(void)
{
}

BITMAP map::mapScreen(BITMAP *buff)
{
	tile = load_bitmap("jungletile.bmp", NULL);//We load out blp to our bitmap data type
	for (int x=0; x<640; x+=40)//then we blit it to every square on the screen.
	{
		for (int y=0; y<480; y+=40)
		{
	masked_blit(tile, buff,0,0,x,y,tile->w, tile->h);
		}
	}
	destroy_bitmap(tile);// Then we destroy it once we're done to avoid emory leaks.
	return *buff;//This it is returned to be blitted to the screen.
}