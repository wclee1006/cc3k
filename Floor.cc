#include "Floor.h"
#include <cstdlib>
#include "Human.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Orc.h"
#include "Small.h"
#include "Normal.h"
#include "Merchant.h"
#include "DragonH.h"
#include "Dragon.h"
#include "Restore.h"
#include "BoostAtk.h"
#include "BoostDef.h"
#include "Poison.h"
#include "WoundAtk.h"
#include "WoundDef.h"
#include "Werewolf.h"
#include "Troll.h"
#include "Goblin.h"
#include "Merchant.h"
#include "Vampire.h"
#include "Phoenix.h"
#include "Compass.h"
#include "Stair.h"
#include "MerchantH.h"
#include <iostream>

void Floor::UpdateView() {
  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) {
      cells[r][c].notifyObservers();
    }
  }
}

void Floor::traverseChamber(Chamber &chamber, Cell *cell) {
  chamber.addCell(cell);
  cell->setCounted(true);
  int r = cell->getY();
  int c = cell->getX();
  if ((cells[r-1][c]).getType() == CellType::VerWall) {
  } else if ((cells[r-1][c]).getType() == CellType::HorWall) {
  } else if ((cells[r-1][c]).getType() == CellType::Door) {
  } else {
    if (!(cells[r-1][c]).isCounted()) {
      traverseChamber(chamber, &cells[r-1][c]);
    }
  }

  if ((cells[r][c-1]).getType() == CellType::VerWall) {
  } else if ((cells[r][c-1]).getType() == CellType::HorWall) {
  } else if ((cells[r][c-1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r][c-1]).isCounted()) {
      traverseChamber(chamber, &cells[r][c-1]);
    }
  }

  if ((cells[r][c+1]).getType() == CellType::VerWall) {
  } else if ((cells[r][c+1]).getType() == CellType::HorWall) {
  } else if ((cells[r][c+1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r][c+1]).isCounted()) {
      traverseChamber(chamber, &cells[r][c+1]);
    }
  }

  if ((cells[r+1][c]).getType() == CellType::VerWall) {
  } else if ((cells[r+1][c]).getType() == CellType::HorWall) {
  } else if ((cells[r+1][c]).getType() == CellType::Door) {
  } else {
    if (!(cells[r+1][c]).isCounted()) {
      traverseChamber(chamber, &cells[r+1][c]);
    }
  }
  
  if ((cells[r-1][c-1]).getType() == CellType::VerWall) {
  } else if ((cells[r-1][c-1]).getType() == CellType::HorWall) {
  } else if ((cells[r-1][c-1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r-1][c-1]).isCounted()) {
      traverseChamber(chamber, &cells[r-1][c-1]);
    }
  }

  if ((cells[r-1][c+1]).getType() == CellType::VerWall) {
  } else if ((cells[r-1][c+1]).getType() == CellType::HorWall) {
  } else if ((cells[r-1][c+1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r-1][c+1]).isCounted()) {
      traverseChamber(chamber, &cells[r-1][c+1]);
    }
  }
  
  if ((cells[r+1][c-1]).getType() == CellType::VerWall) {
  } else if ((cells[r+1][c-1]).getType() == CellType::HorWall) {
  } else if ((cells[r+1][c-1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r+1][c-1]).isCounted()) {
      traverseChamber(chamber, &cells[r+1][c-1]);
    }
  }

  if ((cells[r+1][c+1]).getType() == CellType::VerWall) {
  } else if ((cells[r+1][c+1]).getType() == CellType::HorWall) {
  } else if ((cells[r+1][c+1]).getType() == CellType::Door) {
  } else {
    if (!(cells[r+1][c+1]).isCounted()) {
      traverseChamber(chamber, &cells[r+1][c+1]);
    }
  }
}


void Floor::createChambers() {
  for (int i = 0; i < 5; ++i) {
    Chamber cham;
    chambers.emplace_back(cham);
    bool finish = false;
    for (int r = 0; r < 25; ++r) {
      if (finish) {break;}
      for (int c = 0; c < 79; ++c) {
	if (finish) {break;}
	if ((cells[r][c]).getType() == CellType::Floor) {
	  if ((cells[r][c]).isCounted() == false) {
	    traverseChamber(chambers[i], &cells[r][c]);
	    finish = true;
	  }
	}
      }
    }
  }
}


