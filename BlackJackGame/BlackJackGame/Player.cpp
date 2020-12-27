
#include "Player.h"
#include "Game.h"
#include <ctime>
Player::Player() {
	money_ = 10000;
	sum_ = 0;
	new_hand_ = false;
	sum_split_ = 0;
}
Player::~Player() {
	hand.clear();
	additional_hand.clear();
}
int Player::getMoney() const {
	return money_;
}
void Player::setMoney(int credits) {
	money_ = credits;
}
void Player::openHand() {
	hand.reserve(5);
}
void Player::addNewHand() {
	additional_hand.reserve(5);
	new_hand_ = true;
}
void Player::deleteNewHand() {
	additional_hand.clear();
	new_hand_ = false;
}
int Player::getSum() {
	return sum_;
}
int Player::getSplitSum() {
	return sum_split_;
}
