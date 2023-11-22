#include "Cell.h"

std::string Cell::getContentDisplay() {return content->getDisplay();}

bool Cell::isCounted() {return counted;}

void Cell::setcontent(CellContent *t) {
	delete content;
	content = t;
}

void Cell::setCounted(bool b) {counted = b;}

Cell::Cell(int x, int y, CellType t): x{x}, y{y}, type{t} {setInfo(Info{x,y,t,""});}

void Cell::attach(Cell *c) {
  neighbours.emplace_back(c);
}

void Cell::removeContent() {
  if (getInfo().cellContent == "@") {
    content = nullptr;
  }
  Info now {x, y, type, ""};
  setInfo(now);
  delete content;
  content = nullptr;
}

bool Cell::emptycheck() {
  if (content == nullptr) {return true;}
  else {return false;}
}

int Cell::getX() const {return x;}

int Cell::getY() const {return y;}

CellType Cell::getType() const {return type;}

Cell::~Cell() {
    delete content;
}
void Cell::RandomAct() {
  if (content != nullptr) { 
    content->act(ActionType::EnemyAct);
  }
}

void Cell::NewTurn() {
  if (content != nullptr) {
    content->newTurn();
  }
}

void Cell::Protect() {
  if (content != nullptr) {
    content->act(ActionType::Protect);
  }
}

