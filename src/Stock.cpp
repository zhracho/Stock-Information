

#include "Stock.h"
#include <string>;
using namespace std;
Stock::Stock(string date, string stockName, int totalVolume, double adjClose) {
    this->stockName = stockName;
    this->date = date;
    this->adjClose = adjClose;
    this->totalVolume = totalVolume;
}
