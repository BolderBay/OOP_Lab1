#include <iostream>

#define quantityOld 10                     //Количество карт в колоде 

int randomRankOld[quantityOld];               //Массив для случайной генерации ранга карты
char randomSuitOld[quantityOld];              //Массив для генерации случайной масти карты
char lettersOld[4]{'h','d','c','s'};       //Возможные масти карт, от слов Heart, Diamond, Club, Spade


struct Card {           //Структура для задачи карты
private:
    int rank;           // Значение ранга
    char suit;          // значение масти
public:
    Card()              // Конструктор по умолчанию создает "пустую" карту
    {
        rank = NULL;
        suit = NULL;
    };
    Card(int rank, char suit)           // Коструктор, создающий карту с рангом и мастью
    {
        if (rank > 0 && rank < 14)      // ограничение на ранг [1, 13]
            Card::rank = rank;
        else {
            std::cout << "Invalid rank\n";
            Card::rank = 1;                                             // в случае ошибки ранга устанавливается ранг 1
        }
        if (suit == 'h' || suit == 'd' || suit == 'c' || suit == 's')   //ограничение на масть
            Card::suit = suit;
        else {
            std::cout << "Invalid suit\n";
            Card::suit = 'h';                                           // в случа ошибки масти устанавливается масть Heart
        };
    };
    int getRank() const { return rank; };                         // геттер ранга
    char getSuit() const { return suit; };                        // геттер ранга
    void setRank(int rank) { Card::rank = rank; };          // сеттер ранга
    void setSuit(char suit) { Card::suit = suit; };         // сеттер масти
};

class DeckOld {                            //класс колоды
private:
    Card list[quantityOld];                //массив колоды 
public:
    DeckOld() {                            // конструктор по умолчанию создает упорядоченный набор карт: переодичность ранга - 13, переодичность масти - 4
        for (int filler = 0; filler < quantityOld; ++filler) {
            Card basekard((filler % 13) + 1, lettersOld[filler % 4]);
            list[filler] = basekard;
        
        };
    };
    DeckOld(int number)                    // конструктор, создающий колоду из number карт, определяемых случайно
    {
        if (number <= quantityOld)
        {
            DeckOld::getRandom();
            for (int counter = 0; counter < number; counter++)
            {
                Card karta(randomRankOld[counter] + 1, randomSuitOld[counter]);
                list[counter] = karta;
            };
        }
        else std::cout << "Exceeding the card limit\n";
       
    };
    DeckOld(Card card) {                   // конструктор, создающий колоду из одной указанной карты
        list[0] = card;    
    };
    DeckOld& operator++()                  // перегрузка оператора ++ для добавления случайной карты в колоду
    {
        int lastPosition = 0;
        Card additionCard((rand() % 12)+1, lettersOld[rand() % 4]);
        while (list[lastPosition].getRank() != NULL && lastPosition< quantityOld) { lastPosition++; };
        if (lastPosition < quantityOld)
            list[lastPosition] = additionCard;
        else
            std::cout << "The deck contains the maximum number of cards\n"; // ограничение на превышение размера колоды 
        return *this;

    };
    char getSuit(int position) const { return list[position].getSuit(); }; // геттер на масть карты по ее позиции
    int getRank(int position) const { return list[position].getRank(); };  // геттер на ранг карты по ее позиции
    void sort() {                                                    // сортировка по масти и рангу
        Card buffer;
        int currentPosition = 0;
        int lastPosition = 0;
        int lettersPosition = 0;
        int lastnonzero = 0;
        int counter = 0;
        while (list[lastnonzero].getRank() != NULL && lastnonzero < quantityOld) { lastnonzero++; };

        for (lettersPosition; lettersPosition < 4; lettersPosition++) {
            for (currentPosition; currentPosition < lastnonzero; currentPosition++) {
                if (list[currentPosition].getSuit() == lettersOld[lettersPosition]){
                    buffer = list[lastPosition];
                    list[lastPosition] = list[currentPosition];
                    list[currentPosition] = buffer;
                    lastPosition++;
                    counter++;
                    };
            };
            sortRank(lastPosition-counter, lastPosition-1);     //после сортироки по букве применяется сортировка по рангу
            currentPosition = lastPosition;
            counter = 0;
        };          
    };
    DeckOld selectSuit(char selectSuit) {
        if (selectSuit == 'h' || selectSuit == 'd' || selectSuit == 'c' || selectSuit == 's') {
            DeckOld filtredDeck(0);
            int lastPosition = 0;
            while (list[lastPosition].getRank() != NULL && lastPosition < quantityOld) { lastPosition++; };
            for (int position = 0; position < lastPosition; position++) {
                if (list[position].getSuit() == selectSuit)
                    filtredDeck.addCard(list[position]);
            };
            return filtredDeck;
        }
        else
            std::cout << "Wrong suit";
    };

