#pragma once
#include <string>
using namespace std;
struct Stock {
    string stockName;
    string date;
    double adjClose;
    int totalVolume;

    Stock(string stockName, string date, double adjClose, int totalVolume);

};

