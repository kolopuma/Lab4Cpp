#include "Game.h"
#include "Dealer.h"
#include "BlackJackException.h"
#include "EqualException.h"
#include "LoseException.h"
#include "WinException.h"
#include "OutOfScoreException.h"
#include <Windows.h>
#include <stdio.h>
#include <ctime>
Game::Game() {
	for (int i = 0; i < 4; i++) {
		decks[i] = new Deck();
	}
	players[0] = new Player();
	players[0]->setMoney(2000);
	players[1] = new Dealer();
	start = true;
	player_stop = false;
	match_stop = false;
	isSplit = false;
}
Game::Game(bool empty) {

}
Game::~Game() {
	delete[] decks;
}
void Game::giveCardToPlayer(bool dealer) {
	srand(time(NULL));
	if (dealer) {
		if (!match_stop) {
			Card card = decks[rand() % 4]->giveCard();
			players[1]->hand.push_back(card);
			players[1]->sum_ += card.getValue();
		}

		if (players[1]->getSum() > 21) {
			throw OutOfScoreException();
		}

		if (players[1]->getSum() == 21) {
			throw BlackJackException();
		}

		if (players[0]->getSum() > players[1]->getSum() && player_stop&& match_stop) {
			throw LoseException();
		}
		
		if (players[0]->getSum() < players[1]->getSum() && player_stop && match_stop) {
			throw WinException();
		}

		if (players[0]->getSum() == players[1]->getSum() && player_stop && match_stop) {
			throw EqualException();
		}
		
	}
	else
	{
		if (!isSplit) {
			Card card = decks[rand() % 4]->giveCard();
			players[0]->hand.push_back(card);
			players[0]->sum_ += card.getValue();
			if (players[0]->getSum() > 21) {
				throw OutOfScoreException();
			}

			if (players[0]->getSum() == 21) {
				throw BlackJackException();
			}

			if (players[0]->getSum() == players[1]->getSum() && player_stop && match_stop) {
				throw EqualException();
			}
		}
		else {
			Card card = decks[rand() % 4]->giveCard();
			players[0]->additional_hand.push_back(card);
			players[0]->sum_split_ += card.getValue();
			if (players[0]->getSplitSum() > 21) {
				throw OutOfScoreException();
			}

			if (players[0]->getSplitSum() == 21) {
				throw BlackJackException();
			}

			if (players[0]->getSplitSum() == players[1]->getSum() && player_stop && match_stop) {
				throw EqualException();
			}
		}
	}
}
void Game::printPlayersHand(bool dealer) {
	if (dealer) {
		for (size_t i = 0; i < players[1]->hand.size(); i++)
		{
			std::wcout.width(5);
			std::wcout << players[1]->hand[i];
		}
		std::wcout.width(5);
		
	}
	else
	{
		if (!isSplit) {
			for (size_t i = 0; i < players[0]->hand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->hand[i];
			}
		}
		else {
			for (size_t i = 0; i < players[0]->hand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->hand[i];
			}
			std::wcout << L"\nДополнительная рука: ";
			for (size_t i = 0; i < players[0]->additional_hand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->additional_hand[i];
			}
		}
	}
}
void Game::printInfoAboutDecks() {
	for (int i = 0; i < 4; i++) {
		decks[i]->printCountOfDeck();
	}
	std::wcout << "\n";
}
void Game::printGameInfo() {
	if (!isSplit) {
		std::cout << "Колоды:";
		printInfoAboutDecks();
		std::cout << "\nДилер:";
		printPlayersHand(true);
		std::wcout << L"\nВы:";
		printPlayersHand(false);
		std::wcout << L"\n\n1.Хватит";
		std::wcout << L"\n2.Еще\n";
		std::wcout << L"3.Сплит?\n";
	}
	else {
		std::cout << "Колода:";
		printInfoAboutDecks();
		std::cout << "\nДилер:";
		printPlayersHand(true);
		std::wcout << L"\nВы:";
		printPlayersHand(false);
		std::wcout << L"\n\n1.Хватит";
		std::wcout << L"\n2.Еще\n";
	}
}
void Game::getAmount() {
	int member = 0;
	
	std::wcout << L"Ваша ставка?" << L" Всего: " << std::to_wstring(players[0]->getMoney()) << std::endl;
	std::cin >> member;
	if (member > 0 && member <= players[0]->getMoney()) {
		total = member;
		system("cls");
	}
	else
	{
		std::wcout << L"У вас недостаточно денег.\n";
		system("pause");
		system("cls");
		getAmount();
	}
}
void Game::play() {
	wchar_t input;
	getAmount();
	players[1]->openHand();
	giveCardToPlayer(true);
	players[0]->openHand();
	giveCardToPlayer(false);
	printGameInfo();
	int required_value = 0;
	int all_value = 0;
	int all_counter = 0;
	int average_value = 0;
	while (start)
	{
		std::wcin >> input;
		switch (input)
		{
		case L'1':
			system("cls");
			player_stop = true;
			while (!match_stop) {
				required_value = 21 - players[1]->sum_;
				all_value = 0;
				all_counter = 0;
				for (int i = 0; i < 4; i++) {
					all_value += decks[i]->getDeckSum();
					all_counter += decks[i]->getCount();
				}
				average_value = all_value / all_counter;
				if (average_value <= required_value) {
					try {
						giveCardToPlayer(true);
					}
					catch (OutOfScoreException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() + total);
							std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total) << L" Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() + (2 * total));
							std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(2 * total) << L" Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
					}
					catch (BlackJackException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() - total);
							std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							printGameInfo();
							std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
					}
					
				}
				else
				{
					match_stop = true;
					try {
						giveCardToPlayer(true);
					}
					
					catch (OutOfScoreException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() + total);
							std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total) << L" Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() + (2 * total));
							std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total * 2) << L" Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
					}
					catch (BlackJackException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() - total);
							std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							printGameInfo();
							std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
					}
					catch (LoseException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() + total);
							std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total) << L" Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							if (players[0]->getSplitSum() > players[1]->getSum()) {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() + total * 2);
								std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total * 2) << L" Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else if (players[0]->getSplitSum() < players[1]->getSum()) {
								printGameInfo();
								std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() + 3 * total / 2);
								std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(3 * total / 2) << L" Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
						}
					}					
					catch (EqualException) {
						if (!isSplit) {
							printGameInfo();
							std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
						}
						else {
							if (players[0]->getSplitSum() > players[1]->getSum()) {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() + 3 * total / 2);
								std::wcout << L"\nПоздравляем! Ваш выиграли! Ваш выигрыш: " << std::to_wstring(3 * total / 2) << L" Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else if (players[0]->getSplitSum() < players[1]->getSum()) {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() - total / 2);
								std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total / 2) << L". Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else {
								printGameInfo();
								std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
						}
					}
					catch (WinException) {
						if (!isSplit) {
							printGameInfo();
							players[0]->setMoney(players[0]->getMoney() - total);
							std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
							start = false;
							break;
						}
						else {
							if (players[0]->getSplitSum() > players[1]->getSum()) {
								printGameInfo();
								std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else if (players[0]->getSplitSum() < players[1]->getSum()) {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() - total);
								std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
							else {
								printGameInfo();
								players[0]->setMoney(players[0]->getMoney() - total / 2);
								std::wcout << L"\nВы проиграли! Ваш проигрыш: " << std::to_wstring(total / 2) << L". Всего: " << std::to_wstring(players[0]->getMoney());
								start = false;
								break;
							}
						}
					}
					
				}
			}
			start = false;
			break;
		case L'2':
			system("cls");
			try {
				giveCardToPlayer(false);
			}
			catch (OutOfScoreException) {
				printGameInfo();
				players[0]->setMoney(players[0]->getMoney() - total);
				std::wcout << L"\nПеребор! Вы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
				start = false;
				break;
			}

			catch (BlackJackException) {
				printGameInfo();
				players[0]->setMoney(players[0]->getMoney() + total);
				std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total) << L" Всего: " << std::to_wstring(players[0]->getMoney());
				start = false;
				break;
			}			
			printGameInfo();
			break;
		case L'3':
			system("cls");
			players[0]->addNewHand();
			isSplit = true;
			try {
				giveCardToPlayer(false);
			}
			
			catch (OutOfScoreException) {
				if (players[0]->getSum() > players[1]->getSum()) {
					printGameInfo();
					std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
					break;
				}
				else {
					printGameInfo();
					players[0]->setMoney(players[0]->getMoney() - total);
					std::wcout << L"\nПеребор! Вы проиграли! Ваш проигрыш: " << std::to_wstring(total) << L". Всего: " << std::to_wstring(players[0]->getMoney());
				}
			}
			catch (BlackJackException) {
				if (players[0]->getSum() > players[1]->getSum()) {
					printGameInfo();
					players[0]->setMoney(players[0]->getMoney() + total * 2);
					std::wcout << L"\nПоздравляем! Вы выиграли! Ваш выигрыш: " << std::to_wstring(total * 2) << L" Всего: " << std::to_wstring(players[0]->getMoney());
					start = false;
					break;
				}
				else {
					printGameInfo();
					std::wcout << L"\nНичья! Ваша ставка " << std::to_wstring(total) << L" сохранена. Всего: " << std::to_wstring(players[0]->getMoney());
				}
			}
			printGameInfo();
			break;
		default:
			system("cls");
			start = false;
			break;
		}
	}
}
bool Game::Continue() {
	std::wcout << L"\n1.Продолжить\n2.Выход\n";
	wchar_t input;
	std::wcin >> input;
	switch (input)
	{
	case L'1':
		system("cls");
		start = true;
		match_stop = false;
		player_stop= false;
		isSplit = false;
		players[0]->sum_ = 0;
		players[1]->sum_ = 0;
		players[0]->hand.clear();
		players[1]->hand.clear();
		players[0]->sum_split_ = 0;
		players[0]->deleteNewHand();
		return true;
	default:
		return false;
	}
}