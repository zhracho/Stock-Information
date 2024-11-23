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
    void insert(Stock stonk);
    void topN(int n);
    void printHeap();
    Stock maxElement();
    void printMax();
    Stock extractMax();
    void searchCompany(int x, const string& stockName);
    void searchDate(const string& startDate);
    void printHeader();
    void printTable(const Stock& stonk);
};

