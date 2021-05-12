#pragma once

#include <vector>

class Rules_t {
public:
	Rules_t();

	int size() const;

	void setAllOpen(bool b);
	void setThreeOpen(bool b);
	void setSuddenDeath(bool b);
	void setSwap(bool b);
	void setPlus(bool b);
	void setSame(bool b);
	void setFallenAce(bool b);
	void setOrder(bool b);
	void setChaos(bool b);
	void setReverse(bool b);
	void setAscension(bool b);
	void setDescension(bool b);

	bool getAllOpen() const;
	bool getThreeOpen() const;
	bool getSuddenDeath() const;
	bool getSwap() const;
	bool getPlus() const;
	bool getSame() const;
	bool getCombo() const;
	bool getFallenAce() const;
	bool getOrder() const;
	bool getChaos() const;
	bool getReverse() const;
	bool getAscension() const;
	bool getDescension() const;
	
	int rouletteCount() const;
	void addRoulette();
	Rules_t resolveRouletteAutomatically() const;
	Rules_t resolveRouletteManually() const;

	void loadRulesManually();

private:
	std::vector<bool> m_rules;
	int m_rouletteNum;
};