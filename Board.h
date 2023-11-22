#ifndef __BOARD__H
#define __BOARD__H
#include <string>
#include "TextDisplay.h"
#include "Floor.h"
#include "Info.h"

class Board {
    int floorForBS; //Represents the number of the floor (from 0 to 4) that the Barrier Suit will be spawned on
    int floorCounter = 0; //Not sure if we should start this out as 1 or 0? 
    TextDisplay t; //View for MVC 
    Floor f; //The Floor we use for each level
    
    int randomizeFloorForBS(); // Returns a random number from 1 to 5 that represents the number of the floor that the Barrier Suit will be spawned on
   
    public:
        Board(std::string file);
	// once the "r" is called, restart would been called
	void restart();
        void populateBoard(std::string playerRace);
        bool playerMove(Direction dir);
        void playerAttack(Direction dir);
        void playerUse(Direction dir);
        void updateView();
	int getScore();
	//enemy random act
	bool RandomAct();
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
	void changefloor(int whichF);
};

#endif
