#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct card_s {
	char color[7];
	int value;
	char action[15];
	struct card_s* pt;
} card;

card* deckHead = NULL;
card* centerLineHead = NULL;
int wasCardPlayed = 0;
int centerLineSize = 0;
int turnOver = 0;
int yesOrNo = 0;
int unableToMatch = 0;
int numMatches = 0;
int colorMatch = 0;
int doubleColorMatch = 0;
int playernum = 0;
card* centerLineTemp[10];

void removeCard(card** head, int position);
card* getNext(card* thisCard);
void swap(card* ptr, int i, int j);
int randGen(int count);
void shuffleDeck(int size);
void createCard(card* newCard, int value, char* color, char* action);
void initializeDeck();
void loadDeck(FILE* inFile);
void drawHand(card** deckhead, card** playerHead);
void drawCard(card** deckhead, card** playerHead);
void printHand(card* playerHead);
void initializeCenterLine(card** deckhead, card** centerLine);
int cardsinhand(card* headnode);
card* getCard(card** head, int index);
int numberChoice(card* centerLine);
void addCard(card** centerLine, card* newCard);
void copyCard(card** centerLine, card* newCard, card* cardToCopy);
void toBeRemoved(card** centerLine, int i);
void removeMatches(card** centerLine);
void takeTurn(int numChoice, card** player, card** centerLine, card* centerLine0, int p, int i, int choice1, int choice2);
int countScore(card** player);


//Remove card from deck, playerhand, or centerline
void removeCard(card** head, int pos) {
	if (*head == NULL)
		return;

	card* temp = *head;

	if (pos == 0) {
		*head = temp->pt;

		free(temp);
		return;
	}

	for (int i = 0; temp != NULL && i < pos - 1; i++)
		temp = temp->pt;

	if (temp == NULL || temp->pt == NULL)
		return;

	card* next = temp->pt->pt;
	free(temp->pt);
	temp->pt = next;
}


//Returns the next card
card* getNext(card* thisCard) {
	return thisCard->pt;
}


//Used to swap the location of two card positions, used for shuffling cards
void swap(card* ptr, int i, int j) {
	card* newi = ptr;
	card* newj = ptr;
	int tempValue;
	char tempColor[7];
	char tempAction[15];

	for (int k = 0; k < i; k++) {
		newi = getNext(newi);
	}
	for (int l = 0; l < j; l++) {
		newj = getNext(newj);
	}

	tempValue = newi->value;
	newi->value = newj->value;
	newj->value = tempValue;

	strcpy(tempColor, newi->color);
	strcpy(newi->color, newj->color);
	strcpy(newj->color, tempColor);

	strcpy(tempAction, newi->action);
	strcpy(newi->action, newj->action);
	strcpy(newj->action, tempAction);
}


//Generates a random number, used for shuffling cards
int randGen(int count) {
	double frac;
	frac = (double)rand() / ((double)RAND_MAX + 1);
	return floor(count * frac);
}


//Function to shuffle the deck
void shuffleDeck(int size) {
	srand((int)time(NULL));
	for (int i = 0; i < 1000; ++i) {
		swap(deckHead, randGen(108), randGen(108));
	}
}


//Creates a new card and adds it to the deck
void createCard(card* newCard, int value, char* color, char* action) {
	
	card* temp = deckHead;

	newCard->value = value;
	strcpy(newCard->color, color);
	strcpy(newCard->action, action);
	newCard->pt = NULL;

	if (deckHead == NULL) {
		deckHead = newCard;
	}
	else {
		while (temp->pt != NULL) {
			temp = temp->pt;
		}
		temp->pt = newCard;
	}
}