void Floor::initializeBoard(std::string file, TextDisplay *td) {
  potionsCounter = 0;
  enemiesCounter = 0;
  compassCounter = 0;
  BScounter = false;
  bool hasStair = false;
  p = nullptr;
  for (int r = 0; r < 25; ++r) {
    std::vector<Cell> Row;
    cells.emplace_back(Row);
    for (int c = 0; c < 79; ++c) {
      Cell i{c, r, CellType::Nothing};
      cells[r].emplace_back(i);
    }
  }
  
  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) { 
      char thecell = file[r*79 + c];
      if (thecell == ' ') {
	Cell i{c, r, CellType::Nothing};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '|') {
	Cell i{c, r, CellType::VerWall};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '-') {
	Cell i{c, r, CellType::HorWall};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '#') {
	Cell i{c, r, CellType::Passageway};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '+') {
	Cell i{c, r, CellType::Door};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '.') {
	Cell i{c, r, CellType::Floor};
	cells[r][c] = i;
	cells[r][c].attachOb(td);
      } else if (thecell == '0') {
	potionsCounter += 1;
	Restore *con = new Restore;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '1') {
	potionsCounter += 1;
	BoostAtk *con = new BoostAtk;
	cells[r][c]= Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '2') {
	potionsCounter += 1;
	BoostDef *con = new BoostDef;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '3') {
	potionsCounter += 1;
	Poison *con = new Poison;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '4') {
	potionsCounter += 1;
	WoundAtk *con = new WoundAtk;
	cells[r][c] = {c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '5') {
	potionsCounter += 1;
	WoundDef *con = new WoundDef;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '6') {
	Normal *con = new Normal;
	cells[r][c] = Cell{c, r, CellType::Floor};	
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '7') {
	Small *con = new Small;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '8') {
	MerchantH *con = new MerchantH;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '9') {
	DragonH *con = new DragonH;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'V') {
	enemiesCounter += 1;
	Vampire *con = new Vampire;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'W') {
	enemiesCounter += 1;
	Werewolf *con = new Werewolf;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'N') {
	enemiesCounter += 1;
	Goblin *con = new Goblin;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'D') {
	enemiesCounter += 1;
	Dragon *con = new Dragon;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'X') {
	enemiesCounter += 1;
	Phoenix *con = new Phoenix;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'T') {
	enemiesCounter += 1;
	Troll *con = new Troll;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'M') {
	enemiesCounter += 1;
	Merchant *con = new Merchant;
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'C') {
	compassCounter += 1;
	Compass *con = new Compass{nullptr, nullptr};
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == 'B') {  
	BScounter = true;
	DragonH *con = new DragonH{6, nullptr, true};
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
      } else if (thecell == '\\') {
	Stair *con = new Stair{true};
	cells[r][c] = Cell{c, r, CellType::Floor};
        cells[r][c].attachOb(td);
        cells[r][c].setcontent(con);
        con->LinkCurr(&cells[r][c]);
        con->updateinfo();
	hasStair = true;
      } else if (thecell == '@') {
	cells[r][c] = Cell{c, r, CellType::Floor};
	Human *con = new Human;
	cells[r][c].attachOb(td);
	cells[r][c].setcontent(con);
	con->LinkCurr(&cells[r][c]);
	con->updateinfo();
	this->p = con;
      } 
    }
  }

  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) {
      if (r == 0) {
	cells[r][c].attach(&cells[r+1][c]);
	if (c == 0) {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r+1][c+1]);
	} else if (c == 78) {
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r+1][c-1]);
	} else {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r+1][c+1]);
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r+1][c-1]);
	}
      } else if (r == 24) {
	cells[r][c].attach(&cells[r-1][c]);
	if (c == 0) {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r-1][c+1]);
	} else if (c == 78) {
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r-1][c-1]);
	} else {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r-1][c+1]);
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r-1][c-1]);
	}
      } else {
	cells[r][c].attach(&cells[r-1][c]);
	cells[r][c].attach(&cells[r+1][c]);
	if (c == 0) {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r-1][c+1]);
	  cells[r][c].attach(&cells[r+1][c+1]);
	} else if (c == 78) {
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r-1][c-1]);
	  cells[r][c].attach(&cells[r+1][c-1]);
	} else {
	  cells[r][c].attach(&cells[r][c+1]);
	  cells[r][c].attach(&cells[r-1][c+1]);
	  cells[r][c].attach(&cells[r+1][c+1]);
	  cells[r][c].attach(&cells[r][c-1]);
	  cells[r][c].attach(&cells[r-1][c-1]);
	  cells[r][c].attach(&cells[r+1][c-1]);
	}
      }
    }
  }

  if (hasStair) {
    p->hasCompass(true);
  }

  
  //link drag and dragH
  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) {
      cells[r][c].Protect();
    }
  }
}


