#pragma once
#include <allegro.h>

//This going to be the base class for all the objects in my scene that will have movable positions. It will also be the main class for y protagonist.
class pawn
{

public:
	pawn(void);
	~pawn(void);
	

	//Setters and getters for the position
	void setX( float tempx );
	void setY( float tempy );
	float getx();
	float gety();
	//For controlling the character
	void controls(int x2,int y2, int w, int h);
	//For updating the character to the buffer
	virtual BITMAP newScreen(BITMAP *buff);
	void boundary();
	bool hitWall(int x2,int y2, int w, int h);

protected:
	//Position
	float x ;
	float y ;
	float speed;
	BITMAP *sprite;
	//variable to set whether or not it's printed to the screen
	bool onscreen;

	//The spriteSize is the size of the objects bitmap.
	int spriteSizeX;
	int spriteSizeY;
	int animationFrame;

};

