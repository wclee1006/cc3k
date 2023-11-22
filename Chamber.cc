#include "Chamber.h"

int Chamber::getSize() {return size;}

Cell *Chamber::getCell(int n) {return cells[n];}

void Chamber::addCell(Cell *cell) {
  ++size;
  cells.emplace_back(cell);
}
