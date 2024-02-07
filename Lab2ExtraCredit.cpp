//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//* Program name    : Lab2ExtraCredit					    * 
//*									    * 
//* Written by      : Anthony Cantu					    * 
//*									    * 
//* Purpose         : Playing card game, checks for straight, flush,	    *
//*		      full house, and 4 of a kind. Ability to replace	    *
//*		      and discard cards drawn from a deck.                  * 
//*									    * 
//* Inputs          : User answers prompts to discard and replace cards	    *
//*		      or to continue a game after a 4 of a kind if	    *
//*		      possible.						    * 
//*									    * 
//* Outputs         : Display entry request and displays currently	    *
//*		      held hand and if user would like to discard	    *
//*		      or replace the cards in hand with a drawn card	    * 
//*									    * 
//* Calls           : No internal or external calls			    * 
//*									    * 
//* Structure       : BEGIN						    * 
//*                        Straight line code no sub-processes		    * 
//*                   STOP						    * 
//*                        End of Program				    * 
//*									    * 
//*-------------------------------------------------------------------------* 
//* Collaboration   : Got help from Professor Urrutia			    *
//*									    *
//*		      Additional help from classmates:			    *
//*			Daniel Balolong					    *
//*			   - Exchanged ideas and methods		    *
//*			     on how to accomplish the goal of		    *
//*			     this application				    *
//*									    *
//*		       String::at explanation				    *
//*			 https://cplusplus.com/reference/string/string/at/  *
//*			 used to return a character from given		    *
//*			 position of a string				    * 
//*									    * 
//*-------------------------------------------------------------------------* 
//* Change Log:								    * 
//*                         Revision					    * 
//*       Date    Changed  Rel Ver Mod Purpose				    * 
//* 10/03/23      acantu 000.000.000 Initial release of program		    * 
//*									    * 
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

//Prototypes
void dealCards();
int dealSingleCard();
void currentCards();
bool checkWinningCards();
bool checkFlush();
bool checkFourOfKind();
void checkUsedRank(string draw);
void possibleFourOfKind();
bool checkFullHouse();
bool checkStraight();

//Variables
const string DECK[52] = {
				"2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AH",	//Hearts
				"2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AC",	//Clubs
				"2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD", "AD",	//Diamonds
				"2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AS",	//Spades
};
string usedCards[52] = { " " };		//Initalize an array of used cards with 52 length
int cardsDealt = 0;			//Total number of cards that have been delt
int hand[5];				//Array to store the hand held
int usedRank[13] = { 0 };		//Array to store the ranks drawn from the deck
bool winner = false;			//Boolean status for if a winning hand has been declared, initialize to false
bool fourOfKindPossible = false;	//Boolean status for if a four of a kind is still possible in the deck
char q;					//Placeholder for pausing application

