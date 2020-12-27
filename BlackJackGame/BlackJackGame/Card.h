#pragma once
#include <string>
#include "io.h"
#include "fcntl.h"
#include <iostream>
enum class Suit
{
	Hearts,
	Diamond,
	Club,
	Spades
};
class Card
{
public:
	Card(std::wstring title, int value, Suit suit);
	~Card();
	int getValue() const;
	std::wstring getPrintInterpretation() const;
	Suit getSuit() const;
	wchar_t getSuitInSymbol() const;
	friend std::wostream& operator<<(std::wostream& out, const Card& card);
private:
	std::wstring title_;
	int value_;
	wchar_t suit_symbol_;
	Suit suit_;
};