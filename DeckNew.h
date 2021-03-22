#include <iostream>
#include "constants.h"
using namespace constants;              // ������������� ������ ������������ ����
                                       
struct Card {           // ��������� ��� ������ �����
private:
    int rank;           // �������� �����
    char suit;          // �������� �����
public:
    Card();                         // ����������� �� ��������� ������� "������" �����
    Card(int rank, char suit);      // ����������, ��������� ����� � ������ � ������
    int  getRank() const;           // ������ �����
    char getSuit() const;           // ������ �����
    Card & setRank(int rank);       // ������ �����
    Card & setSuit(char suit);      // ������ �����
};

class Deck {                        // ����� ������
private:
    Card list[QUANTITY];            // ������ ������ 
    int  lenght;                    // ������ ������
    void getRandom();
    void sortRank(int left, int right);
public:
    Deck();
    Deck(int number);                     // �����������, ��������� ������ �� number ����, ������������ ��������
    Deck(Card card);                      // �����������, ��������� ������ �� ����� ��������� �����
    char getSuit(int position) const;     // ����� �� ����� ����� �� �� �������
    int getRank(int position) const;      // ������ �� ���� ����� �� �� �������
    int getLenght() const;                // ������ �� ����� ������
    Deck selectSuit(char selectSuit);     // ������� ������ �� �����
    void sort();                          // ����������
    void addCard(Card card);              // ��� ������� ��� ��������� ����� � ������  
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // ���������� ��������� << ��� ������
    friend std::istream& operator >>(std::istream& c, Deck& d);         // ���������� ��������� >> ��� �����
    Deck& operator++();                                                 // ���������� ��������� ++ ��� ���������� ��������� ����� � ������
    int operator[] (int index) const;                                   // ���������� ��������� [] ��� ��������� ����� ����� � ������� index
    char operator() (int index) const;                                  // ���������� ��������� () ��� ��������� ����� ����� � ������� index
};

