#include "Elf.h"
#include "Cell.h"

void Elf::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
        curr->getType(), "@"});
  curr->setState(State{"Elf", gold, hp, atk, def, "Player character has\
 spawned."});
}


Elf::Elf() {
    hp = 140;
    atk = 30;
    def = 10;
    race = "Elf";
}
void Elf::gainGold(int gain) {
    gold += gain;
    action += " and collects ";
    action += std::to_string(gain);
    action += " gold";
}
void Elf::applyPotion(Potion &pot) {
    int effect = pot.getEffect();
    if (effect < 0) {
        effect = -effect;
    }
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
void Elf::resetAtkDef() {
    atk = 30;
    def = 10;
}
