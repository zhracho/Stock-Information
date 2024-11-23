

#include "Stock.h"
#include <string>;
using namespace std;
Stock::Stock(string date, string stockName, int totalVolume, double adjClose) {
    this->stockName = stockName;
    this->date = date;
    this->adjClose = adjClose;
    this->totalVolume = totalVolume;
}

int Stock::getYear(const string &dateParse) {
    int month = dateParse.find('/');
    int day = dateParse.find('/', month + 1);

    return stoi(dateParse.substr(day + 1));
}

int Stock::getMonth(const string &dateParse) {
    int month = dateParse.find('/');
    month = stoi(dateParse.substr(0, month));
    return month;
}

int Stock::getDate(const string &dateParse) {
    int month = dateParse.find('/');
    int date = dateParse.find('/', month + 1);

    return stoi(dateParse.substr(month + 1, date - 1));
}
