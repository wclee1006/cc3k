#include "Enemy.h"
#include "Player.h"
#include "Cell.h"
#include <vector>
#include <cstdlib>
#include <cmath>

// see Enemy.h for documentation

Enemy::Enemy(int hp, int atk, int def, bool acted, bool dead): Character{hp, atk, def}, 
	acted{acted}, dead{dead} {}

bool Enemy::isDead() {
	return dead;
}

int Enemy::getHP() {
	return hp;
}

void Enemy::act(ActionType type) {

	if (type == ActionType::EnemyAct && !dead && !acted) {

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
			int destCount = possDest.size();

			if (destCount > 0) {
				int dest = 0;

				if (destCount > 1) {
					dest = rand() % (destCount - 1);
				}

				possDest[dest]->content = this;
				curr->content = nullptr;

				Cell *to = possDest[dest];
				Info i{to->getX(), to->getY(), to->getType(), to->content->getDisplay()};
				to->setInfo(i);
				to->notifyObservers();

				i = Info{curr->getX(), curr->getY(), curr->getType(), ""};
				curr->setInfo(i);
				curr->notifyObservers();

				curr = to;
			}
			acted = true;
		}
	}
}

int Enemy::attackedBy(int atk) {
	int damage = ceil((100 / (100 + (double)def)) * (double)atk);

	if (damage < hp) {
		hp -= damage;
		return 0;
	} else {
		hp = 0;
		dead = true;

		Info i{curr->getX(), curr->getY(), curr->getType(), curr->content->getDisplay()};
		curr->setInfo(i);
		curr->notifyObservers();
		return 1;
	}
}

void Enemy::newTurn() {
	acted = false;
}

bool Enemy::canMoveOn(Player &player) {
	if (dead) return true;
	return false;
}

bool Enemy::hasActed() {
	return acted;
}

void Enemy::setActed(bool act) {
	acted = act;
}

Enemy::~Enemy() {}
