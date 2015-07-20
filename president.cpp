#include <iostream>
#include "player.h"
#include <string>
#include <stdlib.h>
#include "table.h"
#include <iterator>    
#include <regex>      
using namespace std;

vector<player> startGame(vector<player> vec);
void placeCard(vector<card> card);
bool same_suit(string suit[]);
bool straight(short value[]);
void check_cards(bool four, bool three, bool pair, bool two_pair, short num_of_combos, short size);
vector<string> splitString(string stringThing, char splitter);
void endTurn();
vector<card> selectionSort(vector<card> sortVec);
bool isThreeOfClubsDown = false;;
vector<player> players;
int cardsPerPlayer;
deck cardDeck;
table cardTable;
int main() {
	cardTable = table();
	string suits = "CDHS";
	int numOfPlayers;
	bool gameOver = false;
	cout << "Welcome to president!" << endl;
	cout << "Please enter the amount of players below: " << endl;
	cin >> numOfPlayers;

	if (errno) {
		cout << "error happend according to errno"; 
	}

	if (cin.fail()) {
		cout << "cin reported that it failed";
		//exit(1);
	}

	cardsPerPlayer = 52 / numOfPlayers;


	cout << "Each player has " << cardsPerPlayer << " cards" << endl;

	string playerName;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter player " << i + 1 << "'s name: " << endl;
		cin >> playerName;
		player tempPlayer = player(playerName);
		players.push_back(tempPlayer);

	}


	system("CLS");
	players = startGame(players);
	int playerId = 0;
	/** DECIDE WHOS FIRST **/
	card threeOfClubs;
	threeOfClubs = card(3, 'C');
	vector<card> threeOfClubsVectorBecauseCisStupid;
	threeOfClubsVectorBecauseCisStupid.push_back(threeOfClubs);
	for (int i = 0; i < players.size(); i++) {
		for (int x = 0; x < players[i].getHandSize(); x++) {
			if (players[i].getHand()[x].displayCard() == threeOfClubsVectorBecauseCisStupid[0].displayCard()) {
				cardTable.setTopCard(threeOfClubsVectorBecauseCisStupid);
				players[i].removeCardByIndex(x);
				playerId = i;
				isThreeOfClubsDown = true;
			}
		}
	}



	cout << players[playerId].getName() << " had the three of clubs to start the game" << endl;
	playerId++;

	/**GAME**/

	int rounds = 0;

	/**GAME LOOP **/
	while (1 == 1 && !gameOver) {
		/**ROUND LOOP**/
		for (int i = 0; i < players.size(); i++) {
			int previousPlayerId = playerId;
			if (rounds > 1) {
				isThreeOfClubsDown = false;

			}
			vector<card> topCards = { card(NULL, NULL) };

			vector<card> tempVec = selectionSort(players[i].getHand());
	
			players[i].setHand(tempVec);
			topCards = cardTable.topCard;
			

			string topCardToPrint = "";
			// Iterate through the top cards played (in case more then one)
			for (int i = 0; i < topCards.size(); i++) {
				topCardToPrint += topCards[i].displayCard();
				topCardToPrint += " ";
			}
			cout << "Current top card: " << topCardToPrint << endl;
			cout << players[i].getName() << "'s" << " hand: " << endl << players[i].printHand() << endl;
			cout << "Type which card to play, and type two numbers seperated by a / to use a pair." << endl;
			cout << "Type '0' to pass" << endl;
			cout << "Type 'cards' to see previous cards" << endl;
			string selectedCard;
			cin >> selectedCard;

			if (selectedCard == "cards") {
				cout << endl << endl;
				for (int i = 0; i < cardTable.getOldCards().size(); i++)
					cout << cardTable.getOldCards()[i].displayCard() << endl;

				break;
			}
			// Passes
			else if (selectedCard == "0") {
				players[i].setPassed();
				system("cls");
				cout << "You chose to pass, wait five seconds for the next player" << endl;

				int totalPlayersPassed = 0;
				for (int i = 0; i < players.size(); i++){
					if (players[i].getPassed()){
						totalPlayersPassed++;
					}
				}

				if (totalPlayersPassed == players.size() - 1) {
					cout << "Everyone passed! Moving to the next round" << endl;
					rounds++;
					playerId = playerId + 1;
					playerId = playerId % numOfPlayers;
					endTurn();
					card newCard;
					newCard = card(NULL, NULL);
					vector<card> temporaryVectorBecauseIHateC;
					temporaryVectorBecauseIHateC.push_back(newCard);
					placeCard(temporaryVectorBecauseIHateC);
					system("cls");
					break;
				}

				endTurn();

			}
			else if (selectedCard.find("/") != string::npos) {
				vector<string> multipleCardsToPlay = splitString(selectedCard, '/');

				vector<card> multipleCardsToPlayVector;
				for (int a = 0; a < multipleCardsToPlay.size(); a++) {
					card cardToAddToVector = players[i].getHand()[atoi(multipleCardsToPlay[a].c_str()) - 1];

					multipleCardsToPlayVector.push_back(cardToAddToVector);
				}

				if (cardTable.getAmountOfTopCards() != multipleCardsToPlayVector.size() && cardTable.getTopCard()[0].getValue() != 0) {
					system("cls");
					cout << "You must play the same amount of cards as previous players played (" << cardTable.getAmountOfTopCards() << ")" << endl;
					cout << "TOP CARD IS" << cardTable.getTopCard()[0].displayCard() << endl;
					break;
				}
				else if (cardTable.getTopCard().size() > 1 || cardTable.getTopCard()[0].getValue() == 0){
					if (multipleCardsToPlayVector[0].getValue() == multipleCardsToPlayVector[1].getValue() && multipleCardsToPlayVector[0].getValue() > cardTable.getTopCard()[0].getValue())  {

						placeCard(multipleCardsToPlayVector);
						string cardsPlayed = "";
						for (int z = 0; z < multipleCardsToPlayVector.size(); z++) {
							players[i].removeCard(multipleCardsToPlayVector[z]);
							cardsPlayed += multipleCardsToPlayVector[z].displayCard();
							cardsPlayed += " ";
						}
						cout << "You played " << cardsPlayed << endl;
						endTurn();
						continue;

					}
					else {
						system("cls");
						cout << "You're cards aren't better than the previous ones." << endl;
						break;
					}

				}
				else {
					system("cls");
					cout << "You're cards aren't better than the previous ones." << endl;
					break;
				}
				

			}
			else {
				for (int k = 0; k < players.size(); k++)
					players[k].resetPassed();

				vector<card> cardsToPlay;

				card indivCardToPlay = players[i].getHand()[atoi(selectedCard.c_str()) - 1];
				cardsToPlay.push_back(indivCardToPlay);
				
				//Check if its too large
			//	int cardToPlaySuit = suits.find(cardsToPlay[atoi(selectedCard.c_str()) - 1].getSuit());
			//	int topCardSuit = suits.find(cardTable.getTopCard()[0].getSuit());
				if (players[i].getHand()[atoi(selectedCard.c_str()) - 1].getCardValue() > cardTable.getTopCard()[0].getCardValue() && players[i].getHand()[atoi(selectedCard.c_str()) - 1].getValue() != 2) {

					placeCard(cardsToPlay);
					players[i].removeCardByIndex(atoi(selectedCard.c_str()) - 1);
					cout << players[i].getName() << " played " << cardsToPlay[0].displayCard() << endl;
				}
				else if (players[i].getHand()[atoi(selectedCard.c_str()) - 1].getValue() == 2) {
					cardTable.clearDeck();
					cout << players[i].getName() << " played a 2, so the deck is cleared and they start the next round." << endl;
					playerId == previousPlayerId;
				}
				else if (cardsToPlay[atoi(selectedCard.c_str()) - 1].getValue() == cardTable.getTopCard()[0].getValue() && players[i].getHand()[atoi(selectedCard.c_str())].getSuit() > cardTable.getTopCard()[0].getSuit()) {
					cout << "PLACING" << endl;
					placeCard(cardsToPlay);
					cout << "REMOVING" << endl;
					players[i].removeCardByIndex(atoi(selectedCard.c_str()) - 1);
					cout << "REMOVED" << endl;
					cout << players[i].getName() << " played " << cardsToPlay[atoi(selectedCard.c_str()) - 1].displayCard() << endl;
				}
				else {
					system("cls");
					
					cout << "The card you tried to play (" << players[i].getHand()[atoi(selectedCard.c_str()) - 1].displayCard() << ") is not greater than " << cardTable.getTopCard()[0].displayCard() << endl;
					i--;
					i = i % numOfPlayers;
					continue;
				}
				//Check if the player has won 
				if (players[i].getHand().size() == 0) {
					gameOver = true;
					system("cls");
					cout << players[i].getName() << " wins!" << endl;
					break;
				}


				cout << "Your turn is over! " << players[(i + 1) % players.size()].getName() << " is next in 5 seconds." << endl;

				endTurn();

			}

			system("cls");

			playerId++;
			playerId = playerId % numOfPlayers;


		}
		rounds++;
	}



	return 0;

}

