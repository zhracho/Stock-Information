#pragma once
#include <string>
using namespace std;
struct Stock {
    string stockName;
    string date;
    double adjClose;
    int totalVolume;

    Stock(string date, string stockName, int totalVolume, double adjClose);
public:
    static int getYear(const string& dateParse);
    static int getMonth(const string& dateParse);
    static int getDate(const string& dateParse);

};

