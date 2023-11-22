#ifndef _NORMAL_H
#define _NORMAL_H

#include "Treasure.h"

class Normal : public Treasure {
public:
	Normal(int value = 1);
	void updateinfo() override;
};

#endif