bool Floor::started() {
  if (this->p == nullptr) {
    return false;
  } else {
    return true;
  }
}

void Floor::resetFloor() {
  for (int i = 0; i < 25; ++i) {
    for (int j = 0; j < 79; ++j) {
      cells[i][j].removeContent();
    }
  }
  p->isOnStair(false);
}


void Floor::setcontent(CellContent *con) {
  while(true) {
    int which_cham = rand() % 5;
    int size = chambers[which_cham].getSize();
    int which_cell = rand() % size;
    Cell *thecell = chambers[which_cham].getCell(which_cell);
    int r = thecell->getY();
    int c = thecell->getX();
    if ((cells[r][c]).emptycheck()) {
      con->LinkCurr(&cells[r][c]);
      (cells[r][c]).setcontent(con);
      con->updateinfo();
      break;
    }
  }
}

void Floor::setDragonH(DragonH *con) {
  while (true) {
    int which_cham = rand() % 5;
    int size = chambers[which_cham].getSize();
    int which_cell = rand() % size;
    Cell *thecell = chambers[which_cham].getCell(which_cell);
    int r = thecell->getY();
    int c = thecell->getX();
    if ((cells[r][c]).emptycheck()) {
      con->LinkCurr(&cells[r][c]);
      (cells[r][c]).setcontent(con);
      con->updateinfo();
      Dragon *dra = new Dragon;
      con->setDragon(dra);
      while (true) {
	int which_dir = rand() % 8;
	if (which_dir == 0) {
	  if ((cells[r-1][c-1]).getType() == CellType::Floor) {
	    if ((cells[r-1][c-1]).emptycheck()) {
	      (cells[r-1][c-1]).setcontent(dra);
	      dra->LinkCurr(&cells[r-1][c-1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 1) {
	  if ((cells[r-1][c]).getType() == CellType::Floor) {
	    if ((cells[r-1][c]).emptycheck()){
	      (cells[r-1][c]).setcontent(dra);
	      dra->LinkCurr(&cells[r-1][c]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 2) {
	  if ((cells[r-1][c+1]).getType() == CellType::Floor) {
	    if ((cells[r-1][c+1]).emptycheck()){
	      (cells[r-1][c+1]).setcontent(dra);
	      dra->LinkCurr(&cells[r-1][c+1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 3) {
	  if ((cells[r][c-1]).getType() == CellType::Floor) {
	    if ((cells[r][c-1]).emptycheck()){
	      (cells[r][c-1]).setcontent(dra);
	      dra->LinkCurr(&cells[r][c-1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 4) {
	  if ((cells[r][c+1]).getType() == CellType::Floor) {
	    if ((cells[r][c+1]).emptycheck()){
	      (cells[r][c+1]).setcontent(dra);
	      dra->LinkCurr(&cells[r][c+1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 5) {
	  if ((cells[r+1][c-1]).getType() == CellType::Floor) {
	    if ((cells[r+1][c-1]).emptycheck()){
	      (cells[r+1][c-1]).setcontent(dra);
	      dra->LinkCurr(&cells[r+1][c-1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 6) {
	  if ((cells[r+1][c]).getType() == CellType::Floor) {
	    if ((cells[r+1][c]).emptycheck()){
	      (cells[r+1][c]).setcontent(dra);
	      dra->LinkCurr(&cells[r+1][c]);
	      dra->updateinfo();
	      break;
	    }
	  }
	} else if (which_dir == 7) {
	  if ((cells[r+1][c+1]).getType() == CellType::Floor) {
	    if ((cells[r+1][c+1]).emptycheck()){
	      (cells[r+1][c+1]).setcontent(dra);
	      dra->LinkCurr(&cells[r+1][c+1]);
	      dra->updateinfo();
	      break;
	    }
	  }
	}
      }
      break;
    }
  }
}


void Floor::populateFloor(std::string playerRace, bool BSspawned) {
  if (playerRace == "h") {
    p = new Human;
  } else if (playerRace == "e") {
    p = new Elf;
  } else if (playerRace == "d") {
    p = new Dwarf;
  } else if (playerRace == "o") {
    p = new Orc;
  } 
  //playerRace == "" represent e already have an player

  //player
  setcontent(p);
  
  //Stair
  Stair *stair = new Stair{false};
  setcontent(stair);

  //Potion
  for (int i = 0; i < 10; ++i) {
    int kind = rand() % 6;
    if (kind == 0) {
      Restore *con = new Restore;
      setcontent(con);
    } else if (kind == 1) {
      BoostAtk *con = new BoostAtk;
      setcontent(con);
    } else if (kind == 2) {
      BoostDef *con = new BoostDef;
      setcontent(con);
    } else if (kind == 3) {
      Poison *con = new Poison;
      setcontent(con);
    } else if (kind == 4) {
      WoundAtk *con = new WoundAtk;
      setcontent(con);
    } else {
      WoundDef *con = new WoundDef;
      setcontent(con);
    }
  }

  //Tresure
  for (int i = 0; i < 10; ++i) { 
    int kind = rand() % 8;
    if (kind < 5) {
      Normal *con = new Normal;
      setcontent(con);
    } else if (kind == 5) {
      DragonH *con = new DragonH;
      setDragonH(con);
    } else {
      Small *con = new Small;
      setcontent(con);
    }
  }

  //Barrier suit
  if (BSspawned) {
    DragonH *con = new DragonH{6,nullptr,true};
    setDragonH(con);
  }
  //enemies
  int compassnum = rand() % 20;
  for (int i = 0; i < 20; ++i) {
    if (i != compassnum) {
      int kind = rand() % 18;
      if (kind < 4) {
	Werewolf *con = new Werewolf;
	setcontent(con);
      } else if (kind < 7) {
	Vampire *con = new Vampire;
	setcontent(con);
      } else if (kind < 12) {
	Goblin *con = new Goblin;
	setcontent(con);
      } else if (kind < 14) {
	Troll *con = new Troll;
	setcontent(con);
      } else if (kind < 16) {
	Phoenix *con = new Phoenix;
	setcontent(con);
      } else if (kind < 18) {
	MerchantH *con = new MerchantH{4, new Merchant};
	setcontent(con);
      }
    } else if (i == compassnum) {
      int kind = rand() % 16;
      if (kind < 4) {
        Werewolf *con = new Werewolf;
	Compass *compass = new Compass{stair, con};
	setcontent(compass);
      } else if (kind < 7) {
        Vampire *con = new Vampire;
	Compass *compass = new Compass{stair, con};
	setcontent(compass);
      } else if (kind < 12) {
        Goblin *con = new Goblin;
	Compass *compass = new Compass{stair, con};
	setcontent(compass);
      } else if (kind < 14) {
        Troll *con = new Troll;
	Compass *compass = new Compass{stair, con};
	setcontent(compass);
      } else if (kind < 16) {
        Phoenix *con = new Phoenix;
	Compass *compass = new Compass{stair, con};
	setcontent(compass);
      }
    }
  }
}


bool Floor::playerMove(Direction dir) {
  p->move(dir);
  return p->Isitonstair();
}

void Floor::deleteplayer() {delete p;}

int Floor::getScore() {
  if (p->getrace() == "Human") {
    return p->getgold() * 1.5;
  }
  return p->getgold();
}

bool Floor::RandomAct() {
  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) {
      cells[r][c].RandomAct();
      if (p->getisDead()) {
	return true;
      }
    }
  }
  for (int r = 0; r < 25; ++r) {
    for (int c = 0; c < 79; ++c) {
      cells[r][c].NewTurn();
    }
  }
  return false;
}

void Floor::playerAttack(Direction dir) {
  p->attack(dir);
}

void Floor::playerUse(Direction dir) {
  p->use(dir);
}

void Floor::actionfloor() {
	p->actionfloor();
}
