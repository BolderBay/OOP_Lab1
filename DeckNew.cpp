#include "DeckNew.h"
#include <strstream>
#include <stdio.h>

Card::Card()              // Конструктор по умолчанию создает карту минимального ранга первой заданной масти
{
	rank = MINRANG;
	suit = letters[0];
};
Card::Card(int rank, char suit)         // Коструктор, создающий карту с рангом и мастью
{
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == suit) {
			StandFlag = true;
			break;
		}
	}
	if (rank < MINRANG || rank > MAXRANG && StandFlag == false) throw std::exception("Invalid rang and suit\n");
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");         // Ограничение на ранг [MINRANG, MAXRANG] и на масть 
	if (StandFlag == false) throw std::exception("Invalid suit\n");
	Card::rank = rank;
	Card::suit = suit;

};
int Card::getRank() const { return rank; };
char Card::getSuit() const { return suit; };
Card& Card::setRank(int rank) {
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");          // Ограничение на ранг [MINRANG, MAXRANG]
	else {
		Card::rank = rank;
		Card::suit = suit;
		return *this;
	}
};
Card& Card::setSuit(char suit) {
	bool StandFlag = false;

	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == suit) {
			StandFlag = true;
			break;
		}
	}
	if (StandFlag == false) throw std::exception("Invalid suit\n");          // Ограничение на масть 
	Card::rank = rank;
	Card::suit = suit;
	return *this;
};

bool Card::operator> (Card sortCard) 
{
	int suit1pos=0;
	int suit2pos=0;
	for (int i = 0; i < sizeof(letters); i++) 
	{
		if (letters[i] == suit) suit1pos = i;
		if (letters[i] == sortCard.getSuit()) suit2pos = i;
	}
	if (suit1pos > suit2pos) return false;
	if (suit1pos < suit2pos) return true;
	if (suit1pos == suit2pos && rank > sortCard.getRank()) return true;
	if (suit1pos == suit2pos && rank < sortCard.getRank()) return false;
}

Deck::Deck() {                            // конструктор по умолчанию создает упорядоченный набор карт: переодичность ранга - MAXRANG, переодичность масти - len(letters)
	lenght = QUANTITY;
	for (int filler = 0; filler < QUANTITY; ++filler) {
		Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
		list[filler] = basekard;
	};
};
Deck::Deck(int number)                    // конструктор, создающий колоду из number карт, определяемых случайно
{
	srand(time(0));
	if (number > QUANTITY || number < 0) throw std::exception("Invalid number\n");
	lenght = number;
	for (int filler = 0; filler < QUANTITY; ++filler) {
		Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
		list[filler] = basekard;
	};

	for (int swapper = 0; swapper < QUANTITY; swapper++)
	{
		Card buffer;
		int randomPosition = rand() % QUANTITY;
		buffer = list[swapper];
		list[swapper] = list[randomPosition];
		list[randomPosition] = buffer;
	}


};

Deck::Deck(Card &card) {                   // конструктор, создающий колоду из одной указанной карты
	lenght = 1;
	list[0] = card;
};
Deck& Deck::operator++()                  // перегрузка оператора ++ для добавления случайной карты в колоду
{
	srand(time(0));
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");  // ограничение на размер колоды
	Card additionCard;
	bool FindingFlag = true;
	while (FindingFlag == true) {
		FindingFlag = false;
		additionCard.setRank((rand() % MAXRANG) + 1);
		additionCard.setSuit(letters[rand() % (sizeof(letters) / sizeof(letters[0]))]);
		for (int i = 0; i < lenght; i++)
			if (list[i].getRank() == additionCard.getRank() && list[i].getSuit() == additionCard.getSuit()) FindingFlag = true;
	}
	addCard(additionCard);
	return *this;
};

char Deck::getSuit(int position) const {
	if (position > lenght) throw std::exception("Incorrect position\n");
	return list[position].getSuit();
};
int Deck::getRank(int position) const {
	if (position > lenght) throw std::exception("Incorrect position\n");
	return list[position].getRank();
};
int Deck::getLenght() const { return lenght; };

void Deck::NewSort() {
	Card buffer;
	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght - 1; j++) {
			if (list[j+1] > list[j]) {
				buffer = list[j + 1];
				list[j + 1] = list[j];
				list[j] = buffer;
			}
		}
	}
}

