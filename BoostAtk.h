#ifndef _BOOST_ATK_H
#define _BOOST_ATK_H

#include "Potion.h"

class BoostAtk : public Potion {
	static bool recognized;
public:
	BoostAtk(int effect = 5);

	bool isRecognized() override;
	void setRecognized(bool rec) override;

	// returns "P" if not recognized
	// returns "BA" if recognized
	std::string getDisplay() const override;

	// tells the player to use this Potion
	void usedBy(Player &player) override;
	void updateinfo() override;
};

#endif
