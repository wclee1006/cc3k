#include "Goblin.h"
#include "Player.h"
#include "Cell.h"

void Goblin::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "N"});
}

Goblin::Goblin(int hp, int atk, int def): Enemy{hp, atk, def} {}

void Goblin::attacked(CellContent &attacker) {
	if (!dead) {
		attacker.attacksOn(*this);
	}
}

void Goblin::attacksOn(Player &player) {
	acted = true;
	player.attackedBy(atk);
}

std::string Goblin::getDisplay() const {
	if (dead) return "";
	return "N";
}
