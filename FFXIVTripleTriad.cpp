// FFXIVTripleTriad.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "card.h"
#include "deck.h"
#include "rules.h"
#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void goSingleMatchNPC(const std::vector<Card_t>& cardlist)
{
	Deck_t playerDeck = getPlayerDeck(cardlist);
	Deck_t npcDeck = getNPCDeck(cardlist);

	//printDeck(npcDeck, cardlist);
	//printDecks(playerDeck, npcDeck, cardlist, true);

	Rules_t rules;
	std::cout << std::endl
		<< "Match Rules:" << std::endl;
	rules.loadRulesManually();

	//TODO
	//rules = rules.resolveRouletteManually();

	//executeInteractiveMatch(playerDeck, npcDeck, cardlist);
}

int main()
{
	srand(time(NULL));

	std::vector<Card_t> cardlist = loadCardList("cardlist.csv");
	// TODO: select mode (single match vs NPC, single match vs unknown, find best deck vs NPC, find best deck for tournament)

	bool endprog(false);

	do {
		std::string mode;
		std::cout << "Triple Triad Solver!" << std::endl
			<< "\tMNPC - single match vs NPC" << std::endl
			<< "\tQuit - end program" << std::endl
			<< std::endl
			<< "Mode: ";
		std::cin >> mode;

		if (iequals(mode, "Quit"))
			endprog = true;
		else if (iequals(mode, "MNPC")) {
			goSingleMatchNPC(cardlist);
		}
	} while (!endprog);

    return 0;
}

