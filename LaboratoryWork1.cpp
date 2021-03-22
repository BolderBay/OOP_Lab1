#include "DeckNew.h"
#include <iostream>

void printCards(Deck cards) {                       //функция вывода карт в колоде
    for (int j = 0; j < cards.getLenght(); j++) {
        std::cout << j + 1 << ") " << cards.getRank(j) << " " << cards.getSuit(j) << "\n";
    };
};
void printCardsLine(Deck cards) {                   //функция вывода карт в колоде в линию
    for (int j = 0; j < cards.getLenght(); j++) {
        std::cout << cards.getSuit(j) << " ";
    };
    std::cout << '\n';
    for (int j = 0; j < cards.getLenght(); j++) {
        std::cout << cards.getRank(j) << " ";
    };
    std::cout << '\n';
};



int main()
{   
	Deck myDeck(10);
    printCardsLine(myDeck);
    myDeck.sort();
    Deck filter = myDeck.selectSuit('h');
    printCardsLine(myDeck);
    printCardsLine(filter);
    std::cout << filter[0] << filter(0) << std::endl;
    Deck newDeck(0);
    std::cin >> newDeck;
    printCardsLine(newDeck);

}

