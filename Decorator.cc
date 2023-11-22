#include "Decorator.h"
#include "Cell.h"

Decorator::Decorator(Enemy *enemy): Enemy{enemy->getHP(), 0, 0}, enemy{enemy} {}

void Decorator::act(ActionType type) {
	if (enemy) {
		hp = enemy->getHP();
		if (type == ActionType::EnemyAct && !(enemy->isDead()) && !(enemy->hasActed())) {

			// Attacks its neighbours
			for (auto &neighbourCell: curr->neighbours) {
				if (neighbourCell->content) {
					neighbourCell->content->attacked(*enemy);
				}
			}

			// If it didn't attack anything, move
			if (!(enemy->hasActed())) {
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
					enemy->LinkCurr(curr);
				}
				enemy->setActed(true);
			}
		}

	}
}

void Decorator::setActed(bool act) {
	enemy->setActed(act);
}

bool Decorator::isDead() {
	return enemy->isDead();
}

void Decorator::newTurn() {
	enemy->newTurn();
}

bool Decorator::hasActed() {
	return enemy->hasActed();
}

void Decorator::LinkCurr(Cell *current) {
	curr = current;
	enemy->LinkCurr(current);
}

void Decorator::attacked(CellContent &attacker) {
	if (enemy) {
		CellContent *content = enemy;
		content->attacked(attacker);
	}
	hp = enemy->getHP();
}

Decorator::~Decorator() {delete enemy;}