//Creates the deck, if not scanned in from a file
void initializeDeck() {
	char cardColor[7] = "yellow";
	char cardAction[15] = "none";

	for (int i = 0; i < 108; i++) {
		card* newCard = (card*)malloc(sizeof(card));

		if (i < 24) {
			if (i < 3)			
				createCard(newCard, 1, cardColor, cardAction);
			else if (i < 6)
				createCard(newCard, 3, cardColor, cardAction);
			else if (i < 9)
				createCard(newCard, 4, cardColor, cardAction);
			else if (i < 12)
				createCard(newCard, 5, cardColor, cardAction);
			else if (i < 14)
				createCard(newCard, 6, cardColor, cardAction);
			else if (i < 16)
				createCard(newCard, 7, cardColor, cardAction);
			else if (i < 18)
				createCard(newCard, 8, cardColor, cardAction);
			else if (i < 20)
				createCard(newCard, 9, cardColor, cardAction);
			else if (i < 22)
				createCard(newCard, 10, cardColor, cardAction);
			else if (i < 24) {
				strcpy(cardAction, "AnyNumber");

				createCard(newCard, 11, cardColor, cardAction);
			}				
		}
		else if (i < 48) {
			strcpy(cardColor, "red");
			strcpy(cardAction, "none");

			if (i < 27)
				createCard(newCard, 1, cardColor, cardAction);
			else if (i < 30)
				createCard(newCard, 3, cardColor, cardAction);
			else if (i < 33)
				createCard(newCard, 4, cardColor, cardAction);
			else if (i < 36)
				createCard(newCard, 5, cardColor, cardAction);
			else if (i < 38)
				createCard(newCard, 6, cardColor, cardAction);
			else if (i < 40)
				createCard(newCard, 7, cardColor, cardAction);
			else if (i < 42)
				createCard(newCard, 8, cardColor, cardAction);
			else if (i < 44)
				createCard(newCard, 9, cardColor, cardAction);
			else if (i < 46)
				createCard(newCard, 10, cardColor, cardAction);
			else if (i < 48) {
				strcpy(cardAction, "AnyNumber");

				createCard(newCard, 11, cardColor, cardAction);
			}
		}	
		else if (i < 72) {
			strcpy(cardColor, "green");
			strcpy(cardAction, "none");

			if (i < 51)
				createCard(newCard, 1, cardColor, cardAction);
			else if (i < 54)
				createCard(newCard, 3, cardColor, cardAction);
			else if (i < 57)
				createCard(newCard, 4, cardColor, cardAction);
			else if (i < 60)
				createCard(newCard, 5, cardColor, cardAction);
			else if (i < 62)
				createCard(newCard, 6, cardColor, cardAction);
			else if (i < 64)
				createCard(newCard, 7, cardColor, cardAction);
			else if (i < 66)
				createCard(newCard, 8, cardColor, cardAction);
			else if (i < 68)
				createCard(newCard, 9, cardColor, cardAction);
			else if (i < 70)
				createCard(newCard, 10, cardColor, cardAction);
			else if (i < 72) {
				strcpy(cardAction, "AnyNumber");

				createCard(newCard, 11, cardColor, cardAction);
			}
		}
		else if (i < 96) {
		strcpy(cardColor, "blue");
		strcpy(cardAction, "none");

			if (i < 75)
				createCard(newCard, 1, cardColor, cardAction);
			else if (i < 78)
				createCard(newCard, 3, cardColor, cardAction);
			else if (i < 81)
				createCard(newCard, 4, cardColor, cardAction);
			else if (i < 84)
				createCard(newCard, 5, cardColor, cardAction);
			else if (i < 86)
				createCard(newCard, 6, cardColor, cardAction);
			else if (i < 88)
				createCard(newCard, 7, cardColor, cardAction);
			else if (i < 90)
				createCard(newCard, 8, cardColor, cardAction);
			else if (i < 92)
				createCard(newCard, 9, cardColor, cardAction);
			else if (i < 94)
				createCard(newCard, 10, cardColor, cardAction);
			else if (i < 96) {
				strcpy(cardAction, "AnyNumber");
				createCard(newCard, 11, cardColor, cardAction);
			}
		}
		else if (i >= 96) {
			strcpy(cardColor, "black");
			strcpy(cardAction, "AnyColor");

			createCard(newCard, 2, cardColor, cardAction);
		}
	}
}


