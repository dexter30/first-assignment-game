#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//This class basically just opens a file that contains the level information and loads it into the memory to be rendered in game.

struct objFromFile //This struct basically contains the information for every enemy, wall and goal object.
{
	std::string ID, d;
	int x, y, w, h;
	bool binary;
	//ID will hold a character so i can identify which object is which (enemy or wall?). X, Y, W and H are all values to hold position and size.
	//And the binary value is so i know which way the enemy is going. 
};



class fileLoader
{
public:
	fileLoader(int &levelNumber); //The constructor must contain a value so it knows which file ot load. (the file will vary depending on the level).
	~fileLoader(void);

	objFromFile giveparams(int objNumb);//This function will return a specified object
	int numberOfObjects();//This just returns the size of a vector that holds the objects so my forloops know how long to run for.
	
private:
	std::fstream fileInputs;//This stream will simple hold the stream of information coming in from a text file that I specify.
	std::vector <objFromFile> objList;//This vector will hold the objects that I read in.
	std::string line;//This string will temporarily hold the informaiton.
	std::vector <std::string> lineVec;//This vector will just hold each indivual line and its objects.
};