    friend std::ostream& operator <<(std::ostream& c, const DeckOld& d);
    friend std::istream& operator >>(std::istream& c, DeckOld& d);
    DeckOld& operator= (const DeckOld& deck);

    void getRandom() {  // функция для создания случайных карт
        for (int counter = 0; counter < quantityOld; counter++)
        {
            int randomNumber = rand() % (counter+1);
            randomRankOld[counter] = randomRankOld[randomNumber];
            randomRankOld[randomNumber] = counter%13;
            randomSuitOld[counter] = randomSuitOld[randomNumber];
            randomSuitOld[randomNumber] = lettersOld[counter%4];
        };
    };
    void addCard(Card card) {
        int lastPosition = 0;
        Card additionCard(card.getRank(), card.getSuit());
        while (list[lastPosition].getRank() != NULL && lastPosition < quantityOld) { lastPosition++; };
        if (lastPosition < quantityOld)
            list[lastPosition] = additionCard;
        else
            std::cout << "The deck contains the maximum number of cards\n";
    };
    void sortRank(int left, int right) {                             // сортировка по рангу быстрой сортировкой  
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
            DeckOld::sortRank(left, pivot - 1);
        if (right > pivot)
            DeckOld::sortRank(pivot + 1, right);
    };
};


std::ostream& operator <<(std::ostream& c, const DeckOld& d) // перегрузка оператора << для вывода графики
{
    int outputCount = 0;
    while (d.getRank(outputCount) != 0 && outputCount < quantityOld) {
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
std::istream& operator >>(std::istream& c, DeckOld& d)
{
    int number = 0;
    char leter = ' ';
    std::string stroka;

    while (1 == 1) {
        c >> stroka;
        std::cout << stroka;
       // c >> number >> leter;
       // std::cout << number << leter << std::endl;
    };
    return c;
};
//Deck& Deck::operator= (const Deck& deck) 




void printCards(DeckOld cards, int numbers) {                       //функция вывода карт в колоде
    for (int j = 0; j < numbers; j++) {
        std::cout << j + 1 << ") " << cards.getRank(j) << " " << cards.getSuit(j) << "\n";
    };
};
void printCardsLine(DeckOld cards, int numbers) {                   //функция вывода карт в колоде в линию
    for (int j = 0; j < numbers; j++) {
        std::cout  << cards.getSuit(j) << " ";
    };
    std::cout << '\n';
    for (int j = 0; j < numbers; j++) {
        std::cout << cards.getRank(j) << " ";
    };
    std::cout << '\n';
};
void printNonZero(DeckOld cards) {                                  //функция вывода ненулевых карт в колоде
    int lastPosition = 0;
    while (cards.getRank(lastPosition) > NULL && lastPosition < quantityOld ) { 
        std::cout << lastPosition + 1 << ") " << cards.getRank(lastPosition) << " " << cards.getSuit(lastPosition) << "\n";
        lastPosition++; 
    }
};

int main()
{
   srand(time(0));      //зерно для псевдослучайного генератора 
   DeckOld koloda(10);
   printCards(koloda, 10);
   DeckOld dKoloda = koloda.selectSuit('d');
   std::cout << std::endl;
   printNonZero(dKoloda);
   std::cout << dKoloda << std::endl;
   return 0;
}

