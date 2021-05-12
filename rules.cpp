#include "stdafx.h"
#include "rules.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>

enum RuleEnum { RAllOpen, RThreeOpen, RSuddenDeath, RSwap, RPlus, RSame, RFallenAce, ROrder, RChaos, RReverse, RAscension, RDescension };

Rules_t::Rules_t()
{
	m_rules = std::vector<bool>(12, false);
	m_rouletteNum = 0;
}

int Rules_t::size() const
{
	int rval = 0;
	for (int i = 0; i < m_rules.size(); ++i)
		if (m_rules[i])
			++rval;

	return rval + m_rouletteNum;
}

void Rules_t::setAllOpen(bool b)
{
	m_rules[RAllOpen] = b;
}

void Rules_t::setThreeOpen(bool b)
{
	m_rules[RThreeOpen] = b;
}

void Rules_t::setSuddenDeath(bool b)
{
	m_rules[RSuddenDeath] = b;
}

void Rules_t::setSwap(bool b)
{
	m_rules[RSwap] = b;
}

void Rules_t::setPlus(bool b)
{
	m_rules[RPlus] = b;
}

void Rules_t::setSame(bool b)
{
	m_rules[RSame] = b;
}

void Rules_t::setFallenAce(bool b)
{
	m_rules[RFallenAce] = b;
}

void Rules_t::setOrder(bool b)
{
	m_rules[ROrder] = b;
}

void Rules_t::setChaos(bool b)
{
	m_rules[RChaos] = b;
}

void Rules_t::setReverse(bool b)
{
	m_rules[RReverse] = b;
}

void Rules_t::setAscension(bool b)
{
	m_rules[RAscension] = b;
}

void Rules_t::setDescension(bool b)
{
	m_rules[RDescension] = b;
}

bool Rules_t::getAllOpen() const
{
	return m_rules[RAllOpen];
}

bool Rules_t::getThreeOpen() const
{
	return m_rules[RThreeOpen];
}

bool Rules_t::getSuddenDeath() const
{
	return m_rules[RSuddenDeath];
}

bool Rules_t::getSwap() const
{
	return m_rules[RSwap];
}

bool Rules_t::getPlus() const
{
	return m_rules[RPlus];
}

bool Rules_t::getSame() const
{
	return m_rules[RSame];
}

bool Rules_t::getCombo() const
{
	return m_rules[RPlus] || m_rules[RSame];
}

bool Rules_t::getFallenAce() const
{
	return m_rules[RFallenAce];
}

bool Rules_t::getOrder() const
{
	return m_rules[ROrder];
}

bool Rules_t::getChaos() const
{
	return m_rules[RChaos];
}

bool Rules_t::getReverse() const
{
	return m_rules[RReverse];
}

bool Rules_t::getAscension() const
{
	return m_rules[RAscension];
}

bool Rules_t::getDescension() const
{
	return m_rules[RDescension];
}

int Rules_t::rouletteCount() const
{
	return m_rouletteNum;
}

void Rules_t::addRoulette()
{
	++m_rouletteNum;
}

Rules_t Rules_t::resolveRouletteAutomatically() const
{
	Rules_t rval(*this);
	while (rval.rouletteCount() > 0 && rval.size() <= 9) {
		int newRule = rand() % 12;
		switch (newRule) {
		case RAllOpen:
			if (!rval.getThreeOpen() && !rval.getAllOpen()) {
				rval.setAllOpen(true);
				--rval.m_rouletteNum;
			}
			break;
		case RThreeOpen:
			if (!rval.getAllOpen() && !rval.getThreeOpen()) {
				rval.setThreeOpen(true);
				--rval.m_rouletteNum;
			}
			break;

		case ROrder:
			if (!rval.getChaos() && !rval.getOrder()) {
				rval.setOrder(true);
				--rval.m_rouletteNum;
			}
			break;
		case RChaos:
			if (!rval.getOrder() && !rval.getChaos()) {
				rval.setChaos(true);
				--rval.m_rouletteNum;
			}
			break;

		case RAscension:
			if (!rval.getDescension() && !rval.getAscension()) {
				rval.setAscension(true);
				--rval.m_rouletteNum;
			}
			break;
		case RDescension:
			if (!rval.getAscension() && !rval.getDescension()) {
				rval.setDescension(true);
				--rval.m_rouletteNum;
			}
			break;

		default:
			if (!rval.m_rules[newRule]) {
				rval.m_rules[newRule] = true;
				--rval.m_rouletteNum;
			}
			break;
		}
	}

	return rval;
}

