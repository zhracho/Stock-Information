#pragma once
#include <string>
#include <vector>
#include "Stock.h"
using namespace std;
class MaxHeap {
    vector<Stock> heap;
private:
    void heapifyDown(vector<Stock>& vec, int index);

public:
    void insert(string stockName, string date, double adjClose, int totalVolume);
    void printHeap();
    Stock maxElement();
    void printMax();
    Stock extractMax();
    void searchCompany(int x, const string& stockName);
    void searchDate(const string& startDate);
    int getYear(const string& dateParse);
    int getMonth(const string& dateParse);
    int getDate(const string& dateParse);
};

