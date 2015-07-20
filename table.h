#include "card.h"
using namespace std;
class table {
public:
	
	vector<card> topCard;
	vector<card> oldCards;
	int amountOfTopCards = 0;

	table() {
		topCard = { card(NULL, NULL) };
	}
	void setTopCard(vector<card> toTop) {
		for (int i = 0; i < topCard.size(); i++)
			oldCards.push_back(topCard[i]);
		topCard = toTop;
		amountOfTopCards = topCard.size();
	}
	vector<card> getOldCards() {
		return oldCards;
	}
	vector<card> getTopCard() {
		return topCard;
	}

	int getAmountOfTopCards() {
		return amountOfTopCards;
	}

	void setAmountOfTopCards(int size) {
		amountOfTopCards = size;
	}

	void clearDeck() {
		oldCards.clear();
		for (int i = 0; i < topCard.size(); i++)
			topCard[i].setSuitAndValue(NULL, NULL);
	}
};