//Loads a deck that's given from an input file
void loadDeck(FILE* inFile) {
	int count = 0;

	while (count != 108) {
		char cardColor[7];
		char cardAction[15];
		int cardValue = 0;

		fscanf(inFile, "%s %d %s\n", &cardColor, &cardValue, &cardAction);

		card* newCard = (card*)malloc(sizeof(card));
		createCard(newCard, cardValue, cardColor, cardAction);

		count++;
	}
}


//draws a hand of 7 cards for each player
void drawHand(card** deckhead, card** playerHead) {
	card* temp = *deckhead;
	card* decktemp = *deckhead;
	card* playertemp = *playerHead;
	for (int i = 0; i < 6; ++i) {
		*deckhead = (*deckhead)->pt;
	}
	decktemp = *deckhead;
	*deckhead = (*deckhead)->pt;
	decktemp->pt = NULL;
	if (*playerHead == NULL) {
		*playerHead = temp;
	}
	else {
		while (playertemp->pt != NULL) {
			playertemp = getNext(playertemp);
		}
		playertemp->pt = temp;
	}
}


//draws a card from the deck
void drawCard(card** deckhead, card** playerHead) {
	card* temp = *deckhead;
	card* decktemp = *deckhead;
	card* playertemp = *playerHead;

	*deckhead = (*deckhead)->pt;
	decktemp->pt = NULL;

	while (playertemp->pt != NULL) {
		playertemp = getNext(playertemp);
	}
	playertemp->pt = temp;
}


//prints the nodes of a list passed in
void printHand(card* playerHead) {
	card* temp = playerHead;

	while (temp != NULL) {
		if (temp->pt == NULL) {
			if (temp->value == 11)
				printf("# %s", temp->color);
			else
				printf("%d %s", temp->value, temp->color);
			temp = temp->pt;
		}
		else {
			if (temp->value == 11)
				printf("# %s, ", temp->color);
			else
				printf("%d %s, ", temp->value, temp->color);
			temp = temp->pt;
		}
	}
}


//Create's a center line by drawing two cards from the deck
void initializeCenterLine(card** deckhead, card** centerLine) {
	card* temp = *deckhead;
	card* decktemp = *deckhead;
	card* centerTemp = *centerLine;
	for (int i = 0; i < 1; ++i) {
		*deckhead = (*deckhead)->pt;
	}
	decktemp = *deckhead;
	*deckhead = (*deckhead)->pt;
	decktemp->pt = NULL;
	if (*centerLine == NULL) {
		*centerLine = temp;
	}
	else {
		while (centerTemp->pt != NULL) {
			centerTemp = getNext(centerTemp);
		}
		centerTemp->pt = temp;
	}
}


//Returns the number of cards in a hand/center line
int cardsinhand(card* headnode) {
	card* temp = headnode;
	int count = 0;
	while (temp != NULL) {
		count = count + 1;
		temp = temp->pt;
	}
	return count;
}


//Returns the card at a chosen index
card* getCard(card** head, int index) {

	card* current = *head;

	int count = 0;
	while (current != NULL) {
		if (count == index)
			return (current);
		count++;
		current = current->pt;
	}
}


//Prompts the user for how many cards they want to play on a center line card
int numberChoice(card* centerLine) {
	int numChoice = 0;

	if (centerLine->value == 11)
		printf("\n\n\n\tHow many cards do you want to play on # %s: ", centerLine->color);
	else
		printf("\n\n\n\tHow many cards do you want to play on %d %s: ", centerLine->value, centerLine->color);
	scanf("%d", &numChoice);

	if ((numChoice < 0) || (numChoice > 2)) {
		printf("Invalid Input. Please try again: ");
		numberChoice(centerLine);
	}
	else {
		return numChoice;
	}
}


//Adds a given card to the end of the centerLine
void addCard(card** centerLine, card* newCard) {

	card* temp = *centerLine;

	if (centerLine == NULL) {
		*centerLine = newCard;
	}
	else {
		while (temp->pt != NULL) {
			temp = temp->pt;
		}
		temp->pt = newCard;
	}
}


