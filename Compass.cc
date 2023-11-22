#include "Compass.h"
#include "Player.h"
#include "Stair.h"
#include "Cell.h"

void Compass::updateinfo() {
  if (enemy->isDead() || !enemy) {
    curr->setInfo(Info{curr->getX(), curr->getY(),
          curr->getType(), "C"});
  } else {
    curr->setInfo(Info{curr->getX(), curr->getY(),
	  curr->getType(), enemy->getDisplay()});
  }
}

Compass::Compass(Stair *stair, Enemy *enemy): Decorator{enemy},
	stair{stair} {}

bool Compass::canMoveOn(Player &player) {
	if (!enemy || enemy->isDead()) {
		stair->isViewable(true);
		return true;
	} else {
		return false;
	}
}

std::string Compass::getDisplay() const {
	if (!enemy || enemy->isDead()) {
		return "C";
	} else {
		return enemy->getDisplay();
	}
}
