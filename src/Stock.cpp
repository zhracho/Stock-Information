#include "Stock.h"
#include <string>
using namespace std;

//Initializing the constructor
Stock::Stock(string date, string stockName, int totalVolume, double adjClose) {
    this->stockName = stockName;
    this->date = date;
    this->adjClose = adjClose;
    this->totalVolume = totalVolume;
}

int Stock::getYear(const string &dateParse) {
    //https://cplusplus.com/reference/algorithm/find/ to figure out the find operation
    //Get all of the characters up until the /
    int month = dateParse.find('/');
    //Get everything from the month onward
    int day = dateParse.find('/', month + 1);
    //Extract the year
    return stoi(dateParse.substr(day + 1));
}

int Stock::getMonth(const string &dateParse) {
    //https://cplusplus.com/reference/algorithm/find/ to figure out the find operation
    //Get all of the characters up until the /
    int month = dateParse.find('/');
    //Get everything from the beginning up until the first /
    month = stoi(dateParse.substr(0, month));
    return month;
}

int Stock::getDate(const string &dateParse) {
    //https://cplusplus.com/reference/algorithm/find/ to figure out the find operation
    int month = dateParse.find('/');
    int date = dateParse.find('/', month + 1);
    //Extract the date given the previous positions
    return stoi(dateParse.substr(month + 1, date - 1));
}
