#include <allegro.h>
//#include <cstdlib>
#include "pawn.h"
#include "map.h"
#include "enemy.h"
#include "menu.h"
#include "shuriken.h"
#include "wall.h"
#include "fileLoader.h"
#include <string>
#include<vector>
#include "goalItem.h"

//
//
//		Main game file.
//
//

//Prototypes
void init();
void deinit();
void buffManager(BITMAP *buff, pawn& player, map& area, std::vector<enemy*>&ninja, std::vector<wall*> &walls, std::vector<goalItem*>&lemons);
void UpdateObjects(pawn player, map area, std::vector<wall*> &w, std::vector<enemy*>&ninja, std::vector<goalItem*>&lemons);
void addToNukeCache(std::vector<shuriken*>&v, pawn player, BITMAP *buffer, std::vector<enemy*>&ninja, std::vector<wall*> &w, bool* playerhit);
void loadLevel(std::vector<enemy*>&ninja, std::vector<wall*> &walls, std::vector<goalItem*>&lemons);
void menuOpen(BITMAP *buff, bool *quitGame);

//These timer and tick methods are used for timer resons.
volatile int ticks = 0;
void ticker()
{
	ticks++;
}
END_OF_FUNCTION(ticker)

const int updates_per_second = 60;



//initialiastion is so I can enable important hardware features like monitor, keyboard, interface and even timing.
void init() 
{
	
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) 
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0)
	 {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
    install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
	
}

void deinit() 
{
	clear_keybuf();

}

void buffManager(BITMAP *buff, pawn& player, map& area, std::vector<enemy*>&ninja ,std::vector<wall*> &walls, std::vector<goalItem*>&lemons)
{
	//This function will paste all the objects in the scene to the buffer thus allowing for less lines in the main.
	area.mapScreen(buff);
	//jango.newScreen(buff);
	player.newScreen(buff);
	for (int i = 0; i<lemons.size(); i++)//We go through the vector and blit them indicidually to the buffer.
	{
		lemons[i]->newScreen(buff);
	}
	for (int i = 0; i<ninja.size(); i++)
	{
		ninja[i]->newScreen(buff);
	}
	for (int i=0; i<walls.size(); i++)
	{
		walls[i]->imageToScreen(buff);
	}

	
}

//This is an important function that changes the position of several moving objects. You'll see static objects like walls are not included.
void updateObjects(pawn& player, map& area, std::vector<wall*> &w, std::vector<enemy*>&ninja, std::vector<goalItem*>&lemons)
{
	for(int i=0; i<w.size();i++)
			{
	player.controls(w[i]->getx(),w[i]->gety(), w[i]->getw(), w[i]->geth());
	}
	for(int i=0; i<ninja.size(); i++)
	{
		ninja[i]->movement();
	}
	for(int i=0; i<lemons.size(); i++)
	{
		lemons[i]->collisionCheck(player.getx(), player.gety(), 16, 16);
	}
	
	//jango.movement();
}

//The menu function will open a menu and return a pointer that relates to the game quitting status
void menuOpen(BITMAP *buff, bool *quitGame)
{
	bool exitMenu = false;//i need a value to make sure the user wants to quit or not.
	menu buttons;//I initialise an instance of an object.

	do
	{
	switch (buttons.menuChoice(buff))
	{
	case 1://Play
		exitMenu = true;
		break;
	case 2://Provide information
		textprintf_ex(screen, font, 10, 10, makecol(255, 100, 200),
		    -1, "playTime");
		rest(10);
		exitMenu = true;
		break;
	case 4://Quit game.
	*quitGame = true;//This variale is returned to the main int and closes the program.
	exitMenu = true;
		break;
	case 0:
		break;
	}
	}while(exitMenu== false);

	//We repeat this function until we get an answer because menus function until an subject has been chosen. and we don't exit until a value is reached.

	
	
	
}

//This function handles several of the vectors for the projectile walls and the single player.
//we run through every shuriken, every wall and finaly the player to see when the shuriken should be deleted.
void addToNukeCache(std::vector<shuriken*>&v, pawn player, BITMAP *buffer, std::vector<enemy*>&ninja, std::vector<wall*> &w, bool *playerHit)
{
	for(int i=0; i<ninja.size(); i++)//This is where we set a loop up to check how many shurikens are in play. 
	{
		if(ninja[i]->sensePlayer(player.getx(), player.gety()) == true)
		{
			if (v.size() < 1)//to save memory we only allow one on screen.
			{
				v.push_back(new shuriken(ninja[i]->getx(), ninja[i]->gety(), player.getx(), player.gety()));
			}
		}
	}



	for(int i=0; i<v.size();i++)//This code then checks to see if the object is still alive(in case it goes of screen)or if its hit an object, and then we erase it form the vector.
	{
		for(int j =0; j<w.size(); j++)
		{
		if (v[i]->getIsAlive() == false||v[i]->collisionCheck(player.getx(), player.gety()) == true)//This checks with collision against the player.
		{
		
			v.erase(v.begin()+i);
			*playerHit = true;
			break;

		}
		else if(v[i]->collisionCheck(w[j]->getx(), w[j]->gety(), w[j]->getw(), w[j]->geth())==true)//Then this checks with collision against any walls.
		{
			v.erase(v.begin()+i);
			break;
		}
		else
		{
			v[i]->thrownStar(buffer, player.getx(), player.gety());//Otherwise the shuriken still flies through the air.
		}
	
		}

	}
	
	
}


