#include "menu.h"


menu::menu(void)
{
	//We specify the position of every button on the screen.
	playButtYPos = 20;
	infoButtYPos = 90;
	optButtYPos = 160;
	exitButtYPos = 230;
	menuMusic = load_midi("jingle.mid");

	//The chosen option is defualted to 0 so the menu loop knows when to repeat.
	chosenOpt = 0;
}


menu::~menu(void)
{

}

int menu::menuChoice(BITMAP *buff)//This is the funciton that will display th emenu.
{
	bool lightedButton;
	chosenOpt = 0;
	//We load in the BMP's here.
	playButton = load_bitmap("playbutton.bmp", NULL);
	infoButton = load_bitmap("infobutton.bmp", NULL);
	//optionsButton = load_bitmap("optbutton.bmp", NULL);
	exitButton = load_bitmap("exitbutton.bmp", NULL);
	mouseIcon = load_bitmap("mouseIcon.bmp", NULL);
	instructions = load_bitmap("insstructions.bmp", NULL);
	play_midi(menuMusic, 1);
	while(chosenOpt ==0)
	{
		clear_bitmap(buff);

		//This area checks which icon the user is hovering over. They all have different values so 4 conditions are checked.
		if (!(mouse_y > playButtYPos + playButton->h||
			playButtYPos > mouse_y)) 
		{rectfill(buff, 0, playButtYPos,640, 80, makecol(255,162,0)); lightedButt = 1;}

		else if (!(mouse_y > infoButtYPos + infoButton->h||
			infoButtYPos > mouse_y))
		{rectfill(buff, 0, infoButtYPos,640, 140, makecol(255,162,0)); lightedButt = 2;}

		else if (!(mouse_y > exitButtYPos + exitButton->h||
			exitButtYPos > mouse_y))
		{rectfill(buff, 0, exitButtYPos,640, 290, makecol(255,162,0)); lightedButt = 4;}
		else{lightedButt = 0;		}

		//These functions blit the icons to the screen.
		masked_blit(playButton, buff,0,0,SCREEN_W/2-(playButton->w/2),20,playButton->w, playButton->w);
		masked_blit(infoButton, buff,0,0,SCREEN_W/2-(playButton->w/2),90,playButton->w, playButton->w);
		//masked_blit(optionsButton, buff,0,0,SCREEN_W/2-(playButton->w/2),160,playButton->w, playButton->w);
		masked_blit(exitButton, buff,0,0,SCREEN_W/2-(playButton->w/2),230,playButton->w, playButton->w);
		masked_blit(mouseIcon, buff,0,0,mouse_x,mouse_y,mouseIcon->w,mouseIcon->h);

		//Finally this case statement is activated after the user clicks the program then checks which condition the user has clicked. then returns the value to the main game.
		if (mouse_b & 1 )
		{
			switch (lightedButt)
			{


			case 1:
				chosenOpt = 1;
				return 1;
				break;
			case 2:
				chosenOpt = 0;
				while(mouse_b & 1)
				{
					while(!key[KEY_SPACE])
					{
				      blit(instructions, screen,0,0,0,0,640,420);
					}
				}
				
				break;
			case 3:
				chosenOpt = 3;
				break;
			case 4:
				chosenOpt = 4;
				
				break;
			

			}
		}

		//We blit the menu to the screne until we get an answer.

		blit(buff, screen, 0, 0, 0, 0, buff->w, buff->h);
	}

	//Then we destroy all unused bitmaps to avoid memory leaks.
		destroy_bitmap(playButton);
	destroy_bitmap(infoButton);
	//destroy_bitmap(optionsButton);
	destroy_bitmap(exitButton);
	destroy_bitmap(mouseIcon);
	stop_midi();
	play_midi(NULL, FALSE);
	return chosenOpt;
	
}