Rules_t ruleManualHelper(const Rules_t& rules_in, bool resolvingRoulette) {
	// TODO: Could be smarter about edge conditions, warning about Ascension+Descension etc
	// For now I'm trusting that user will faithfully carry these values from game
	// Unexpected behavior if they enter a wacky combo on their own
	Rules_t rval(rules_in);
	while (true) {
		if (!resolvingRoulette)
			std::cout << "END - End, RO - Roulette, ";

		if (!rval.getAllOpen() && !rval.getThreeOpen())
			std::cout << "AO - All Open, TO - Three Open, ";
		if (!rval.getSuddenDeath())
			std::cout << "SD - Sudden Death, ";
		if (!rval.getSwap())
			std::cout << "SW - Swap, ";
		if (!rval.getPlus())
			std::cout << "PL - Plus, ";
		if (!rval.getSame())
			std::cout << "SA - Same, ";
		if (!rval.getFallenAce())
			std::cout << "FA - Fallen Ace, ";
		if (!rval.getOrder() && !rval.getChaos())
			std::cout << "OR - Order, CH - Chaos, ";
		if (!rval.getReverse())
			std::cout << "RE - Reverse, ";
		if (!rval.getAscension() && !rval.getDescension())
			std::cout << "AS - Ascension, DE - Descension";
		std::cout << std::endl;
		std::string input;
		std::cin >> input;

		if (iequals(input, "AO") && !rval.getAllOpen()) {
			rval.setAllOpen(true);
			return rval;
		}
		else if (iequals(input, "TO") && !rval.getThreeOpen()) {
			rval.setThreeOpen(true);
			return rval;
		}
		else if (iequals(input, "SD") && !rval.getSuddenDeath()) {
			rval.setSuddenDeath(true);
			return rval;
		}
		else if (iequals(input, "SW") && !rval.getSwap()) {
			rval.setSwap(true);
			return rval;
		}
		else if (iequals(input, "PL") && !rval.getPlus()) {
			rval.setPlus(true);
			return rval;
		}
		else if (iequals(input, "SA") && !rval.getSame()) {
			rval.setSame(true);
			return rval;
		}
		else if (iequals(input, "FA") && !rval.getFallenAce()) {
			rval.setFallenAce(true);
			return rval;
		}
		else if (iequals(input, "OR") && !rval.getOrder()) {
			rval.setOrder(true);
			return rval;
		}
		else if (iequals(input, "CH") && !rval.getChaos()) {
			rval.setChaos(true);
			return rval;
		}
		else if (iequals(input, "RE") && !rval.getReverse()) {
			rval.setReverse(true);
			return rval;
		}
		else if (iequals(input, "AS") && !rval.getAscension()) {
			rval.setAscension(true);
			return rval;
		}
		else if (iequals(input, "DE") && !rval.getDescension()) {
			rval.setDescension(true);
			return rval;
		}
		else if (iequals(input, "RO") && !resolvingRoulette) {
			rval.addRoulette();
			return rval;
		}
		else if (iequals(input, "END") && !resolvingRoulette) {
			return rval;
		}
	}
}

Rules_t Rules_t::resolveRouletteManually() const
{	
	Rules_t rval(*this);
	while (rval.rouletteCount() > 0) {
		rval = ruleManualHelper(rval, true);
		--rval.m_rouletteNum;
	}

	return rval;
}

void Rules_t::loadRulesManually()
{
	Rules_t rules;
	int oldsize = rules.size(), newsize = rules.size();

	do {
		oldsize = rules.size();
		rules = ruleManualHelper(rules, false);
		newsize = rules.size();
	} while (newsize < 4 && oldsize != newsize);

	*this = rules;
}
