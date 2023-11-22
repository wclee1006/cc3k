#include "Human.h"
#include "Cell.h"
#include <iostream>
Human::Human() {
    hp = 140;
    atk = 20;
    def = 20;
    race = "Human";
}

void Human::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "@"});
  curr->setState(State{"Human", gold, hp, atk, def, "Player character has spawned."});
}

void Human::gainGold(int gain) {
    gold += gain;
    action += " and collects ";
    action += std::to_string(gain);
    action += " gold";
}

void Human::applyPotion(Potion &pot) {
    //check if it would reduce player to less than 1 HP
    int effect = pot.getEffect();
    if (pot.getAffect() == AffectType::HP) {
        hp += effect;
        if (hp <= 0) {
            hp = 1;
        }
        if (hp > 140) {
            hp = 140;
        }
    }
    else if (pot.getAffect() == AffectType::Def) {
        def += effect;
    }
    else {
        atk += effect;
    }
}

void Human::resetAtkDef() {
    atk = 20;
    def = 20;
}
