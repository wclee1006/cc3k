#include "BoostDef.h"
#include "Player.h"
#include "Cell.h"

// see BoostDef.h for documentation
bool BoostDef::recognized = false;

void BoostDef::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "P"});
}

bool BoostDef::isRecognized() {
	return recognized;
}

void BoostDef::setRecognized(bool rec){
	recognized = rec;
}

BoostDef::BoostDef(int effect): Potion{effect, AffectType::Def} {}

std::string BoostDef::getDisplay() const {
	if (recognized) {
		return "BD";
	} else {
		return "P";
	}
}

void BoostDef::usedBy(Player &player) {
	recognized = true;
	player.applyPotion(*this);

	Info i{curr->getX(), curr->getY(), curr->getType(), ""};
	curr->setInfo(i);
	curr->notifyObservers();
}
