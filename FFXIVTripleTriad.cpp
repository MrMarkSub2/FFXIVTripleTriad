// FFXIVTripleTriad.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "card.h"

#include <iostream> // TODO

int main()
{
	std::vector<Card_t> cardlist = loadCardList("cardlist.csv");
	std::cout << cardlist.size() << std::endl;
	// TODO: select mode (single match vs NPC, single match vs unknown, find best deck vs NPC, find best deck for tournament)
    return 0;
}