vector<card> selectionSort(vector<card> sortVec)
{
	for (int i = 0; i < sortVec.size(); i++)
	{
		int lowest = i;
		for (int j = i; j < sortVec.size(); j++)
		{
			if (sortVec[j].getValue() < sortVec[lowest].getValue())
			{
				lowest = j;
			}
		}
		card temp = sortVec[i];
		sortVec[i] = sortVec[lowest];
		sortVec[lowest] = temp;

	}

	return sortVec;

}


void endTurn() {

	int sleepTimer = 10;
	system("cls");
	for (int x = 2; x >= 1; x--)
	{
		cout << to_string(x) << '\r';
		_sleep(1000);
	}
	_sleep(sleepTimer);
}

vector<string> splitString(string stringThing, char splitter) {
	vector<string> splitStrings;
	int k = 0;
	for (int i = 0; i < stringThing.size(); i++) {
		if (stringThing[i] == splitter) {
			splitStrings.push_back(stringThing.substr(k, i - k));
			k = i + 1;
		}

	}
	splitStrings.push_back(stringThing.substr(k, stringThing.size() - k));
	return splitStrings;

}

vector<player> startGame(vector<player> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < cardsPerPlayer; j++) {
			vec[i].addCard(cardDeck.draw());
			
		}
		
	}
	
	return vec;

}

void placeCard(vector<card> cardToPlaceInVector) {
	cardTable.setTopCard(cardToPlaceInVector);
}

void displayPlayerNames() {
	for (int i = 0; i < players.size(); i++)
		cout << players[i].playerName << endl;

}