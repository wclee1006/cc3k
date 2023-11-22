#ifndef _BOOST_DEF_H
#define _BOOST_DEF_H

#include "Potion.h"

class BoostDef : public Potion {
	static bool recognized;
public:
	BoostDef(int effect = 5);

	bool isRecognized() override;
	void setRecognized(bool rec) override;

	// returns "P" if not recognized
	// returns "BD" if recognized
	std::string getDisplay() const override;

	// tells Player to use this Potion
	void usedBy(Player &player) override;
	void updateinfo() override;
};

#endif
