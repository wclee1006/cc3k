#include "Dragon.h"
#include "DragonH.h"
#include "Cell.h"
#include "Player.h"
#include <vector>
#include <cmath>

void Dragon::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "D"});
}

Dragon::Dragon(int hp, int atk, int def, DragonH *dragonH): Enemy{hp, atk, def}, 
	dragonH{dragonH} {}

void Dragon::setDragonH(DragonH *dragonH) {
	this->dragonH = dragonH;
}

void Dragon::protectHoard() {
	for (auto &neighbourCell: curr->neighbours) {
		if (neighbourCell->content) {
			neighbourCell->content->attacked(*this);
		}
	}
}

void Dragon::act(ActionType type) {}

void Dragon::attacked(CellContent &attacker) {
	if (!dead) {
		attacker.attacksOn(*this);
	}
}

void Dragon::attacksOn(Player &player) {
	acted = true;
	player.attackedBy(atk);
}

int Dragon::attackedBy(int atk) {
	int damage = ceil((100 / (100 + (double)def)) * (double)atk);

	if (damage < hp) {
		hp -= damage;
	} else {
		hp = 0;
		dead = true;
		dragonH->dragonIsDead();

		Info i{curr->getX(), curr->getY(), curr->getType(), ""};
		curr->setInfo(i);
		curr->notifyObservers();
	}
	return 0;
}

std::string Dragon::getDisplay() const {
	if (dead) return "";
	return "D";
}

void Dragon::findDragon(DragonH *dragonH) {
	this->dragonH = dragonH;
	dragonH->dragon = this;
}
