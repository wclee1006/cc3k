#ifndef _DRAGONH_H
#define _DRAGONH_H

#include "Treasure.h"

class Dragon;

class DragonH : public Treasure {
	Dragon *dragon;
	bool bSuit;

	// called by Dragon when it is dead.
	void dragonIsDead();

	// if type is Protect, find a dragon to protect this
	void act(ActionType type);

	// can only move on if dragon is dead
	bool canMoveOn(Player &player) override;

	void attacksOn(Player &player) override;
public:
	DragonH(int value = 6, Dragon *dragon = nullptr, bool bSuit = false);

	void setDragon(Dragon *dragon);

	friend class Dragon;

	void updateinfo() override;
};

#endif
