#ifndef __Cell__H
#define __Cell__H
#include <string>
#include <vector>
#include "CellContent.h"
#include "Subject.h"

class Cell: public Subject {
  private:
    std::vector<Cell*> neighbours; 
    CellContent *content = nullptr; 
    int x;
    int y;
    CellType type;
    bool counted = false;  //Has the Cell been added to a Chamber yet? false = not in a Chamber, true = in a Chamber

  public:
    std::string getContentDisplay();
    bool isCounted();  
    void setcontent(CellContent* t);
    void setCounted(bool b);  
    Cell(int x, int y, CellType t);
    void attach(Cell *c);
    void removeContent();
    bool emptycheck();
    int getX() const;
    int getY() const;
    CellType getType() const;
    void RandomAct();
    void NewTurn();
    void Protect();


    friend class Enemy;
    friend class Dragon;
    friend class Merchant;
    friend class DragonH;
    friend class Player;
    friend class Decorator;
    ~Cell();    
};

#endif
