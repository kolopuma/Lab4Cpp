#include "Adapter.h"
#include "IFormattable.h"
#include <io.h>
#include <fcntl.h>
Adapter::Adapter(Deck* deck) {
	deck_ = deck;
}
std::wstring Adapter::format() {
	std::wstring formatted_line_of_deck = L"";
	for (int i = 0; i < deck_->getCount(); i++) {
		Card card = deck_->getCardPerIndex(i);
		if (card.getSuit() == Suit::Club || card.getSuit() == Suit::Spades) {

			formatted_line_of_deck += card.getPrintInterpretation() + L'*';
			for (int j = 0; j < card.getValue(); j++) {
				formatted_line_of_deck += L"\x1b[34m";
				formatted_line_of_deck += card.getSuitInSymbol();
				formatted_line_of_deck += L"\x1b[0m";
			}
			formatted_line_of_deck += L"\n";
		}
		else {
			formatted_line_of_deck += card.getPrintInterpretation() + L'*';
			for (int j = 0; j < card.getValue(); j++) {
				formatted_line_of_deck += L"\x1b[41m";
				formatted_line_of_deck += card.getSuitInSymbol();
				formatted_line_of_deck += L"\x1b[0m";

			}
			formatted_line_of_deck += L"\n";
		}
	}
	return formatted_line_of_deck;
}
void Adapter::prettyPrint(const IFormattable& object) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	std::wcout << format();
}