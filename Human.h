#ifndef __HUMAN__H
#define __HUMAN__H
#include "Player.h"
#include "Potion.h"

class Human: public Player {
    public:
        Human();
        void gainGold(int gain) override; //Adds gain to the Player’s amount of gold
        void applyPotion(Potion &pot) override; //Depending on the type of potion, modifies the Player’s atk or def or hp (either + or - effect)
        void resetAtkDef() override; //Resets the Player’s atk to 20 and def to 20
	void updateinfo() override;
};

#endif
