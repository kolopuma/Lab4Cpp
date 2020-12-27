
#pragma once
#include <vector>
#include "Card.h"
class Player
{
public:
	Player();
	~Player();
	void setMoney(int money);
	int getMoney() const;
	void openHand();
	void addNewHand();
	void deleteNewHand();
	int getSum();
	int getSplitSum();
	friend class Game;
protected:
	int sum_;
	int sum_split_;
	std::vector<Card>hand;
private:
	std::vector<Card> additional_hand;
	bool new_hand_;
	int money_;
};
