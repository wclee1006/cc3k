#include "Board.h"
#include <cstdlib>

void Board::changefloor(int whichF) {
  floorCounter = whichF;
  t.updateFloor(whichF);
}

Board::Board(std::string file) {
  floorForBS = rand() % 5;
  floorCounter = 0;
  f.initializeBoard(file, &this->t);
  f.createChambers();
  if (!f.started()) {
    std::string race;
    std::cout << "Please enter h, e, d or o to decide your race." << std::endl;
    while(std::cin >> race) {
      if ((race == "h") || (race == "e") || (race == "d") || (race == "o")) {
	if (floorForBS == 0) {
	  f.populateFloor(race, true);
	} else {
	  f.populateFloor(race, false);
	}	
	return;
      }
      std::cout << "Please enter h, e, d or o to decide your race." << std::endl;
    }
  }
}

void Board::restart() {
  floorForBS = rand() % 5;
  floorCounter = 0;
  t.clear();
  t.firstFloor();
  f.resetFloor();
  f.deleteplayer();
  std::string race;
  std::cout << "Please enter h, e, d or o to decide your race." << std::endl;
  while(std::cin >> race) {
    if ((race == "h") || (race == "e") || (race == "d") || (race == "o")) {
      if (floorForBS == 0) {
	f.populateFloor(race, true);
      } else {
	f.populateFloor(race, false);
      }
      updateView();
      return;
    }
    std::cout << "Please enter h, e, d or o to decide your race." << std::endl;
  }
}

bool Board::playerMove(Direction dir) {
  if (f.playerMove(dir)) {
    ++floorCounter;
    if (floorCounter == 5) {return true;}
    f.resetFloor();
    t.updateFloor(floorCounter);
    if (floorForBS == floorCounter) {
      f.populateFloor("", true);
      f.actionfloor();
    } else {
      f.populateFloor("", false);
      f.actionfloor();
    }
  }
  updateView();
  return false;
}

void Board::playerAttack(Direction dir) {f.playerAttack(dir);}

void Board::playerUse(Direction dir) {f.playerUse(dir);}

void Board::updateView() {f.UpdateView();}

int Board::getScore() {
  return f.getScore();
}

bool Board::RandomAct() {return f.RandomAct();}


std::ostream &operator<<(std::ostream &out, const Board &b) {
  out << b.t;
  return out;
}