int main()
{
	string decission;		//String to hold user input for prompts
	int newCard;			//Interger to temporarily hold the new card drawn
	bool validInput = false;	//Boolean status for user input

	srand(time(0));

	cout << "Anthony Cantu\t" << "Lab2ExtraCredit\t" << "Lab2ExtraCredit.exe" << endl;
	cout << setfill(' ');

	dealCards(); //Initialize hand

	cout << "First 5 cards -> "
		<< DECK[hand[0]] << ", " << DECK[hand[1]] << ", " << DECK[hand[2]]
			<< ", " << DECK[hand[3]] << ", " << DECK[hand[4]];

	winner = checkWinningCards(); //Check initiale draw for winning cards

	cout << endl;

	while (!winner)
	{
		cout << endl; //Line Break

		if(!validInput)	//If validInput does not equal false, do not deal a new card
			newCard = dealSingleCard();

		while (!validInput)
		{
			cout << setw(2) << cardsDealt << "th card -> " << DECK[newCard] << endl;
			cout << setw(43) << "(D)iscard or (R1, 2, 3, 4, 5)eplace ? ==> ";

			cin >> decission;
			if (decission == "D" || decission == "d")
			{
				cout << endl; //Line Break

				cout << setw(2) << cardsDealt << "th card -> " << DECK[newCard]
					<< " Discarded." << endl;
				validInput = true;
			}
			else if (decission == "R1" || decission == "r1")	//Replace new card with first card in hand.
			{
				cout << "Replacing card " << DECK[hand[0]] << " with " << DECK[newCard] << endl;
				hand[0] = newCard;
				validInput = true;
			}
			else if (decission == "R2" || decission == "r2")
			{
				cout << "Replacing card " << DECK[hand[1]] << " with " << DECK[newCard] << endl;
				hand[1] = newCard;
				validInput = true;
			}
			else if (decission == "R3" || decission == "r3")
			{
				cout << "Replacing card " << DECK[hand[2]] << " with " << DECK[newCard] << endl;
				hand[2] = newCard;
				validInput = true;
			}
			else if (decission == "R4" || decission == "r4")
			{
				cout << "Replacing card " << DECK[hand[3]] << " with " << DECK[newCard] << endl;
				hand[3] = newCard;
				validInput = true;
			}
			else if (decission == "R5" || decission == "r5")
			{
				cout << "Replacing card " << DECK[hand[4]] << " with " << DECK[newCard] << endl;
				hand[4] = newCard;
				validInput = true;
			}
			else
			{
				cout << endl << "Invalid entry, please try again!" << endl << endl;
				currentCards();
				cout << endl; //Line Break
			}
		}
		validInput = false;				//Set validInput to false if code made it past the while loop

		cout << endl; //Line Break
		currentCards();					//Display current cards
		winner = checkWinningCards();	//Check to see if winning hand is held

		while (fourOfKindPossible)		//Is four of a kind is still possible in the deck?
		{
			cout << "Do you wish to continue (y/n)? ";
			cin >> decission;
			if (decission == "Y" || decission == "y")
			{
				winner = false;
				fourOfKindPossible = false;
				dealCards();
				cout << endl; //Line Break
				currentCards();
			}
			else if (decission == "N" || decission == "n")
			{
				cout << "Press any key to Exit.";
				cin.ignore(2, '\n');
				cin.get(q);
				return 0;
			}
			else
			{
				cout << "Invalid entry, please try again!" << endl;
			}
		}
	}
	cout << "Press any key to Exit.";
	cin.ignore(2, '\n');
	cin.get(q);
	return 0;
}

bool checkWinningCards() //Function to check hand for a winning hand
{
	if (checkFlush())			//Check for a flush
	{
		cout << "Flush!" << endl
			<< "Winning Hand!" << endl;
		possibleFourOfKind();
		return true;
	}
	else if (checkFourOfKind())	//Check for a four of a kind
	{
		cout << "Four of a Kind!" << endl
			<< "Winning Hand!" << endl;
		possibleFourOfKind();
		return true;
	}
	else if (checkFullHouse())	//Check for a full house
	{
		cout << "Full House!" << endl
			<< "Winning Hand!" << endl;
		possibleFourOfKind();
		return true;
	}
	else if (checkStraight())	//Check for a straight
	{
		cout << "Straight!" << endl
			<< "Winning Hand!" << endl;
		possibleFourOfKind();
		return true;
	}
	else
		return false;
}

