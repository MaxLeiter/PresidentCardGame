#include "card.h"
#include <algorithm>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;
class deck {
public:
	vector<card> deckOfCards;
	int sizeOfDeck = 52;
	deck() {
		for (int i = 0; i < 13; i++)
		{
			card deckCard = card(i+2, 'S');
			deckOfCards.push_back(deckCard);
		}
		for (int i = 0; i < 13; i++)
		{
			card deckCard = card(i + 2, 'D');
			deckOfCards.push_back(deckCard);
		}
		for (int i = 0; i < 13; i++)
		{
			card deckCard = card(i + 2, 'C');
			deckOfCards.push_back(deckCard);
		}
		for (int i = 0; i < 13; i++)
		{
			card deckCard = card(i + 2, 'H');
			deckOfCards.push_back(deckCard);
		}
		srand(time(NULL));
		random_shuffle(begin(deckOfCards), end(deckOfCards));

	}

	void displayDeck() {

		for (int i = 0; i < 52; i++) {
			cout << deckOfCards[i].displayCard();
		}
	}

	
	card draw() {
		sizeOfDeck--;

		return deckOfCards[52-sizeOfDeck-1];
		
	}
	
	
};