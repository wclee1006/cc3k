#ifndef _DECORATOR_H
#define _DECORATOR_H

#include "Enemy.h"

class Cell;

class Decorator: public Enemy {
public:
	void LinkCurr(Cell *current) override;
protected:
	Enemy *enemy;

	Decorator(Enemy *enemy);

	// calls act on Enemy
	void act(ActionType type) override;

	// calls attacked on Enemy
	void attacked(CellContent &attacker) override;

	bool isDead() override;

	void newTurn() override;

	bool hasActed() override;

	void setActed(bool act) override;

	virtual ~Decorator();
};

#endif
