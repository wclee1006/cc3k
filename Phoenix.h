#ifndef _PHOENIX_H
#define _PHOENIX_H

#include "Enemy.h"

class Phoenix: public Enemy {
public:
	Phoenix(int hp = 50, int atk = 35, int def = 20);
	void updateinfo() override;
private:
	// tells attacker it is attacking this Phoenix
	void attacked(CellContent &attacker) override;

	// attacks the Player
	void attacksOn(Player &player) override;

	// returns "X"
	std::string getDisplay() const override;
};

#endif
