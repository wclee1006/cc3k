#include "BoostAtk.h"
#include "Player.h"
#include "Cell.h"

// see BoostAtk.h for documentation
bool BoostAtk::recognized = false;

void BoostAtk::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "P"});
}

bool BoostAtk::isRecognized() {
	return recognized;
}

void BoostAtk::setRecognized(bool rec) {
	recognized = rec;
}

BoostAtk::BoostAtk(int effect): Potion{effect, AffectType::Atk} {}

std::string BoostAtk::getDisplay() const {
	if (recognized) {
		return "BA";
	} else {
		return "P";
	}
}

void BoostAtk::usedBy(Player &player) {
	recognized = true;
	player.applyPotion(*this);

	Info i{curr->getX(), curr->getY(), curr->getType(), ""};
	curr->setInfo(i);
	curr->notifyObservers();
}
