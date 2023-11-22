#include "Character.h"

Character::Character(int hp, int atk, int def): hp{hp}, atk{atk}, def{def} {}

Character::~Character() {}

int Character::gethp() {
    return hp;
}

int Character::getatk() {
    return atk;
}

int Character::getdef() {
    return def;
}