//Copies the card details of cardToCopy over to newCard
void copyCard(card** centerLine, card* newCard, card* cardToCopy) {
	card* temp = *centerLine;

	newCard->value = cardToCopy->value;
	strcpy(newCard->color, cardToCopy->color);
	strcpy(newCard->action, cardToCopy->action);
	newCard->pt = NULL;

	if (*centerLine == NULL) {
		*centerLine = newCard;
	}
	else {
		while (temp->pt != NULL) {
			temp = temp->pt;
		}
	}
}


//Changes the value of a matched card to -1 so that my "removeMatches" fuction knows which cards to remove
void toBeRemoved(card** centerLine, int i) {
	card* current = *centerLine;
	i--;
	int count = 0;
	while (current != NULL) {
		if (count == i)
			current->value = -1;
		count++;
		current = current->pt;
	}
}


//Removes any cards that were matches from the center line
void removeMatches(card** centerLine) {
	int cardsRemoved = 0;

	while (cardsRemoved != numMatches) {
		card* temp;

		if (cardsinhand(*centerLine) == 1)
			drawCard(&deckHead, centerLine);

		if ((*centerLine)->value == -1)
		{
			temp = *centerLine;
			*centerLine = (*centerLine)->pt;
			free(temp);
			cardsRemoved++;
		}
		else
		{
			card* current = *centerLine;
			while (current->pt != NULL)
			{
				if (current->pt->value == -1) {
					temp = current->pt;
					current->pt = current->pt->pt;
					free(temp);
					cardsRemoved++;
					break;
				}
				else
					current = current->pt;
			}
		}

		for (int i = 0; i < colorMatch; i++)
			drawCard(&deckHead, centerLine);

		for (int j = 0; j < doubleColorMatch; j++)
			drawCard(&deckHead, centerLine);

		if (cardsinhand(*centerLine) < 2)
			drawCard(&deckHead, centerLine);
	}
}


