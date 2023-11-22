#ifndef __Character__H
#define __Character__H
#include "CellContent.h"

//superclass for Playable and Enemies (because they all share HP, ATK, DEF)

class Character: public CellContent {
  protected:
    int hp;
    int atk;
    int def;

 public:
    int gethp();
    int getatk();
    int getdef();

    // called by the attacker to pass in damage
    // intended for defender to use any defensive mechanism
    // e.g. BarrierSuit
    virtual int attackedBy(int atk) = 0;

    virtual ~Character();  
    explicit
    Character(int hp = 0, int atk = 0, int def = 0);
};

#endif
