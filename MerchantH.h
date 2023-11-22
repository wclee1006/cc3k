#ifndef _MERCHANTH_H
#define _MERCHANTH_H

#include "Treasure.h"
#include "Merchant.h"

class Merchant;

class MerchantH : public Treasure {
public:
	MerchantH(int value = 4, Merchant *merchant = nullptr);

	void setMerchant(Merchant *merchant);

	~MerchantH();

	void updateinfo() override;
private:
	Merchant *merchant;
};

#endif
