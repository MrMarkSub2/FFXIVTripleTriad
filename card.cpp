#include "stdafx.h"
#include "card.h"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <sstream>


int cardValToInt(char c) {
	if (c >= '1' && c <= '9')
		return c - '0';
	else if (c == 'A')
		return 10;
	else
		throw std::runtime_error("Invalid card value");
}

Card_t::Card_t(int id, int rarity, const std::string & name, const std::string & cardtype, char up, char right, char down, char left)
	: m_id(id), m_rarity(rarity), m_name(name)
{
	if (m_rarity < 1 || m_rarity > 5)
		throw std::runtime_error("Invalid rarity value");

	if (cardtype == "")
		m_cardtype = CT_NONE;
	else if (cardtype == "Scion")
		m_cardtype = CT_SCION;
	else if (cardtype == "Garlean")
		m_cardtype = CT_GARLEAN;
	else if (cardtype == "Primal")
		m_cardtype = CT_PRIMAL;
	else if (cardtype == "Beastman")
		m_cardtype = CT_BEASTMAN;
	else
		throw std::runtime_error("Invalid card type");

	m_up = cardValToInt(up);
	m_right = cardValToInt(right);
	m_down = cardValToInt(down);
	m_left = cardValToInt(left);
}

std::vector<Card_t> loadCardList(const std::string & filename)
{
	std::vector<Card_t> cardlist;

	std::ifstream ifs(filename);
	if (!ifs.is_open()) 
		throw std::runtime_error("Could not open cardlist file");

	std::string line;
	
	//discard header row
	std::getline(ifs, line);

	while (std::getline(ifs, line)) {
		std::stringstream lineStream(line);

		std::string id_s, rarity_s, name_s, cardtype_s, up_s, right_s, down_s, left_s;
		
		std::getline(lineStream, id_s, ',');
		std::getline(lineStream, rarity_s, ',');
		std::getline(lineStream, name_s, ',');
		std::getline(lineStream, cardtype_s, ',');
		std::getline(lineStream, up_s, ',');
		std::getline(lineStream, right_s, ',');
		std::getline(lineStream, down_s, ',');
		std::getline(lineStream, left_s, ',');

		cardlist.push_back(Card_t(atoi(id_s.c_str()), atoi(rarity_s.c_str()), name_s, cardtype_s, up_s[0], right_s[0], down_s[0], left_s[0]));
	}

	return cardlist;
}
