#ifndef _DRAGON_H
#define _DRAGON_H

#include "Enemy.h"

class DragonH;

class Dragon: public Enemy {
	DragonH *dragonH;

	// called by dragonH when PLayer is near DragonH
	void protectHoard();

	// What the dragon does each turn. Essentially does nothing.
	void act(ActionType type) override;

	// tells attacker it is attacking this Dragon
	void attacked(CellContent &attacker) override;

	// attacks the Player
	void attacksOn(Player &player) override;

	// tells dragonH if it is killed
	int attackedBy(int atk) override;

	// returns "D"
	std::string getDisplay() const override;

	// attaches the dragon to its Hoard
	void findDragon(DragonH *dragonH);
public:
	Dragon(int hp = 150, int atk = 20, int def = 20, DragonH *dragonH = nullptr);

	void setDragonH(DragonH *dragonH);

	friend class DragonH;

	void updateinfo() override;
};

#endif
