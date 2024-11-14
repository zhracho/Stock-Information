

#include "Stock.h"
#include <string>;
using namespace std;
Stock::Stock(string stockName, string date, double adjClose, int totalVolume) {
    this->stockName = stockName;
    this->date = date;
    this->adjClose = adjClose;
    this->totalVolume = totalVolume;
}
