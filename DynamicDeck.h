#include <iostream>
#include "DeckConst.h"
using namespace DeckConst;              // Использование своего пространства имен

struct Card {           // Структура для задачи карты
private:
    int rank;           // Значение ранга
    char suit;          // значение масти
public:
    Card();                         // Конструктор по умолчанию создает "пустую" карту
    Card(int rank, char suit);      // Коструктор, создающий карту с рангом и мастью
    int  getRank() const;           // Геттер ранга
    char getSuit() const;           // Геттер масти
    Card& setRank(int rank);       // Сеттер ранга
    Card& setSuit(char suit);      // Сеттер масти
    bool operator> (Card sortCard);
};

class Deck {                        // класс колоды
private:
    Card *list = new Card[0]();            // Массив колоды 
    int  lenght;                        // Длинна колоды
    void sortRank(int left, int right);
public:
    Deck();
    Deck(int number);                     // Конструктор, создающий колоду из number карт, определяемых случайно
    Deck(Card card);                      // Конструктор, создающий колоду из одной указанной карты
    char getSuit(int position) const;     // Гттер на масть карты по ее позиции
    int getRank(int position) const;      // Геттер на ранг карты по ее позиции
    int getLenght() const;                // Геттер на длину колоды
    Deck selectSuit(char selectSuit);     // Возврат колоды по масти
    void sort();                          // Сортировка
    void NewSort();                       // Новая сортировка
    void addCard(Card card);              // Доп функция для доавления карты в колоду  
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // Перегрузка оператора << для вывода
    friend std::istream& operator >>(std::istream& c, Deck& d);         // Перегрузка оператора >> для ввода
    Deck& operator++();                                                 // Перегрузка оператора ++ для добавления случайной карты в колоду
    int operator[] (int index) const;                                   // Перегрузка оператора [] для получения масти карты в позиции index
    char operator() (int index) const;                                  // Перегрузка оператора () для получения ранга карты в позиции index
    Card getCard(int index);                                            // Дополнительный метод получения карты
    void shiftCard();                                                   // Дополнительный метод сдвига карт в колоде
    void delCard();                                                     // Дополнительный метод удаления карты
};

class DynamicDeck
{
};
