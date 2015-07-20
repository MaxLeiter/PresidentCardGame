#include "card.h"
#include "deck.h"
#include <vector>
#include <string>
#include <algorithm> 
#include <iomanip>
using namespace std;
class player {
	
public:
	deck cardDeckForPrinting;
	vector<card> playerHand;
	string playerName;
	bool passed = false;
	player(string name) {
		
		playerName = name;
	};

	void setPassed() {
		passed = true;
	}

	void resetPassed() {
		passed = false;
	}

	bool getPassed() {
		return passed;
	}

	
	string printHand() {
		
		string outputString = "";
		
		
		for (int i = 0; i < playerHand.size(); i++) {
			outputString += to_string(i + 1);
			outputString += " ";
			outputString += playerHand[i].displayCard();
			outputString += " \t";
			if (i % 3 == 2)
				outputString += "\n";
			
		}
		return outputString;
	}

	vector<card> getHand() {
		return playerHand;
	}

	void setHand(vector<card> cardToSet) {
		playerHand = cardToSet;

	}
	string getName() {
		return playerName;
	}

	void addCard(card cardToAdd) {
		playerHand.push_back(cardToAdd);
	}

	int getHandSize() {
		int handSize = playerHand.size();
		return handSize;
	}


	void removeCardByIndex(int index) {
		playerHand.erase(playerHand.begin() + index);
	}
	

	void removeCard(card cardToRemove) {
		for (int i = 0; i < playerHand.size(); i++)
		{
			if (playerHand[i].displayCard() == cardToRemove.displayCard()) {
				playerHand.erase(playerHand.begin() + i);
				
			}
		}
		
	}

};