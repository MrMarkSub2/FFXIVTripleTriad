#pragma once

#include "card.h"

struct Deck_t {
	std::vector<int> m_always_cards;
	std::vector<int> m_sometimes_cards;
};

Deck_t getPlayerDeck(const std::vector<Card_t>& cardlist);
Deck_t getNPCDeck(const std::vector<Card_t>& cardlist);

void printDeck(const Deck_t& deck, const std::vector<Card_t>& cardlist);
void printDecks(const Deck_t& playerDeck, const Deck_t& npcDeck, const std::vector<Card_t>& cardlist, bool player_is_blue);
