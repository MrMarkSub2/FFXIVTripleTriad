#include "stdafx.h"
#include "deck.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <Windows.h>

std::vector<int> tokenize_list_of_ints(const std::string& str) {
	std::stringstream ss(str);
	std::vector<int> tokens;
	std::string token;

	while (std::getline(ss, token, ' ')) {
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

std::vector<int> convert_to_card_index(const std::vector<int>& tokens, const std::vector<Card_t>& cardlist) {
	std::vector<int> rval;

	for (int i = 0; i < tokens.size(); ++i) {
		int token = tokens[i];
		std::vector<Card_t>::const_iterator it = std::find_if(cardlist.begin(), cardlist.end(),
			[&token](const Card_t& card) { return card.m_id == token; });

		if (it == cardlist.end()) {
			// if even one token is bad, just ask for a fresh list
			return std::vector<int>();
		}
		else
			rval.push_back(std::distance(cardlist.begin(), it));
	}

	return rval;
}

Deck_t getPlayerDeck(const std::vector<Card_t>& cardlist)
{
	Deck_t deck;
	bool is_valid;

	do {
		is_valid = true;
		std::string line;

		std::cout << "Input player card ids: ";
		std::cin >> std::ws;
		std::getline(std::cin, line);
		std::vector<int> tokens = tokenize_list_of_ints(line);

		if (tokens.size() != 5) {
			std::cout << "ERROR: Player deck must have 5 cards" << std::endl;
			is_valid = false;
		}
		else {
			deck.m_always_cards = convert_to_card_index(tokens, cardlist);

			if (deck.m_always_cards.empty()) {
				std::cout << "ERROR: One or more invalid ids" << std::endl;
				is_valid = false;
			}
		}


	} while (!is_valid);

	return deck;
}

Deck_t getNPCDeck(const std::vector<Card_t>& cardlist)
{
	Deck_t deck;
	bool is_valid;

	do {
		is_valid = true;
		std::string line;
		std::vector<int> tokens;

		std::cout << "Input NPC mandatory card ids: ";
		std::cin >> std::ws;
		std::getline(std::cin, line);
		tokens = tokenize_list_of_ints(line);
		deck.m_always_cards = convert_to_card_index(tokens, cardlist);

		if (tokens.size() != deck.m_always_cards.size()) {
			std::cout << "ERROR: One or more invalid ids" << std::endl;
			is_valid = false;
		}

		if (is_valid) {
			std::cout << "Input NPC optional card ids: ";
			std::cin >> std::ws;
			std::getline(std::cin, line);
			tokens = tokenize_list_of_ints(line);
			deck.m_sometimes_cards = convert_to_card_index(tokens, cardlist);

			if (tokens.size() != deck.m_sometimes_cards.size()) {
				std::cout << "ERROR: One or more invalid ids" << std::endl;
				is_valid = false;
			} else if (deck.m_always_cards.size() + deck.m_sometimes_cards.size() < 5) {
				std::cout << "ERROR: NPC must have at least 5 total valid cards" << std::endl;
				is_valid = false;
			}
		}
	} while (!is_valid);

	return deck;
}

void printDeck(const Deck_t & deck, const std::vector<Card_t>& cardlist)
{
	for (int i = 0; i < deck.m_always_cards.size(); ++i) {
		const Card_t& card = cardlist[deck.m_always_cards[i]];
		std::cout << card.m_id << " - " << card.m_name << std::endl;
	}
	for (int i = 0; i < deck.m_sometimes_cards.size(); ++i) {
		const Card_t& card = cardlist[deck.m_sometimes_cards[i]];
		std::cout << card.m_id << " - " << card.m_name << std::endl;
	}
	std::cout << std::endl;
}

void printDecks(const Deck_t & playerDeck, const Deck_t & npcDeck, const std::vector<Card_t>& cardlist, bool player_is_blue)
{
	const int playerAlways = playerDeck.m_always_cards.size();
	const int playerSometimes = playerDeck.m_sometimes_cards.size() + playerAlways;
	const int npcAlways = npcDeck.m_always_cards.size();
	const int npcSometimes = npcDeck.m_sometimes_cards.size() + npcAlways;

	for (int i = 0; i < playerSometimes || i < npcSometimes; ++i) {
		std::stringstream playerText, npcText;
		if (i < playerAlways) {
			const Card_t& card = cardlist[playerDeck.m_always_cards[i]];
			playerText << card.m_id << " - " << card.m_name;
		}
		else if (i < playerSometimes) {
			const Card_t& card = cardlist[playerDeck.m_sometimes_cards[i - playerAlways]];
			playerText << card.m_id << " - " << card.m_name;
		}

		if (i < npcAlways) {
			const Card_t& card = cardlist[npcDeck.m_always_cards[i]];
			npcText << card.m_id << " - " << card.m_name;
		}
		else if (i < npcSometimes) {
			const Card_t& card = cardlist[npcDeck.m_sometimes_cards[i - npcAlways]];
			npcText << card.m_id << " - " << card.m_name;
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (player_is_blue) {
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << std::setw(40) << std::left << playerText.str();
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << std::setw(40) << std::left << npcText.str() << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << std::setw(40) << std::left << npcText.str();
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << std::setw(40) << std::left << playerText.str() << std::endl;
		}
	}
}
