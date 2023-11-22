#include "Orc.h"
#include "Cell.h"

void Orc::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
        curr->getType(), "@"});
  curr->setState(State{"Orc", gold, hp, atk, def, "Player character has\
 spawned."});
}


Orc::Orc() {
    hp = 180;
    atk = 30;
    def = 25;
    race = "Orc";
}

void Orc::gainGold(int gain) {
    gold += ceil(0.5*gain);
    action += " and collects ";
    action += std::to_string((int)ceil(0.5*gain));
    action += " gold";
}

void Orc::applyPotion(Potion &pot) {
    int effect = pot.getEffect();
    if (pot.getAffect() == AffectType::HP) {
        hp += effect;
        if (hp <= 0) {
            hp = 1;
        }
        if (hp > 180) {
            hp = 180;
        }
    }
    else if (pot.getAffect() == AffectType::Def) {
        def += effect;
    }
    else {
        atk += effect;
    }
}

void Orc::resetAtkDef() {
    atk = 30;
    def = 25;
}