bool checkStraight() //** Collab with Daniel Balolong **
{
	int tempHand[5];							//Temporary array to store hand
	int temp;									//Temoporary interger to hold card
	int counter = 0;

	for (int i = 0; i < 5; i++)					//Copy hand into temporary hand
		tempHand[i] = hand[i];

	int multiplier;
	for (int i = 0; i < 5; i++)					//Loop through hand to check ranks
	{
		multiplier = 0;							//Reset multiplier back to 0
		for (int x = 0; x < 13; x++)			//Loop through all possible ranks and assign tempHand to its rank
		{
			if (tempHand[i] == 0 + multiplier || tempHand[i] == 13 + multiplier ||
				tempHand[i] == 26 + multiplier || tempHand[i] == 39 + multiplier)
			{
				tempHand[i] = 2 + multiplier;
				break;
			}
			multiplier++;
		}
	}

	for (int i = 0; i < 5; i++)					//Iterate through amount of elements
	{
		for (int j = 0; j < 5 - i - 1; j++)		//Iterate through each execept already sorted
		{
			if (tempHand[j] > tempHand[j + 1])	//Compare adjacent elements
			{
				temp = tempHand[j];
				tempHand[j] = tempHand[j + 1];
				tempHand[j + 1] = temp;
			}
		}
	}

	for (int y = 0; y < 5; y++)					//Check if five cards are sequential
	{
		if ((tempHand[y] + 1) == tempHand[y + 1])
		{
			counter++;
			if (counter == 4)
				return true;
		}
		else
			counter = 0;
	}
	return false;
}

void possibleFourOfKind() //Function to see if a four of a kind is still possible in the deck
{
	string rankName[13] = {
	"2", "3", "4", "5", "6", "7", "8", "9",
	"10", "J", "Q", "K", "A"
	};

	for (int i = 0; i < 13; i++)
		if (usedRank[i] == 0)	//If there are ranks that have not been drawn from the deck
			fourOfKindPossible = true;

	if (fourOfKindPossible)
	{
		cout << "4 of a kind are still possible for the: ";
		for (int i = 0; i < 13; i++)
			if (usedRank[i] == 0)
				cout << rankName[i] << " ";
	}
}

void checkUsedRank(string draw) //Checks to see which ranks have been drawn
{
	switch (draw.at(0))
	{
	case '2': usedRank[0]++; break;
	case '3': usedRank[1]++; break;
	case '4': usedRank[2]++; break;
	case '5': usedRank[3]++; break;
	case '6': usedRank[4]++; break;
	case '7': usedRank[5]++; break;
	case '8': usedRank[6]++; break;
	case '9': usedRank[7]++; break;
	case '1': usedRank[8]++; break;
	case 'J': usedRank[9]++; break;
	case 'Q': usedRank[10]++; break;
	case 'K': usedRank[11]++; break;
	case 'A': usedRank[12]++; break;
	}
}

bool checkFourOfKind() //Function to check for a four of a kind
{
	int rank[13]; 

	for (int i = 0; i < 13; i++)
		rank[i] = 0;

	for (int i = 0; i < 5; i++)
	{
		switch (DECK[hand[i]].at(0))
		{
		case '2': rank[0]++; break;
		case '3': rank[1]++; break;
		case '4': rank[2]++; break;
		case '5': rank[3]++; break;
		case '6': rank[4]++; break;
		case '7': rank[5]++; break;
		case '8': rank[6]++; break;
		case '9': rank[7]++; break;
		case '1': rank[8]++; break;
		case 'J': rank[9]++; break;
		case 'Q': rank[10]++; break;
		case 'K': rank[11]++; break;
		case 'A': rank[12]++; break;
		}
	}

	for (int i = 0; i < 13; i++)
		if (rank[i] == 4) 
			return true;

	return false;
}

bool checkFullHouse() //Function to check for a full house
{
	int rank[13]; 

	for (int i = 0; i < 13; i++)
		rank[i] = 0;

	for (int i = 0; i < 5; i++)
	{
		switch (DECK[hand[i]].at(0))
		{
		case '2': rank[0]++; break;
		case '3': rank[1]++; break;
		case '4': rank[2]++; break;
		case '5': rank[3]++; break;
		case '6': rank[4]++; break;
		case '7': rank[5]++; break;
		case '8': rank[6]++; break;
		case '9': rank[7]++; break;
		case '1': rank[8]++; break;
		case 'J': rank[9]++; break;
		case 'Q': rank[10]++; break;
		case 'K': rank[11]++; break;
		case 'A': rank[12]++; break;
		}
	}

	bool partOne = false;
	for (int i = 0; i < 13; i++)	//Do three cards in hand match?
		if (rank[i] == 3)
			partOne = true;

	if(partOne)
		for(int i = 0; i < 13; i++) //Lets check for two more, if three match
			if(rank[i] == 2)
				return true;

	return false;
}

