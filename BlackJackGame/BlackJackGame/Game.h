#pragma once
#include "Deck.h"
#include "Player.h"
class Game
{
public:
	Game();
	Game(bool empty);
	~Game();
	void giveCardToPlayer(bool dealer);
	void printInfoAboutDecks();
	void play();
	void getAmount();
	void printPlayersHand(bool dealer);
	void printGameInfo();
	bool Continue();
private:
	Deck* decks[4];
	Player* players[2];
	int total;
	bool start;
	bool player_stop;
	bool match_stop;
	bool isSplit;
};

