#include "DeckNew.h"
#include <iostream>
#include <iomanip>

void printCards(Deck cards) {                       //функция вывода карт в колоде
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << j + 1 << ") " << cards.getRank(j) << " " << cards.getSuit(j) << "\n";
	};
};
void printCardsLine(Deck cards) {                   //функция вывода карт в колоде в линию
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << std::setw(2) << cards.getSuit(j) << " ";
	};
	std::cout << '\n';
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << std::setw(2) << cards.getRank(j) << " ";
	};
	std::cout << '\n';
};



int main()
{
	srand(time(0));

	int game = 2;

	int countCard = 10;
	Deck myDeck(0);
	Deck opponentDeck(0);
	Deck randomDeck(countCard);
	Card getterCard;
	unsigned int myWins = 0;
	unsigned int opponentWins = 0;
	unsigned int winsCount = 3;
	int myRand = 0;
	int opponentRand = 0;
	int counter = 1;

	for (int getter = 0; getter < randomDeck.getLenght(); ++getter) {
		getterCard.setRank(randomDeck.getRank(getter));
		getterCard.setSuit(randomDeck.getSuit(getter));
		if (getter % 2 == 0) myDeck.addCard(getterCard);
		else opponentDeck.addCard(getterCard);
	}

	switch (game)
	{
	case 1:
		srand(time(0));
		while (myWins != winsCount && opponentWins != winsCount)
		{
			std::cout << "Turn " << counter << ": ";
			myRand = rand() % (countCard / 2);
			opponentRand = rand() % (countCard / 2);
			
			if (myDeck.getCard(myRand) > opponentDeck.getCard(opponentRand)) {
				myWins++;
				std::cout << "Your card " << myDeck.getCard(myRand).getSuit() << " " << myDeck.getCard(myRand).getRank() << " is larger than your opponent's " <<
					opponentDeck.getCard(myRand).getSuit() << " " << opponentDeck.getCard(myRand).getRank() << "\n";
			}
			else {
				opponentWins++;
				std::cout << "Your card " << myDeck.getCard(myRand).getSuit() << " " << myDeck.getCard(myRand).getRank() << " is smaller than your opponent's " <<
					opponentDeck.getCard(myRand).getSuit() << " " << opponentDeck.getCard(myRand).getRank() << "\n";
			};
			counter++;
		}

		if (myWins > opponentWins) std::cout << "You wins!" << std::endl;
		else std::cout << "You lose!" << std::endl;
		break;

	case 2:
		while (myDeck.getLenght() != 0 && opponentDeck.getLenght() != 0) {
			if (myDeck.getCard(0) > opponentDeck.getCard(0)) {
				try{
					Card opCard = opponentDeck.getCard(0);
					myDeck.addCard(opCard);
				}
				catch (std::exception& err) { std::cout << err.what(); }
				opponentDeck.delCard();
			}
			Card opCard = opponentDeck.getCard(0);
			if (opponentDeck.getCard(0) > myDeck.getCard(0)) {
				opponentDeck.addCard(opCard);
				myDeck.delCard();
			}
			myDeck.shiftCard();
			opponentDeck.shiftCard();
		}
		if (myDeck.getLenght() == 0) std::cout << "You lose\n";
		else std::cout << "You win\n";
		break;
	default:
		break;
	}

	Deck testdeck(10);
	Deck suda(0);
	printCardsLine(testdeck);
	testdeck.selectSuit('h', suda);
	printCardsLine(suda);
}

