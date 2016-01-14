#include "fileLoader.h"


fileLoader::fileLoader(int &LevelNumber)
{
	std::string LevelName;//The filename will be contained in here.
	
	//Each case will provide a different text file. so depending on the integer passed in we will load a different level.
	switch (LevelNumber)
	{
	case 0:
		LevelName = "test.txt";
		break;
	case 1:
		LevelName = "leveltwo.txt";
		break;
	case 2:
		LevelName = "levelthree.txt";
		break;
	case 3: 
		break;

	}

	//The next few lines are file reading commands from the iostream and fstrea functions.
	fileInputs.open(LevelName);
	if (fileInputs.fail())//If this fails then we get an error message.
	{
		std::cerr<<"Failed to load Level file"<<std::endl;
		exit(1);
	}
	while (!fileInputs.eof())//The following commands will repeat until we reach the end of the file.
	{
		fileInputs>>line;//Every line will be put into our sting aptly named line.
		lineVec.push_back(line);//Then we put it into a vector so we can easily use it in a for loop.
	}

	//This for loop will repeat for every object in our vector. 
	//Basically its taking every object with two spaces between it and putting it into a data type.
	//Specifically the object within our struct.
	for (int i=0; i < lineVec.size(); i+=6)
	{
		objFromFile tempObj;
		tempObj.ID = lineVec[i];
		tempObj.x = atoi(lineVec[i+1].c_str());//I'm converting the strings into integers. Because my command only reads strings.
		tempObj.y = atoi(lineVec[i+2].c_str());
		tempObj.w = atoi(lineVec[i+3].c_str());
		tempObj.h = atoi(lineVec[i+4].c_str());
		if (tempObj.ID == "p")//This will only execute if the ID contains the 'p' char. This means only objects that identify as this type will be checked for an extra value.
		{
			tempObj.d = lineVec[i+5];
			if (tempObj.d == "h")
			{
				tempObj.binary = true;//These are alues for the enemy objects. If its true they move horizontally if false they move vertically.
			}
			else
			{
				tempObj.binary = false;
			}
		}
		//After all this they are pushed into a vector of objects ready for me to print them to the level.
		objList.push_back(tempObj);

	}
	//Finally we close the file because we don't need to use it.
	fileInputs.close();
}


fileLoader::~fileLoader(void)
{
}



int fileLoader::numberOfObjects()
{
	//We return vector sizes for our main loop.
	return objList.size();
}

objFromFile fileLoader::giveparams(int objNumb)
{
	//We return objects for debugging reasons.
	return objList[objNumb];

}