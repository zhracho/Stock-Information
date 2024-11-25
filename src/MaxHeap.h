#pragma once
#include <string>
#include <vector>
#include "Stock.h"
using namespace std;
class MaxHeap {
    vector<Stock> heap;
    void heapifyDown(vector<Stock>& vec, int index);
public:
    void insert(Stock stonk);
    void topN(int n);
    Stock maxElement();
    void printMax();
    Stock extractMax();
    void searchCompany(int x, const string& stockName, bool all);
    void searchDate(const string& startDate);
    void printHeader();
    void printTable(const Stock& stonk);
};

