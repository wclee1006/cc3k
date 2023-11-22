#include "Merchant.h"
#include "Player.h"
#include "Cell.h"
#include "MerchantH.h"
#include <cstdlib>
#include <cmath>

void Merchant::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "M"});
}

Merchant::Merchant(int hp, int atk, int def): Enemy{hp, atk, def} {}

bool Merchant::hostile = false;

void Merchant::act(ActionType type) {

	if (type == ActionType::EnemyAct && hostile && !dead && !acted) {

		// Attacks its neighbours
		for (auto &neighbourCell: curr->neighbours) {
			if (neighbourCell->content) {
				neighbourCell->content->attacked(*this);
			}
		}

		// If it didn't attack anything, move
		if (!acted) {
			// filters where it can move to
			std::vector<Cell *> possDest;

			for (auto &neighbourCell: curr->neighbours) {
				if (neighbourCell->type == CellType::Floor &&
						neighbourCell->content == nullptr) {
					possDest.emplace_back(neighbourCell);
				}
			}

			// randomize where to go
			int dest = rand() % (possDest.size() - 1);

			possDest[dest]->content = this;
			curr->content = nullptr;

			Cell *to = possDest[dest];
			Info i{to->getX(), to->getY(), to->getType(), to->content->getDisplay()};
			to->setInfo(i);
			to->notifyObservers();

			i = Info{curr->getX(), curr->getY(), curr->getType(), ""};
			curr->setInfo(i);
			curr->notifyObservers();

			curr = possDest[dest];

			acted = true;
		}
	}
}

void Merchant::attacked(CellContent &attacker) {
	if (!dead) {
		attacker.attacksOn(*this);
	}
}

void Merchant::attacksOn(Player &player) {
	acted = true;
	player.attackedBy(atk);
}

bool Merchant::isHostile() {
	return hostile;
}

void Merchant::setHostile(bool hostile) {
	this->hostile = hostile;
}

int Merchant::attackedBy(int atk) {
	hostile = true;
	int damage = ceil((100 / (100 + (double)def)) * (double)atk);

	if (damage < hp) {
		hp -= damage;
	} else {
		hp = 0;
		dead = true;

		MerchantH *merchantH = new MerchantH{};
		merchantH->setMerchant(this);
		curr->content = merchantH;

		CellContent *hoard = merchantH;
	
		Info i{curr->getX(), curr->getY(), curr->getType(), hoard->getDisplay()};
		curr->setInfo(i);
		curr->notifyObservers();
	}
	return 0;
}

std::string Merchant::getDisplay() const {
	if (dead) return "";
	return "M";
}
