#ifndef __CHAMBER__H
#define __CHAMBER__H
#include "Cell.h"

class Chamber {
    std::vector<Cell*> cells;
    int size = 0;
 public:
    int getSize();
    Cell *getCell(int n);
    void addCell(Cell *cell);
    void populateChamberNP(std::string type);
    void moveEnemies();
};

#endif
