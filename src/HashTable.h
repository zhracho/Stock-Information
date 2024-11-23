#pragma once
#include "Stock.h"
#include <vector>
#include <string>
using namespace std;


class HashTable {
    int bucketSize = 0;
    double threshold = .8;
    int elements = 0;
    vector<vector<pair<string, vector<Stock>>>> table;
    vector<string> companies;
    vector<string> dates;
public:
    void insert(Stock stonk, bool isDate);
    int hashFunc(const string& stockName);
    HashTable(int buckets);
    void rehash();
    vector<Stock> topNByCompany(const string& stockName, int n, bool print);
    Stock maxStock();
    vector<Stock> topStocks(int n);
    void printHeader();
    void printTable(const Stock& stonk);
    vector<Stock> dateRange(const string& date);


};

