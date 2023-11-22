#include "CellContent.h"

// see CellContent.h for documentation

void CellContent::act(ActionType type) {}

void CellContent::findDragon(DragonH *dragonH) {}

void CellContent::newTurn() {}

CellContent::~CellContent() {}

void CellContent::attacked(CellContent &attacker) {}

void CellContent::attacksOn(Player &player) {}

void CellContent::attacksOn(Enemy &enemy) {}

void CellContent::usedBy(Player &player) {}

bool CellContent::canMoveOn(Player &player) {return false;}

void CellContent::LinkCurr(Cell *current) {curr = current;}

void CellContent::updateinfo() {}
