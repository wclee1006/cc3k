#include "Phoenix.h"
#include "Player.h"
#include "Cell.h"

void Phoenix::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "X"});
}

Phoenix::Phoenix(int hp, int atk, int def): Enemy{hp, atk, def} {}

void Phoenix::attacked(CellContent &attacker) {
	if (!dead) {
		attacker.attacksOn(*this);
	}
}

void Phoenix::attacksOn(Player &player) {
	acted = true;
	player.attackedBy(atk);
}

std::string Phoenix::getDisplay() const {
	if (dead) return "";
	return "X";
}
