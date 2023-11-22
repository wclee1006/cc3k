#ifndef _COMPASS_H
#define _COMPASS_H

#include "Decorator.h"

class Stair;

class Compass: public Decorator {
public:
	Compass(Stair *stair, Enemy *enemy = nullptr);

	void setStair(Stair *stair);

	void updateinfo() override;
private:
	Stair *stair;

	// only returns true if enemy is dead
	bool canMoveOn(Player &player) override;

	// returns "C" if Enemy is dead
	// else returns enemy->getDisplay()
	std::string getDisplay() const override;
};

#endif
