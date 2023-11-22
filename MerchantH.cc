#include "MerchantH.h"
#include "Player.h"
#include "Merchant.h"
#include "Cell.h"

void MerchantH::updateinfo() {
  curr->setInfo(Info{curr->getX(), curr->getY(),
	curr->getType(), "G"});
}

MerchantH::MerchantH(int value, Merchant *merchant): Treasure{value}, 
	merchant{merchant} {}

void MerchantH::setMerchant(Merchant *merchant) {
	this->merchant = merchant;
}

MerchantH::~MerchantH() {delete merchant;}
