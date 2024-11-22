#pragma once
#include <string>
using namespace std;
struct Stock {
    string stockName;
    string date;
    double adjClose;
    int totalVolume;

    Stock(string date, string stockName, int totalVolume, double adjClose);

};

