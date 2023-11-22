#ifndef	__ORC__H
#define	__ORC__H
#include "Player.h"
#include <cmath>
#include "Potion.h"

class Orc: public Player {
    public:
        Orc();
        void gainGold(int gain) override; //Adds 0.5*gain to the Player’s amount of gold
        void applyPotion(Potion &pot) override; //Depending on the type of potion, modifies the Player’s atk or def or hp (either + or - effect)
        void resetAtkDef() override; //Resets the Player’s atk to 30 and def to 25
	void updateinfo() override;
};

#endif