//This is where each player takes their turn playing cards
void takeTurn(int numChoice, card** player, card** centerLine, card* centerLine0, int p, int i, int choice1, int choice2) {
	
	for (i = 1; i <= cardsinhand(*centerLine); ++i) {
		int correctChoice = 0;
		printf("\nPlayer %d's hand: ", p + 1);
		printHand(*player);
		printf("\n\nCenter Line: ");
		for (int k = 0; k < cardsinhand(*centerLine); k++) {
			if (k == cardsinhand(*centerLine) - 1) {
				if (centerLineTemp[k]->value == 11)
					printf("# %s", centerLineTemp[k]->color);
				else
					printf("%d %s", centerLineTemp[k]->value, centerLineTemp[k]->color);
			}
			else {
				if (centerLineTemp[k]->value == 11)
					printf("# %s, ", centerLineTemp[k]->color);
				else
					printf("%d %s, ", centerLineTemp[k]->value, centerLineTemp[k]->color);
			}
		}

		numChoice = numberChoice(centerLine0);

		while (numChoice == 1 || numChoice == 2 || numChoice == 0) {
			if (numChoice == 1) {
				printf("\n\tSelect your card from 1-%d: ", cardsinhand(*player));
				scanf("%d", &choice1);
				card* userChoice1 = getCard(player, choice1 - 1);

				do {
					correctChoice = 0;
					if ((userChoice1->value == centerLine0->value) || strcmp(centerLine0->action, "AnyNumber") == 0) {
						if (strcmp(userChoice1->color, centerLine0->color) == 0 || (strcmp(userChoice1->action, "AnyColor") == 0 || strcmp(centerLine0->action, "AnyColor") == 0))
							colorMatch++;
						numChoice = -1;
						removeCard(player, choice1 - 1);
						wasCardPlayed = 1;
						numMatches++;
						toBeRemoved(centerLine, i);
						correctChoice = 1;
					}
					else if (userChoice1->value == 11) {
						if (strcmp(userChoice1->color, centerLine0->color) == 0 || (strcmp(userChoice1->action, "AnyColor") == 0 || strcmp(centerLine0->action, "AnyColor") == 0))
							colorMatch++;
						numChoice = -1;
						removeCard(player, choice1 - 1);
						wasCardPlayed = 1;
						numMatches++;
						toBeRemoved(centerLine, i);
						correctChoice = 1;
					}
					else {
						printf("\n\tThat selection does not total to the center card, %d %s. Please select again: ", centerLine0->value, centerLine0->color);
						numChoice = numberChoice(centerLine0);
						printf("\n\tSelect your card from 1-%d: ", cardsinhand(*player));
						scanf("%d", &choice1);
						userChoice1 = getCard(player, choice1 - 1);
					}
				} while (correctChoice != 1);
			}
			else if (numChoice == 2) {
				printf("\n\tSelect your cards from 1-%d: ", cardsinhand(*player));
				scanf("%d,%d", &choice1, &choice2);
				card* userChoice1 = getCard(player, choice1 - 1);
				card* userChoice2 = getCard(player, choice2 - 1);

				do {
					correctChoice = 0;
					if ((userChoice1->value + userChoice2->value) == centerLine0->value || strcmp(centerLine0->action, "AnyNumber") == 0) {
						if ((strcmp(userChoice1->color, centerLine0->color) == 0 && strcmp(userChoice2->color, centerLine0->color) == 0) || (strcmp(userChoice1->color, centerLine0->color) == 0 && strcmp(userChoice2->action, "AnyColor") == 0) || (strcmp(userChoice1->action, "AnyColor") == 0 && strcmp(userChoice2->color, centerLine0->color) == 0) || (strcmp(userChoice1->action, "AnyColor") == 0 && strcmp(userChoice2->color, "AnyColor") == 0))
							doubleColorMatch++;
						numChoice = -1;
						removeCard(player, choice1 - 1);
						removeCard(player, choice2 - 2);
						wasCardPlayed = 1;
						numMatches++;
						toBeRemoved(centerLine, i);
						correctChoice = 1;
					}
					else if (((userChoice1->value == 11 || userChoice2->value == 11) && (userChoice1->value < centerLine0->value || userChoice2->value < centerLine0->value)) || (strcmp(centerLine0->action, "AnyNumber") == 0 && (userChoice1->value < centerLine0->value || userChoice2->value < centerLine0->value))) {
						if ((strcmp(userChoice1->color, centerLine0->color) == 0 && strcmp(userChoice2->color, centerLine0->color) == 0) || (strcmp(userChoice1->color, centerLine0->color) == 0 && strcmp(userChoice2->action, "AnyColor") == 0) || (strcmp(userChoice1->action, "AnyColor") == 0 && strcmp(userChoice2->color, centerLine0->color) == 0))
							doubleColorMatch++;
						numChoice = -1;
						removeCard(player, choice1 - 1);
						removeCard(player, choice2 - 2);
						wasCardPlayed = 1;
						numMatches++;
						toBeRemoved(centerLine, i);
						correctChoice = 1;
					}
					else {
						printf("\n\tThat selection does not total to the center card, %d %s. Please select again:  ", centerLine0->value, centerLine0->color);
						numChoice = numberChoice(centerLine0);
						printf("\n\tSelect your cards from 1-%d: ", cardsinhand(*player));
						scanf("%d,%d", &choice1, &choice2);
						userChoice1 = getCard(player, choice1 - 1);
						userChoice2 = getCard(player, choice2 - 1);
					}
				} while (correctChoice != 1);
			}
			else if (numChoice == 0) {
				if (wasCardPlayed == 0 && i == centerLineSize) {
					int anykey = 0;
					do {
						printf("\n\tYou were unable to match any cards on the center line. Press 1 to draw a card: ");
						scanf("%d", &anykey);
					} while (anykey != 1);
					drawCard(&deckHead, player);
					card* drawnCard = getCard(player, cardsinhand(*player));
					int matchLoc = -1;

					for (int k = 0; k < cardsinhand(*centerLine); k++) {
						if (drawnCard->value == getCard(centerLine, k)->value)
							matchLoc = k;
					}

					if (matchLoc != -1 || drawnCard-> value == 11) {
						int playCard = 0;
						if (drawnCard->value == 11) {
							do {
								printf("\n\tYour new card is # %s. It matches %d %s on the center line. Press 1 to play it: ", drawnCard->color, getCard(centerLine, matchLoc)->value, getCard(centerLine, matchLoc)->color);
								scanf("%d", &playCard);
							} while (playCard != 1);
						}
						else {
							do {
								printf("\n\tYour new card is %d %s. It matches %d %s on the center line. Press 1 to play it: ", drawnCard->value, drawnCard->color, getCard(centerLine, matchLoc)->value, getCard(centerLine, matchLoc)->color);
								scanf("%d", &playCard);
							} while (playCard != 1);
						}
						removeCard(player, cardsinhand(*player));
						wasCardPlayed = 1;
						numMatches++;
						toBeRemoved(centerLine, matchLoc+1);
					}
					else {
						int playCard = 0;
						do {
							playCard = 0;
							printf("\n\tYour new card is %d %s, and is unable to be played. Press 1 to continue: ", drawnCard->value, drawnCard->color);
							scanf("%d", &playCard);
						} while (playCard != 1);
						numChoice = -1;
						unableToMatch = 1;
					}
				}
				else
					numChoice = -1;
			}
			if (i == centerLineSize) {
				if (colorMatch > 0) {
					if (colorMatch == 1)
						printf("\n\tYou made 1 color match!\n");
					else
						printf("\n\tYou made %d color matches!\n", colorMatch);
					for (int l = 0; l < colorMatch; l++) {
						if (player == NULL)
							break;
						do {
							printf("\n\tYour cards: ");
							printHand(*player);
							printf("\n\n\tChoose a card to play in the center line for your color match, 1-%d: ", cardsinhand(*player));
							scanf("%d", &numChoice);
						} while (numChoice < 1 && numChoice > cardsinhand(*player));
						numChoice--;
						card* newCard = (card*)malloc(sizeof(card));
						copyCard(centerLine, newCard, getCard(player, numChoice));
						addCard(centerLine, newCard);
						removeCard(player, numChoice);
						numChoice = -1;
						i = cardsinhand(*centerLine);
					}
				}
				if (doubleColorMatch > 0) {
					if (doubleColorMatch == 1)
						printf("\n\tYou made 1 double color match!\n");
					else
						printf("\n\tYou made %d double color matches!\n", doubleColorMatch);
					for (int l = 0; l < doubleColorMatch; l++) {
						if (player == NULL)
							break;
						do {
							printf("\n\tYour cards: ");
							printHand(*player);
							printf("\n\n\tChoose a card to play in the center line for your double color match, 1-%d: ", cardsinhand(*player));
							scanf("%d", &numChoice);
						} while (numChoice < 1 && numChoice > cardsinhand(*player));
						numChoice--;
						card* newCard = (card*)malloc(sizeof(card));
						copyCard(centerLine, newCard, getCard(player, numChoice));
						addCard(centerLine, newCard);
						removeCard(player, numChoice);
						numChoice = -1;
						i = cardsinhand(*centerLine);
						printf("\n\tEach player has drawn a card for your double color match.\n ");
						for (int m = 0; m < playernum; ++m) {
							drawCard(&deckHead, &player[m]);
						}
					}
				}

				printf("\n\tThere are no more center row cards to match.");
				if (unableToMatch == 1) {
					printf("\n\tYour cards: ");
					printHand(*player);
					printf("\n\n\tChoose a card to play in the center line, 1-%d: ", cardsinhand(*player));
					scanf("%d", &numChoice);
					numChoice--;
					card* newCard = (card*)malloc(sizeof(card));
					copyCard(centerLine, newCard, getCard(player, numChoice));
					addCard(centerLine, newCard);
					removeCard(player, numChoice);
					printf("\n\tNew Center Line: ");
					printHand(*centerLine);
					numChoice = -1;
					i = cardsinhand(*centerLine);
				}

				turnOver = 1;
				numChoice = -1;
			}
		}
		if (yesOrNo == 1)
			centerLine0 = getCard(centerLine, 0);
		else
			centerLine0 = getCard(centerLine, i);
		printf("\n\n\n");
	}
}