//This function simply loads the data from the main fileLoader and then puts the objects in their designated vectors.
void loadLevel(int levelChoice, std::vector<enemy*>&ninja, std::vector<wall*> &walls, std::vector<goalItem*>&lemons)
{
	ninja.clear();
	walls.clear();
	lemons.clear();
	fileLoader level(levelChoice) ;
	for (int i=0; i<level.numberOfObjects(); i++)
	{
		if(level.giveparams(i).ID =="p")
		{
			ninja.push_back(new enemy(level.giveparams(i).x, level.giveparams(i).y, level.giveparams(i).binary));//We simple add a new instance, and plug in the settings with the constructor.
		}
		if(level.giveparams(i).ID =="o")//It all relates to the ID which I specify in the text document.
		{
			walls.push_back(new wall(level.giveparams(i).x, level.giveparams(i).y, level.giveparams(i).w,level.giveparams(i).h));
		}
		if(level.giveparams(i).ID == "y")
		{
			lemons.push_back(new goalItem(level.giveparams(i).x, level.giveparams(i).y));
		}
	}

}

int main()                                              
{
	bool quitting = false;//One boolean value to decide when the game should end.
	bool *quitGame= &quitting;//This is a pointer to the boolean so I can pass it through functions.
	pawn yupp;//This is the single player in the game. He is controlled by us.
	map jungle;//This is just an instance of the map so we can bit the ap tile to the screen.
	int level = 0; //The level you're playing on
	bool playerCondition; 
	bool *playerHit = &playerCondition;
	

	init();//This is the first thing we must call when we want to initialise our screen.

	//These are the important vector that hold the variable items in our level. They will vary depending on the level. Ergo vectors.
	std::vector<shuriken*> nuke;//Shurikens are the only item that depend on the number of enemies.
	std::vector<wall*> bounds;
	std::vector<enemy*> badGuys;
	std::vector<goalItem*> yellowGold;


	//Timer variables.
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

	//Allegro functions.
	srand(time(NULL));
	if( set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0))
	{
		allegro_message("Error");
		return 1;
	}


	//We must create one bitmap that we will blit our game ojects on. 
	BITMAP *buffer = create_bitmap(640,480);
	menuOpen(buffer, quitGame);//The menu will opsssssen for the user.
	loadLevel(level, badGuys, bounds, yellowGold);//The game will load the enemies and walls into our vectors.

		while(quitting ==false||!level==4)//The first while loop will initiate the main game. But will be skipped if the player has selected to quit in the first menu.
			//Then the while loop will check after ever frame if the state has changed.
		{
			while(ticks == 0)//These function are here for frame related reasons. They allow the game to be run at similar speeds on different computers. 
			{
				rest(1);
			}
			while(ticks>0)
			{
				int old_ticks = ticks;

				//We must clear our buffer after every frame otherwise we get the artifacts from the previous screens on our current frame.
				clear_bitmap(buffer);

				updateObjects(yupp, jungle, bounds, badGuys, yellowGold);//Then we update the objects to their new positions.
				buffManager(buffer,yupp,jungle,badGuys, bounds, yellowGold);//Then we blit them to the buffer..
				addToNukeCache(nuke, yupp, buffer, badGuys, bounds, playerHit);	//then we add the projectiles to the buffer in their new area
				textprintf_ex(buffer, font, mouse_x, mouse_y, makecol(122,106,3), -1, "x: %d, y:%d", mouse_x, mouse_y);
				if (key[KEY_ESC])//This if statement is here in case the player every wants to quit mid game.
				{
					menuOpen(buffer, quitGame);
				}
				if (playerCondition == true)
				{
					loadLevel(level, badGuys, bounds, yellowGold);
					yupp.setX(320);
						yupp.setY(200);
					playerCondition = false;
				}

				//This entire part is the win checking block. It will check to see if we've reached the winning scenario.
				int collectedItems=0;
				for (int i=0; i<yellowGold.size(); i++)
				{
					
					if(yellowGold[i]->collection()== true)
					{
						collectedItems++;
					}
					if (collectedItems == 3)
					{
						level++;
						
						yupp.setX(320);
						yupp.setY(200);
						loadLevel(level, badGuys, bounds, yellowGold);
						
						
					}
					
				}
				 textprintf_ex(buffer, font, 10, 10, makecol(255, 100, 200),
							 -1, "Total Gold: %d", collectedItems);//We print the players score here. E.g the amount of gold they've collected. They need 3 to beat the level.
				ticks--;
				if(old_ticks <= ticks)
					break;

			}
			blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);// Finally we blit the final buffer to the main screen for the player to enjoy.

		}
		


	return 0;
}
END_OF_MAIN();
