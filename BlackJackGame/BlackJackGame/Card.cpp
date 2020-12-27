#include "Card.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
Card::Card(std::wstring title, int value, Suit suit) {
	title_ = title;
	value_ = value;
	suit_ = suit;
	switch (suit_) {
	case Suit::Club:
		suit_symbol_ = L'\u2663';
		break;
	case Suit::Diamond:
		suit_symbol_ = L'\u2666';
		break;
	case Suit::Spades:
		suit_symbol_ = L'\u2660';
		break;
	case Suit::Hearts:
		suit_symbol_ = L'\u2665';
		break;
	}
}
Card::~Card() {

}
int Card::getValue() const {
	return value_;
}
std::wostream& operator<<(std::wostream& out, const Card& card) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	out << card.title_ << card.suit_symbol_ << " ";
	_setmode(_fileno(stdout), _O_TEXT);
	_setmode(_fileno(stdin), _O_TEXT);
	return out;
}
std::wstring Card::getPrintInterpretation() const {
	std::wstring wstr = L"";
	wstr += title_;
	wstr += suit_symbol_;
	return wstr;
}
Suit Card::getSuit() const {
	return suit_;
}
wchar_t Card::getSuitInSymbol() const {
	return suit_symbol_;
}