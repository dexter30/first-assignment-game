#pragma once
#include <allegro.h>
class menu
{
public:
	menu(void);
	~menu(void);
	int menuChoice(BITMAP * buff);//This will do several things. But mainly it will display the meu to the user and return a integer value so the program knows what the user is selecting.
	


private:
	//The following are bitmaps for all the buttons.
	BITMAP * playButton;
	BITMAP * infoButton;
	//BITMAP * optionsButton;//I have omitted this one because of lack of reasons to use it.
	BITMAP * exitButton;
	BITMAP * mouseIcon;
	BITMAP * instructions;
	MIDI *menuMusic; 
	int playButtYPos, infoButtYPos, optButtYPos, exitButtYPos;//Y co ordinate of all the buttons.
	int chosenOpt ;//The integer the program returns.
	int lightedButt; //The variable that the user's mouse is hovering over.

};

