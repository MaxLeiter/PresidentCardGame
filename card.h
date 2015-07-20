#ifndef CARD_H
#define CARD_H

#include<iostream>
#include <string>
using namespace std;

class card
{
private:
	int value;
	char suit;

	
public:


	card()
	{
		value = 14;
		suit = 'S';

	}
	card(int v, char s)
	{
		value = v;
		suit = s;
	}
	char getSuit() {
		return suit;
	}
	void setSuitAndValue(int v, char s) {
		value = v;
		suit = s;
	}
	int getValue() {
		return value;
	}

	int getCardValue() {
		if (suit = 'S'){
			return value * 13;
		}
		else if (suit = 'H'){
			return value * 13 - 1;
		}
		else if (suit = 'D'){
			return value * 13 - 2;
		}
		else{
			return value * 13 - 3;
		}
		
	}

	string displayCard()
	{
		string displayValue = "[";
		if (value < 11)
		{
			displayValue += to_string(value);
		}
		if (value == 11)
		{
			displayValue += "J";
		}
		if (value == 12)
		{
			displayValue += "Q";
		}
		if (value == 13)
		{
			displayValue += "K";
		}
		if (value == 14)
		{
			displayValue += "A";
		}
		displayValue += "-";
		displayValue += suit;
		displayValue += "]";


		return displayValue;
	}

	
};
#endif