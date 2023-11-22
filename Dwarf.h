#ifndef	__DWARF__H
#define	__DWARF__H
#include "Player.h"
#include "Potion.h"

class Dwarf: public Player {
    public:
        Dwarf();
        void gainGold(int gain) override; //Adds 2*gain to the Player’s amount of gold
        void applyPotion(Potion &pot) override; //Depending on the type of potion, modifies the Player’s atk or def or hp (either + or - effect)
        void resetAtkDef() override; //Resets the Player’s atk to 20 and def to 30
	void updateinfo() override;
};

#endif
