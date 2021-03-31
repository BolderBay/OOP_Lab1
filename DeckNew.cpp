#include "DeckNew.h"
#include <strstream>
#include <stdio.h>

Card::Card()              // Êîíñòðóêòîð ïî óìîë÷àíèþ ñîçäàåò êàðòó ìèíèìàëüíîãî ðàíãà ïåðâîé çàäàííîé ìàñòè
{
	rank = MINRANG;
	suit = letters[0];
};
Card::Card(int rank, char suit)         // Êîñòðóêòîð, ñîçäàþùèé êàðòó ñ ðàíãîì è ìàñòüþ
{
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == suit) {
			StandFlag = true;
			break;
		}
	}
	if (rank < MINRANG || rank > MAXRANG && StandFlag == false) throw std::exception("Invalid rang and suit\n");
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");         // Îãðàíè÷åíèå íà ðàíã [MINRANG, MAXRANG] è íà ìàñòü  
	if (StandFlag == false) throw std::exception("Invalid suit\n");
	Card::rank = rank;
	Card::suit = suit;

};
int Card::getRank() const { return rank; };
char Card::getSuit() const { return suit; };
Card& Card::setRank(int rank) {
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");          // Îãðàíè÷åíèå íà ðàíã [MINRANG, MAXRANG]
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
	if (StandFlag == false) throw std::exception("Invalid suit\n");          // Îãðàíè÷åíèå íà ìàñòü 
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

Deck::Deck() {                            // êîíñòðóêòîð ïî óìîë÷àíèþ ñîçäàåò óïîðÿäî÷åííûé íàáîð êàðò: ïåðåîäè÷íîñòü ðàíãà - MAXRANG, ïåðåîäè÷íîñòü ìàñòè - len(letters)
	lenght = QUANTITY;
	for (int filler = 0; filler < QUANTITY; ++filler) {
		Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
		list[filler] = basekard;
	};
};
Deck::Deck(int number)                    // êîíñòðóêòîð, ñîçäàþùèé êîëîäó èç number êàðò, îïðåäåëÿåìûõ ñëó÷àéíî
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

Deck::Deck(Card card) {                   // êîíñòðóêòîð, ñîçäàþùèé êîëîäó èç îäíîé óêàçàííîé êàðòû
	lenght = 1;
	list[0] = card;
};
Deck& Deck::operator++()                  // ïåðåãðóçêà îïåðàòîðà ++ äëÿ äîáàâëåíèÿ ñëó÷àéíîé êàðòû â êîëîäó
{
	srand(time(0));
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");  // îãðàíè÷åíèå íà ðàçìåð êîëîäû
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

void Deck::sort() {                                                    // ñîðòèðîâêà ïî ìàñòè è ðàíãó
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
		sortRank(lastPosition - counter, lastPosition - 1);     // ïîñëå ñîðòèðîêè ïî áóêâå ïðèìåíÿåòñÿ ñîðòèðîâêà ïî ðàíãó
		currentPosition = lastPosition;
		counter = 0;
	};
};
Deck Deck::selectSuit(char selectSuit) {
	Deck filtredDeck(0);
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (list[searcher].getSuit() == selectSuit) {
			StandFlag = true;
			break;
		}
	}
	if (StandFlag == false) throw std::exception("Invalid suit\n");

	for (int position = 0; position < lenght; ++position) {
		if (list[position].getSuit() == selectSuit)
			filtredDeck.addCard(list[position]);
	};

	return filtredDeck;
};

void Deck::addCard(Card card) {
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
void Deck::sortRank(int left, int right) {                             // ñîðòèðîâêà ïî ðàíãó áûñòðîé ñîðòèðîâêîé  
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

std::ostream& operator <<(std::ostream& c, const Deck& d) // ïåðåãðóçêà îïåðàòîðà << äëÿ âûâîäà ãðàôèêè
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
	for (int inputer = 0; inputer < counter; ++inputer) {
		c >> rangInput >> suitInput;
		try {
			d.addCard(Card(rangInput, suitInput));
		}
		catch (std::exception& error) { std::cout << error.what(); }
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
	Card tmp1;
	tmp1 = list[0];
	for (int i = 0; i < lenght - 1; i++)
		list[i] = list[i + 1];
	list[lenght - 1] = tmp1;
}

void Deck::delCard() {
	shiftCard();
	lenght--;
}
