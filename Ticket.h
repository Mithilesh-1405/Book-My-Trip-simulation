
#include <bits/stdc++.h>
using namespace std ;

class Ticket
{
public:
    Ticket(string x, string y, float p, string d , int t)
    {
        this->from = x;
        to = y;
        price = p;
        date = d;
        type = t;
    }
    string from;
    string to;
    float price;
    string date;
    int type ;

    void printTicketDetail()
    {
        cout << "FROM : " << from << endl;
        cout << "TO : " << to << endl;
        cout << "PRICE (RS) : " << price << endl;
        cout << "DATE : " << date << endl;
    }
};