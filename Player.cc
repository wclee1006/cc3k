#include "Player.h"
#include "Cell.h"
#include "Enemy.h"
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>

void Player::updateinfo() {}

bool Player::Isitonstair() {return onStair;}

bool Player::getisDead() {return isDead;}

int Player::getgold() {
    return gold;
}

std::string Player::getrace() {
    return race;
}

std::string Player::getaction() {
    return action;
}

Player::Player() {
}

Player::~Player() {
}

void Player::newTurn() {
    action = "";
}

void Player::move(Direction dir) {
    bool hasMoved = false;

    int x = curr->getX();
    int y = curr->getY();
    int destx = x;
    int desty = y;
    
    if (dir == Direction::N) {
        desty -= 1;
        action = "PC moves North";
    }
    else if (dir == Direction::NW) {
        desty -= 1;
        destx -= 1; 
        action = "PC moves Northwest";
    }
    else if (dir == Direction::NE) {
        desty -= 1;
        destx += 1; 
        action = "PC moves Northeast";
    }
    else if (dir == Direction::S) {
        desty += 1;
        action = "PC moves South";
    }
    else if (dir == Direction::SW) {
        desty += 1;
        destx -= 1; 
        action = "PC moves Southwest";
    }
    else if (dir == Direction::SE) {
        desty += 1;
        destx += 1; 
        action = "PC moves Southeast";
    }
    else if (dir == Direction::W) {
        destx -= 1;
        action = "PC moves West";
    }
    else { //E
        destx += 1;
        action = "PC moves East";
    }
    
    for (auto &n: curr->neighbours) {
        if ((n->getX() == destx) && (n->getY() == desty)) { //if we have found the destination cell
            CellType c = n->type;
            if (((c == CellType::Passageway) || (c == CellType::Door) || (c == CellType::Floor)) && ((!n->content) || (n->content->canMoveOn(*this)))) {
                hasMoved = true;

                if (onStair == true) {
			if (n->content->getDisplay() == "\\"){
				action += " and descends to the next floor on the staircase with the help of their trusty compass";
			}
			else {
				action += " and happens upon a hidden staircase, and decides to take it to the next floor";
			}
			break;
		}

                if (bSuit == true) {
                    action += " and picks up the legendary Barrier Suit";
                }
                
                if (compass == true) {
                    action += " and picks up this floor's compass";
                }
                
                delete n->content;
                n->content = curr->content;
                curr->content = nullptr;
		
		Info i{curr->x, curr->y, curr->type, ""};
		curr->setInfo(i);		
		curr->notifyObservers();
                curr = n;
                
                for (auto &m: curr->neighbours) { //looking at the ngihbours of the new cell that the player moved to
                    //if any of the neighbour cells to curr contains a potion, do:

		    // m->contetn might be nullptr
		    if (m->content == nullptr) {continue;}
		    
                    if ((m->content->getDisplay() == "P") || (m->content->getDisplay() == "PH") || (m->content->getDisplay() == "RH") || (m->content->getDisplay() == "WA") || (m->content->getDisplay() == "WD") || (m->content->getDisplay() == "BA") || (m->content->getDisplay() == "BD")) {
                        action += " and sees a";
                        if (m->content->getDisplay() == "P") {
                            action += "n unknown potion";
                        }
                        else {
                            action += " ";
                            action += m->content->getDisplay();
                            action += " potion";
                        }
                    }
                }
                break;
            }
        }
    }
    
    if (hasMoved == false) {
        action = "PC is not able to move in the specified direction";
    }

    action += ".";

    Info i{curr->x, curr->y, curr->type, curr->content->getDisplay()};
    curr->setInfo(i);
    State s{race, gold, hp, atk, def, action};
    curr->setState(s);
    curr->notifyObservers();
}

void Player::use(Direction dir) {
	bool hasUsed = false;

	int x = curr->getX();
	int y = curr->getY();
	int destx = x;
	int desty = y;

	if (dir == Direction::N) {
		desty -= 1;
	}
	else if (dir == Direction::NW) {
		desty -= 1;
		destx -= 1; 
	}
	else if (dir == Direction::NE) {
		desty -= 1;
		destx += 1; 
	}
	else if (dir == Direction::S) {
		desty += 1;
	}
	else if (dir == Direction::SW) {
		desty += 1;
		destx -= 1; 
	}
	else if (dir == Direction::SE) {
		desty += 1;
		destx += 1; 
	}
	else if (dir == Direction::W) {
		destx -= 1;
	}
	else { //E
		destx += 1;
	}

	for (auto &n: curr->neighbours) {
		if ((n->getX() == destx) && (n->getY() == desty)) { //if we have found the destination cell
			//if any of the neighbour cells to curr contains a potion, do:

			// n->contetn might be nullptr                                                                     
			if (n->content == nullptr) {continue;}

			if ((n->content->getDisplay() == "P") || (n->content->getDisplay() == "PH") || (n->content->getDisplay() == "RH") || (n->content->getDisplay() == "WA") || (n->content->getDisplay() == "WD") || (n->content->getDisplay() == "BA") || (n->content->getDisplay() == "BD")) {
				action += "PC uses a";
				if (n->content->getDisplay() == "P") {
					action += "n unfamiliar potion which turns out to be a ";
					n->content->usedBy(*this);
					action += n->content->getDisplay();
					action += " potion";
				}
				else {
					action += " ";
					n->content->usedBy(*this);
					action += n->content->getDisplay();
					action += " potion";
				}
				hasUsed = true;

				delete n->content;
				n->content = nullptr;
				break;
			}
		}
	}

	if (hasUsed == false) {
		action = "There is no potion in the specified direction";
	}

	action += ".";

	Info i{curr->x, curr->y, curr->type, curr->content->getDisplay()};
	curr->setInfo(i);
	State s{race, gold, hp, atk, def, action};
	curr->setState(s);
	curr->notifyObservers();
}

