#pragma once
#include "IFormattable.h"
#include <string>
#include "Deck.h"
class Adapter :public IFormattable
{
public:
	Adapter(Deck* deck);
	std::wstring format() override;
	void prettyPrint(const IFormattable& object) override;
private:
	Deck* deck_;
};

