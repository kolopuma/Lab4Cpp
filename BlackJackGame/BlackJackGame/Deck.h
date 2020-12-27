#pragma once
#include <vector>
#include "Card.h"
class Deck
{
public:
	Deck();
	~Deck();
	void printCountOfDeck();
	int getDeckSum();
	int getCount();
	Card giveCard();
	Card getCardPerIndex(int i) const;
private:
	std::vector<Card*> cards;
};