void Player::attack(Direction dir) {
    bool hasAttacked = false;
    std::string reset = "";
    
    int x = curr->getX();
    int y = curr->getY();
    int destx = x;
    int desty = y;
    
    if (dir == Direction::N) {
        desty -= 1;
    }
    else if (dir == Direction::NW) {
        desty -= 1;
        destx -= 1; 
    }
    else if (dir == Direction::NE) {
        desty -= 1;
        destx += 1; 
    }
    else if (dir == Direction::S) {
        desty += 1;
    }
    else if (dir == Direction::SW) {
        desty += 1;
        destx -= 1; 
    }
    else if (dir == Direction::SE) {
        desty += 1;
        destx += 1; 
    }
    else if (dir == Direction::W) {
        destx -= 1;
    }
    else { //E
        destx += 1;
    }
    
    for (auto &n: curr->neighbours) {
        if ((n->getX() == destx) && (n->getY() == desty)) {

	    // n->contetn might be nullptr                                                                            
            if (n->content == nullptr) {continue;}
	    
            if ((n->content->getDisplay() == "V") || (n->content->getDisplay() == "W") || (n->content->getDisplay() == "N") || (n->content->getDisplay() == "D") || (n->content->getDisplay() == "X") || (n->content->getDisplay() == "T") || (n->content->getDisplay() == "M")) {
                std::string beforeCombat = n->content->getDisplay();
                int dmg = static_cast<Enemy *>(n->content)->hp;
                std::string temp = action;
                n->content->attacked(*this);
                action = temp;
                hasAttacked = true;
                dmg -= static_cast<Enemy *>(n->content)->hp;
                action = "PC deals ";
                action += std::to_string(dmg);
                action += " damage to ";
                action += beforeCombat;
                action += " (";
                action += std::to_string(static_cast<Enemy *>(n->content)->hp); //add in the HP the monster has left
                action += " HP).";
		std::cout << action  << std::endl;
                if (n->content->getDisplay() == "") {
                    action += ". ";
                    action += beforeCombat;
                    action += " is now dead.";
                }
                break;
	    }
	}
    }

    if (hasAttacked == false) {
	    action = "There is no enemy in the specified direction.";
    }

    Info i{curr->x, curr->y, curr->type, curr->content->getDisplay()};
    curr->setInfo(i);
    State s{race, gold, hp, atk, def, action};
    curr->setState(s);
    curr->notifyObservers();
}

void Player::attacked(CellContent &attacker) {
	if (!isDead) {
		attacker.attacksOn(*this);
	}
}

void Player::attacksOn(Enemy &enemy) {
    gainGold(enemy.attackedBy(atk));
}

int Player::attackedBy(int enemyAtk) {
	if (isDead == false) {
		int ran = rand() % 2;
		if (ran == 0) { //meaning the monster missed their attack
			action += " The enemy misses the attack, dealing 0 damage to PC.";

			Info i{curr->x, curr->y, curr->type, curr->content->getDisplay()};
			curr->setInfo(i);
			State s{race, gold, hp, atk, def, action};
			curr->setState(s);
			curr->notifyObservers();
			return 6;
		}

        int normalDmg = ceil((100/(100+(double)def))*(double)enemyAtk);
        action += " The enemy deals ";
        if (bSuit == false) { //if player has the barrier suit
            hp -= normalDmg;
            action += std::to_string(normalDmg);
        }
        else {
            hp -= ceil(normalDmg/2);
            action += std::to_string(ceil(normalDmg/2));
        }
        action += " damage to PC.";
        if (hp <= 0) {
            isDead = true;
        }
    }

    Info i{curr->x, curr->y, curr->type, curr->content->getDisplay()};
    curr->setInfo(i);
    State s{race, gold, hp, atk, def, action};
    curr->setState(s);
    curr->notifyObservers();

    return 6;
}

std::string Player::getDisplay() const {
    return "@";
}

void Player::isOnStair(bool onStair) {
	this->onStair = onStair;
}

void Player::hasSuit(bool bSuit) {
	this->bSuit = bSuit;
}

void Player::hasCompass(bool compass) {
	this->compass = compass;
}

void Player::actionfloor() {
	State old = curr->getState();
	curr->setState(State{old.race,old.gold,old.hp,old.atk,old.def, "Player move to the next floor!"});
}
