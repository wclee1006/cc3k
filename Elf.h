#ifndef	__ELF__H
#define	__ELF__H
#include "Player.h"
#include "Potion.h"

class Elf: public Player {
    public:
        Elf();
        void gainGold(int gain) override; //Adds gain to the Player’s amount of gold
        void applyPotion(Potion &pot) override; //Depending on the type of potion, modifies the Player’s atk or def or hp. (con't on next line)
        //However, if the effect of the potion is negative, applies the opposite of it instead. Basically all potion effects are positive
        void resetAtkDef() override; //Resets the Player’s atk to 30 and def to 10
	void updateinfo() override;
};

#endif
