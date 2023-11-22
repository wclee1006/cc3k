#ifndef __FLOOR__H
#define __FLOOR__H
#include "TextDisplay.h"
#include "Cell.h"
#include "Chamber.h"
#include "Player.h"
#include "Info.h"

class Floor {
    std::vector<std::vector<Cell>> cells;
    std::vector<Chamber> chambers;
    int potionsCounter;
    int enemiesCounter;
    int compassCounter;
    bool BScounter;
    Player *p;
    bool restore = false;
    bool boostatk = false;
    bool boostdef = false;
    bool poison = false;
    bool woundatk = false;
    bool wounddef = false;

    void traverseChamber(Chamber &chamber, Cell *cell);
    void populateNP();
  
    public:
    	void actionfloor();
        void createChambers();
        //determines if the game started or not
        bool started();
	// let all the cells update their contents
	void UpdateView();
	void deleteplayer();
        void initializeBoard(std::string file, TextDisplay *td);
        void resetFloor();
	void setcontent(CellContent *con);
	void setDragonH(DragonH *con);
        void populateFloor(std::string playerRace, bool BSspawned);  
        bool playerMove(Direction dir);
        void playerAttack(Direction dir);
        void playerUse(Direction dir);
	int getScore();
	// enemy random move
	bool RandomAct();
};

#endif
