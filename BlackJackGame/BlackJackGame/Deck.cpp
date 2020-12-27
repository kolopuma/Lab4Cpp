#include "Deck.h"
#include <ctime>
Deck::Deck() {
	std::wstring titles[3] = { L"J", L"Q" , L"K" };
	cards.reserve(52);
	for (size_t i = 2; i <= 10; i++) {
		cards.push_back(new Card(std::to_wstring(i), i, Suit::Club));
		cards.push_back(new Card(std::to_wstring(i), i, Suit::Diamond));
		cards.push_back(new Card(std::to_wstring(i), i, Suit::Hearts));
		cards.push_back(new Card(std::to_wstring(i), i, Suit::Spades));
	}
	for (size_t i = 0; i < 3; i++) {
		cards.push_back(new Card(titles[i], 10, Suit::Club));
		cards.push_back(new Card(titles[i], 10, Suit::Diamond));
		cards.push_back(new Card(titles[i], 10, Suit::Hearts));
		cards.push_back(new Card(titles[i], 10, Suit::Spades));
	}
	cards.push_back(new Card(L"A", 11, Suit::Club));
	cards.push_back(new Card(L"A", 11, Suit::Diamond));
	cards.push_back(new Card(L"A", 11, Suit::Hearts));
	cards.push_back(new Card(L"A", 11, Suit::Spades));

}
Deck::~Deck() {
	cards.clear();
}
void Deck::printCountOfDeck() {
	std::wcout.width(5);
	std::wcout << "[" << cards.size() << "]";
}
int Deck::getDeckSum() {
	int deck_sum = 0;
	for (size_t i = 0; i < cards.size(); i++) {
		deck_sum += cards[i]->getValue();
	}
	return deck_sum;
}
int Deck::getCount() {
	return cards.size();
}
Card Deck::giveCard() {
	srand(time(NULL));
	int i = rand() % cards.size();
	Card card_of_deck = *cards[i];
	cards.erase(cards.begin() + i);
	return card_of_deck;
}
Card Deck::getCardPerIndex(int i) const {
	return *cards[i];
}