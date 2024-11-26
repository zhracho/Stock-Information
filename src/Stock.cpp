#include "Stock.h"
#include <string>
#include <ctime>
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

time_t Stock::getDateTime(const string &dateParse) {
    tm date2 = {};
    //Extract the date from the components
    int stockDate = Stock::getDate(dateParse);
    int stockYear = Stock::getYear(dateParse);
    int stockMonth = Stock::getMonth(dateParse);

    //Initialize it into our date structure for comparing
    date2.tm_year = stockYear - 1900;
    date2.tm_mon = stockMonth - 1;
    date2.tm_mday = stockDate;

    time_t timestamp2 = mktime(&date2);
    return timestamp2;
}
