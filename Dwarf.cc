#include "Dwarf.h"
#include "Cell.h"

void Dwarf::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
        curr->getType(), "@"});
  curr->setState(State{"Dwarf", gold, hp, atk, def, "Player character has spawned."});
}

  

Dwarf::Dwarf() {
    hp = 100;
    atk = 20;
    def = 30;
    race = "Dwarf";
}
void Dwarf::gainGold(int gain) {
    gold += 2*gain;
    action += " and collects ";
    action += std::to_string(2*gain);
    action += " gold";
}
void Dwarf::applyPotion(Potion &pot) {
    int effect = pot.getEffect();
    if (pot.getAffect() == AffectType::HP) {
        hp += effect;
        if (hp <= 0) {
            hp = 1;
        }
        if (hp > 100) {
            hp = 100;
        }
    }
    else if (pot.getAffect() == AffectType::Def) {
        def += effect;
    }
    else {
        atk += effect;
    }
}
void Dwarf::resetAtkDef() {
    atk = 20;
    def = 30;
}