void Deck::sort() {                                                    // сортировка по масти и рангу
	Card buffer;
	int currentPosition = 0;
	int lastPosition = 0;
	int lettersPosition = 0;
	int counter = 0;
	for (lettersPosition; lettersPosition < (sizeof(letters) / sizeof(letters[0])); ++lettersPosition) {
		for (currentPosition; currentPosition < lenght; ++currentPosition) {
			if (list[currentPosition].getSuit() == letters[lettersPosition]) {
				buffer = list[lastPosition];
				list[lastPosition] = list[currentPosition];
				list[currentPosition] = buffer;
				lastPosition++;
				counter++;
			};
		};
		sortRank(lastPosition - counter, lastPosition - 1);     // после сортироки по букве применяется сортировка по рангу
		currentPosition = lastPosition;
		counter = 0;
	};
};
Deck Deck::selectSuit(char selectSuit, Deck &newdeck) {
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == selectSuit) {
			StandFlag = true;
			break;
		}
	}
	if (StandFlag == false) throw std::exception("Invalid suit\n");

	for (int position = 0; position < lenght; ++position) {
		if (list[position].getSuit() == selectSuit)
			newdeck.addCard(list[position]);
	};

	return 0;
};

void Deck::addCard(Card &card) {
	Card additionCard(card.getRank(), card.getSuit());
	bool FindingFlag = false;
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");
	for (int seacher = 0; seacher < lenght; ++seacher) {
		if (list[seacher].getRank() == card.getRank() && list[seacher].getSuit() == card.getSuit()) {
			FindingFlag = true;
			break;
		}	
	}
	if (FindingFlag == true) throw std::exception("This card is already in the deck\n");

	list[lenght] = additionCard;
	lenght++;

};
void Deck::sortRank(int left, int right) {                             // сортировка по рангу быстрой сортировкой  
	int pivot;
	char pivot_suit = ' ';
	int l_hold = left;
	int r_hold = right;
	pivot = list[left].getRank();
	pivot_suit = list[left].getSuit();
	while (left < right)
	{
		while ((list[right].getRank() <= pivot) && (left < right))
			right--;
		if (left != right)
		{
			list[left].setRank(list[right].getRank());
			list[left].setSuit(list[right].getSuit());
			left++;
		}
		while ((list[left].getRank() >= pivot) && (left < right))
			left++;
		if (left != right)
		{
			list[right].setRank(list[left].getRank());
			list[right].setSuit(list[left].getSuit());
			right--;
		}
	}
	list[left].setRank(pivot);
	list[left].setSuit(pivot_suit);
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		Deck::sortRank(left, pivot - 1);
	if (right > pivot)
		Deck::sortRank(pivot + 1, right);
};

std::ostream& operator <<(std::ostream& c, const Deck& d) // перегрузка оператора << для вывода графики
{
	int outputCount = 0;
	while (d.getRank(outputCount) != 0 && outputCount < d.getLenght()) {
		c << " ____\n";
		c << "|" << d.getRank(outputCount) << "  |\n";
		if (d.getRank(outputCount) > 9)
			c << "| " << d.getSuit(outputCount) << "  |\n";
		else
			c << "| " << d.getSuit(outputCount) << " |\n";
		c << "|__" << d.getRank(outputCount) << "|\n";
		outputCount++;
	};
	return c;
};
std::istream& operator >>(std::istream& c, Deck& d)
{
	int rangInput;
	char suitInput;
	int counter;
	
	c >> counter;
	if (counter > QUANTITY - d.getLenght()) throw std::exception("Incorrect quantity\n");
	for (int inputer = 0; inputer < counter; ++inputer) {
		c >> rangInput >> suitInput;
		try {
			Card imputCard(rangInput, suitInput);
			d.addCard(imputCard);
		}
		catch (std::exception& error) {
			c.setstate(std::ios::failbit);
		}
	}
	return c;
};
int Deck::operator[] (int index) const { 
	if (index > lenght) throw std::exception("Incorrect position\n");
	return list[index].getRank(); 
}
char Deck::operator() (int index) const { 
	if (index > lenght) throw std::exception("Incorrect position\n"); 
	return list[index].getSuit(); 

}

Card Deck::getCard(int index) {
	if (index > lenght) throw std::exception("Incorrect position\n");
	return list[index];
}

void Deck::shiftCard() {
	if (lenght == 0) throw std::exception("Zero length");
	Card tmp1;
	tmp1 = list[0];
	for (int i = 0; i < lenght - 1; i++)
		list[i] = list[i + 1];
	list[lenght - 1] = tmp1;
}

void Deck::delCard() {
	if (lenght == 0) throw std::exception("Zero length");
	shiftCard();
	lenght--;
}
