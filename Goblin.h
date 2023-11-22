#ifndef _GOBLIN_H
#define _GOBLIN_H

#include "Enemy.h"

class Goblin: public Enemy {
public:
	Goblin(int hp = 70, int atk = 5, int def = 10);
	void updateinfo() override;
private:
	// tells attacker it is attacking this Goblin
	void attacked(CellContent &attacker) override;

	// attacks the Player
	void attacksOn(Player &player) override;

	// returns "G"
	std::string getDisplay() const override;

};

#endif
