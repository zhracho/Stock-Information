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
    //Need to make these functions static to access them in HashTable and MaxHeap
    //These functions are created to parse in dates for the fifth function
    static int getYear(const string& dateParse);
    static int getMonth(const string& dateParse);
    static int getDate(const string& dateParse);
    static time_t getDateTime(const string& dateParse);

};

