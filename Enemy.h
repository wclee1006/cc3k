#ifndef __ENEMY__H
#define __ENEMY__H

#include "Character.h"

class Player;

class Enemy: public Character {
public:
	virtual ~Enemy() = 0;

	// Resets acted. Can be overridden to do other actions before
	// each turn by its subclasses.
	virtual void newTurn() override;

	virtual bool isDead();
	virtual bool hasActed();
	virtual void setActed(bool act);
	virtual int getHP();
	friend class Player;
	
protected:
	Enemy(int hp, int atk, int def, bool acted = false, bool dead = false);
	bool acted;
	bool dead;

	// the default behaviour of each enemy:
	// 1) Attacks its surrounding
	// 2) If that's successful, set acted to true and stop
	// 3) Else, randomize move based on surroundings and set acted to true
	void act(ActionType type) override;

	// called when Enemy is being attacked by atk. The default behaviour
	// is set dead to true and returns 1 if Enemy is killed (HP = 0)
	virtual int attackedBy(int atk) override;

	// if Enemy is dead, return true
	virtual bool canMoveOn(Player &player) override;
};





#endif
