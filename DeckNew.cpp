#include "DeckNew.h"

int randomRank[QUANTITY];               // Массив для случайной генерации ранга карты
char randomSuit[QUANTITY];              // Массив для генерации случайной масти карты
char letters[4]{ 'h','d','c','s' };     // Возможные масти карт, от слов Heart, Diamond, Club, Spade


Card::Card()              // Конструктор по умолчанию создает карту минимального ранга первой заданной масти
{
    rank = MINRANG;
    suit = letters[0];
};
Card::Card(int rank, char suit)         // Коструктор, создающий карту с рангом и мастью
{
    bool StandFlag = false;
    try {
        for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
            if (letters[searcher] == suit) {
                StandFlag = true;
                break;
            }
        }
        if (rank < MINRANG || rank > MAXRANG || StandFlag == false) throw 1;          // Ограничение на ранг [MINRANG, MAXRANG] и на масть 
        Card::rank = rank;
        Card::suit = suit;
    }
    catch(int){
        Card::rank = MINRANG;
        Card::suit = letters[0];
    }
    
};
int Card::getRank() const { return rank; };
char Card::getSuit() const { return suit; };
Card& Card::setRank(int rank) {
    try {
        if (rank < MINRANG || rank > MAXRANG) throw 1;          // Ограничение на ранг [MINRANG, MAXRANG]
        Card::rank = rank;
        Card::suit = suit;
    }
    catch (int) {
        Card::rank = MINRANG;
    }
    return *this;
};
Card& Card::setSuit(char suit) {
    bool StandFlag = false;
    try {
        for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
            if (letters[searcher] == suit) {
                StandFlag = true;
                break;
            }
        }
        if (StandFlag == false) throw 100;          // Ограничение на масть 
        Card::rank = rank;
        Card::suit = suit;
    }
    catch (int) {
        Card::suit = letters[0];
    }
    return *this;
};

Deck::Deck() {                            // конструктор по умолчанию создает упорядоченный набор карт: переодичность ранга - MAXRANG, переодичность масти - len(letters)
    lenght = QUANTITY;
    for (int filler = 0; filler < QUANTITY; ++filler) {
        Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
        list[filler] = basekard;
    };
};
Deck::Deck(int number)                    // конструктор, создающий колоду из number карт, определяемых случайно
{
    try {
        if (number > QUANTITY || number < 0) throw 101;
        lenght = number;
        Deck::getRandom();
        for (int counter = 0; counter < number; ++counter)
        {
            Card karta(randomRank[counter] + 1, randomSuit[counter]);
            list[counter] = karta;
        };
    }
    catch (int) {
        lenght = QUANTITY;
        Deck::getRandom();
        for (int counter = 0; counter < QUANTITY; ++counter)
        {
            Card karta(randomRank[counter] + 1, randomSuit[counter]);
            list[counter] = karta;
        };

    }
};
Deck::Deck(Card card) {                   // конструктор, создающий колоду из одной указанной карты
    lenght = 1;
    list[0] = card;
};
Deck& Deck::operator++()                  // перегрузка оператора ++ для добавления случайной карты в колоду
{
    try {
        if (lenght >= QUANTITY) throw 102;  //ограничение на размер колоды
        Card additionCard((rand() % MAXRANG) + 1, letters[rand() % (sizeof(letters) / sizeof(letters[0]))]);
        list[lenght] = additionCard;
        lenght++;
    }
    catch (int) {

    }
    return *this;
};

char Deck::getSuit(int position) const { return list[position].getSuit(); };   
int Deck::getRank(int position) const { return list[position].getRank(); };  
int Deck::getLenght() const { return lenght; };

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
        sortRank(lastPosition - counter, lastPosition - 1);     //после сортироки по букве применяется сортировка по рангу
        currentPosition = lastPosition;
        counter = 0;
    };
};
Deck Deck::selectSuit(char selectSuit) {
    Deck filtredDeck(0);
    try {
        bool StandFlag = false;
        for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
            if (list[searcher].getSuit() == selectSuit) {
                StandFlag = true;
                break;
            }
        }
        if (StandFlag == false) throw 103;
        for (int position = 0; position < lenght; ++position) {
            if (list[position].getSuit() == selectSuit)
                filtredDeck.addCard(list[position]);
        };
    }
    catch (int) {}
    return filtredDeck;
};


void Deck::getRandom() {  // функция для создания случайных карт
    for (int counter = 0; counter < QUANTITY; ++counter)
    {
        int randomNumber = rand() % (counter + 1);
        randomRank[counter] = randomRank[randomNumber];
        randomRank[randomNumber] = counter % 13;
        randomSuit[counter] = randomSuit[randomNumber];
        randomSuit[randomNumber] = letters[counter % 4];
    };
};
void Deck::addCard(Card card) {
    Card additionCard(card.getRank(), card.getSuit());
    try {
        if (lenght >= QUANTITY) throw 103;
        lenght++;
        list[lenght] = additionCard;
    }
    catch(int){}
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
        c << "_____\n";
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
    for (int inputer = 0; inputer < QUANTITY; ++inputer) {
        c >> rangInput >> suitInput;
        d.addCard(Card(rangInput, suitInput));
    }
    return c;
};
int Deck::operator[] (int index) const { return list[index].getRank();}
char Deck::operator() (int index) const { return list[index].getSuit(); }


