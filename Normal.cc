#include "Normal.h"
#include "Cell.h"

Normal::Normal(int value): Treasure{value} {}

void Normal::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "G"});
}
