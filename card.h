#pragma once

#include <vector>
#include <string>

enum Cardtype_t { CT_NONE, CT_SCION, CT_GARLEAN, CT_PRIMAL, CT_BEASTMAN };

struct Card_t {
	Card_t(int id, int rarity, const std::string& name, const std::string& cardtype, char up, char right, char down, char left);

	int m_id, m_rarity;
	std::string m_name;
	Cardtype_t m_cardtype;
	int m_up, m_right, m_down, m_left;
};

std::vector<Card_t> loadCardList(const std::string& filename);
