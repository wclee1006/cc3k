#include "DragonH.h"
#include "Cell.h"
#include "Player.h"
#include "Dragon.h"

void DragonH::updateinfo() {
  if (bSuit) {
    curr->setInfo(Info{curr->getX(), curr->getY(),
	  curr->getType(), "B"});
  } else {
    curr->setInfo(Info{curr->getX(), curr->getY(),
	  curr->getType(), "G"});
  }
}

DragonH::DragonH(int value, Dragon *dragon, bool bSuit): Treasure{value},
	dragon(dragon), bSuit{bSuit} {}

void DragonH::act(ActionType type) {
	if (type == ActionType::Protect) {
		for (auto &neighbourCell: curr->neighbours) {
			if (neighbourCell->content) {
				neighbourCell->content->findDragon(this);
			}
		}
	} else if (type == ActionType::EnemyAct && dragon) {
		for (auto &neighbourCell: curr->neighbours) {
			if (neighbourCell->content) {
				neighbourCell->content->attacked(*this);
			}
		}	
	}
}

void DragonH::attacksOn(Player& player) {
	if (dragon) {
		dragon->protectHoard();
	}
}

bool DragonH::canMoveOn(Player &player) {
	if (dragon) {
		return false;
	} else {
		if (bSuit) {
			player.hasSuit();
		} else {
			player.gainGold(value);
		}
		return true;
	}
}

void DragonH::dragonIsDead() {
	dragon = nullptr;
}

void DragonH::setDragon(Dragon *dragon) {
	this->dragon = dragon;
}