bool checkFlush() //Function to check for a flush
{
	//Can I simplify with a loop?
	if ((hand[0] >= 0 && hand[0] <= 12) && (hand[1] >= 0 && hand[1] <= 12)				//Check Hearts Flush
		&& (hand[2] >= 0 && hand[2] <= 12) && (hand[3] >= 0 && hand[3] <= 12)
		&& (hand[4] >= 0 && hand[4] <= 12))
		return true;
	else if ((hand[0] >= 13 && hand[0] <= 25) && (hand[1] >= 13 && hand[1] <= 25)		//Check Clubs Flush
		&& (hand[2] >= 13 && hand[2] <= 25) && (hand[3] >= 13 && hand[3] <= 25)
		&& (hand[4] >= 13 && hand[4] <= 25))
		return true;
	else if ((hand[0] >= 26 && hand[0] <= 38) && (hand[1] >= 26 && hand[1] <= 38)		//Check Diamonds Flush
		&& (hand[2] >= 26 && hand[2] <= 38) && (hand[3] >= 26 && hand[3] <= 38)
		&& (hand[4] >= 26 && hand[4] <= 38))
		return true;
	else if ((hand[0] >= 39 && hand[0] <= 51) && (hand[1] >= 39 && hand[1] <= 51)		//Check Spades Flush
		&& (hand[2] >= 39 && hand[2] <= 51) && (hand[3] >= 39 && hand[3] <= 51)
		&& (hand[4] >= 39 && hand[4] <= 51))
		return true;
	else
		return false;
}

void currentCards() //Function to display current held hand
{
	cout << "Current 5 cards -> " << DECK[hand[0]] << ", " << DECK[hand[1]]
		<< ", " << DECK[hand[2]] << ", " << DECK[hand[3]] << ", " << DECK[hand[4]]
		<< endl;
}

bool checkDealtCard(string dealt, string used[]) //Check if card was already dealt before
{
	for (int i = 0; i < 52; i++)
	{
		if (used[i] == dealt)
			return true;
	}
	return false;
}

int dealSingleCard()
{
	int dealerCard;
	dealerCard = rand() % 52 + 1;	//Draw a card

	if (cardsDealt >= 52)			//Reached end of deck?
	{
		cout << "Reached the end of the deck!" << endl
			<< "Press any key to Exit.";

		cin.ignore(2, '\n');
		cin.get(q);
		exit(0);
	}

	bool cardDrawn = false;
	while (!cardDrawn)
	{
		if (cardsDealt > 51)								//If cards dealt is greater than 51, break from loop
			break;

		if (!checkDealtCard(DECK[dealerCard], usedCards))	//Why is this underlined green? //If duplicate card dealt returns false, continue.
		{
			usedCards[cardsDealt] = DECK[dealerCard];		//Add drawn card to used card array
			checkUsedRank(DECK[dealerCard]);				//Add to used ranks, used for 4 of a kind
			cardsDealt++;									//Add to number of cards dealt
			cardDrawn = true;								//Drawn card is true
			return dealerCard;								//Return true if able to draw a new card
		}
		else
		{
			if (cardsDealt == 51)						
				cardsDealt++;

			dealerCard = rand() % 52 + 1;					//Draw another card if duplicate card was drawn
		}
	}
	
}

void dealCards()	//Deal cards to hand
{
	for (int i = 0; i < 5; i++)
	{
		hand[i] = dealSingleCard();
	}
}