//Counts the score of a players cards at the end of a round
int countScore(card** player) {
	card* current = *player;
	int sum = 0;

	while (current != NULL) {
		if (strcmp(current->action, "none") == 0)
			sum = sum + current->value;
		else if (strcmp(current->action, "AnyColor") == 0)
			sum = sum + 20;
		else if (strcmp(current->action, "AnyNumber") == 0)
			sum = sum + 40;

		current = current->pt;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {

	FILE* inFile = fopen("Input.txt", "r");
	int shuffleChoice = 0;

	printf("Let's Play a Game of DOS!\n");
	do {
		printf("\n\tPress 1 to shuffle the DOS deck or 2 to load a deck from a file: ");
		scanf("%d", &shuffleChoice);
	} while ((shuffleChoice != 1) && (shuffleChoice != 2));

	while (shuffleChoice != 1 || shuffleChoice != 2) {
		if (shuffleChoice == 1) {
			initializeDeck();
			shuffleDeck(108);
			srand(time(NULL));
			int r = rand() % 108;
			shuffleDeck(r);
			shuffleDeck(108);
			shuffleDeck(r);
			shuffleDeck(108);
			break;
		}
		else if (shuffleChoice == 2) {
			loadDeck(inFile);
			shuffleDeck(108);
			srand(time(NULL));
			int r = rand() % 108;
			shuffleDeck(r);
			shuffleDeck(108);
			shuffleDeck(r);
			shuffleDeck(108);
			break;
		}
		else {
			printf("Invalid Input, please press 1 to shuffle the DOS deck or 2 to load a deck from a file: \n\n");
			scanf("%d", &shuffleChoice);
		}
	}

	int cont = 0;

	do {
		printf("\n\tThe deck is shuffled. Press 1 to deal the cards: ");
		scanf("%d", &cont);
	} while (cont != 1);

	playernum = 0;

	do {
		printf("\n\tPlease enter the number of players (2-6): ");
		scanf("%d", &playernum);
	} while ((playernum != 1) && (playernum != 2) && (playernum != 3) && (playernum != 4) && (playernum != 5) && (playernum != 6));

	printf("\n\n\n");
	card** player = (card**)calloc(playernum, sizeof(card*));

	for (int i = 0; i < playernum; ++i) {
		drawHand(&deckHead, &player[i]);
	}

	card** centerLine = (card**)calloc(10, sizeof(card*));

	initializeCenterLine(&deckHead, centerLine);

	int p = 0;
	int choice1 = 0;
	int choice2 = 0;
	int numChoice = -1;
	int i = 0;
	card* centerLinePos = getCard(centerLine, i);
	int winner = 0;
	int playerScore = 0;

	centerLineSize = cardsinhand(*centerLine);

	while (1 == 1) {
		centerLinePos = getCard(centerLine, 0);
		wasCardPlayed = 0;
		turnOver = 0;
		unableToMatch = 0;
		numMatches = 0;
		card* current = *centerLine;
		int count = 0;
		colorMatch = 0;
		doubleColorMatch = 0;

		do {
			cont = 0;
			printf("\t\tPlayer %d's turn! Press 1 to begin: ", p + 1);
			scanf("%d", &cont);
		} while (cont != 1);

		if (winner == 1)
			break;
		
		while (current != NULL) {
			card* newCard = (card*)malloc(sizeof(card));
			newCard->value = current->value;
			strcpy(newCard->color, current->color);
			strcpy(newCard->action, current->action);
			centerLineTemp[count] = newCard;
			count++;
			current = current->pt;
		}

		while(turnOver != 1) {
			takeTurn(numChoice, &player[p], centerLine, centerLinePos, p, i, choice1, choice2);
		}

		removeMatches(centerLine);

		centerLineSize = cardsinhand(*centerLine);

		if (p < playernum - 1) {
			p = p + 1;
		}
		else if (p = playernum) {
			p = 0;
		}

		for (int i = 0; i < playernum; ++i) {
			if (player[i] == NULL) {
				printf("Player %d wins!\n", i + 1);
				winner = 1;
				for (int j = 0; j < playernum; j++) {
					if (player[j] == NULL)
						continue;
					else {
						playerScore = 0;
						playerScore = countScore(&player[j]);
						printf("Player %d finished the round with %d points.\n", j + 1, playerScore);
					}
				}

				return 0;
			}
		}
	}

	return 0;
}