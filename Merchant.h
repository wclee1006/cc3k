#ifndef _MERCHANT_H
#define _MERCHANT_H

#include "Enemy.h"

class Merchant: public Enemy {
	static bool hostile;

	// only attacks if hostile
	void act(ActionType type) override;

	// tells attacker it is attacking this Merchant
	void attacked(CellContent &attacker) override;

	// attacks the Player
	void attacksOn(Player &player) override;

	// calculates the damage gotten.
	// Also set hostile to true
	int attackedBy(int atk) override;

	// returns "M"
	std::string getDisplay() const override;

	bool isHostile();
	void setHostile(bool rec);

public:
	Merchant(int hp = 30, int atk = 70, int def = 5);
	void updateinfo() override;
};

#endif
