#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Stock.h"
using namespace std;
int HashTable::hashFunc(const string& stockName) {
    int sum = 0;
    for(int i = 0; i < stockName.length(); i++){
        sum += (int)stockName[i];
    }
    return sum;
}

void HashTable::insert(Stock stonk, bool isDate = false) {

    if(isDate){
        int reduceInd = hashFunc(stonk.date) % bucketSize;
        //If the entry exists add it to the big vector that we have
        vector<pair<string, vector<Stock>>> temp = table[reduceInd];

        for(int i = 0; i < temp.size(); i++){
            if(temp[i].first == stonk.date){
                table[reduceInd][i].second.push_back(stonk);
                return;
            }
        }

        vector<Stock> insert = {stonk};

        table[reduceInd].push_back(make_pair(stonk.date, insert));
        dates.push_back(stonk.date);
        elements++;
        double loadFactor = (double)elements / bucketSize;

        if(loadFactor >= threshold){
            rehash();
        }

    }else{
        int reduceInd = hashFunc(stonk.stockName) % bucketSize;
        //If the entry exists add it to the big vector that we have
        vector<pair<string, vector<Stock>>> temp = table[reduceInd];

        for(int i = 0; i < temp.size(); i++){
            if(temp[i].first == stonk.stockName){
                table[reduceInd][i].second.push_back(stonk);
                return;
            }
        }

        vector<Stock> insert = {stonk};

        table[reduceInd].push_back(make_pair(stonk.stockName, insert));
        companies.push_back(stonk.stockName);
        elements++;
        double loadFactor = (double)elements / bucketSize;

        if(loadFactor >= threshold){
            rehash();
        }


    }


}

HashTable::HashTable(int buckets) {
    this->bucketSize = buckets;
    table.resize(bucketSize);
}

void HashTable::rehash() {

    vector<vector<pair<string, vector<Stock>>>> newTable;
    bucketSize = (int)table.size() * 2;
    newTable.resize(bucketSize);

    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            vector<Stock> allStock = table[i][j].second;
            int reduceInd = hashFunc(table[i][j].first) % bucketSize;
            newTable[reduceInd].push_back(make_pair(table[i][j].first,allStock));
        }

    }

    table = newTable;

}

vector<Stock> HashTable::topNByCompany(const string& stockName, int n, bool print = false) {

    vector<Stock> storeCompany;
    vector<Stock> ans;

    if(find(companies.begin(), companies.end(), stockName) != companies.end()){
        int reducedIndex = hashFunc(stockName) % bucketSize;
        for(int i = 0; i < table[reducedIndex].size(); i++){
            if(table[reducedIndex][i].first == stockName){
                storeCompany = table[reducedIndex][i].second;
            }
        }

        std::sort(storeCompany.begin(), storeCompany.end(),
                  [] (Stock stock1, Stock stock2) {return stock1.adjClose > stock2.adjClose;});

        for(int i = 0; i < n; i++){
            ans.push_back(storeCompany[i]);
        }

        if(print){
            printHeader();
            for(int i = 0; i < ans.size(); i++){
                printTable(ans[i]);
            }
        }
    }else{
        cout << "Not Found in the Data... Please Try Another Company!" << endl;
    }


    return ans;
}

Stock HashTable::maxStock() {
    vector<Stock> maxStocks;
    for(int i = 0; i < companies.size(); i++){
        maxStocks.push_back(topNByCompany(companies[i], 1)[0]);
    }

    Stock ans = *std::max_element(maxStocks.begin(), maxStocks.end(),
                                  [] (Stock stock1, Stock stock2) {return stock1.adjClose < stock2.adjClose;});


    printHeader();
    printTable(ans);

    return ans;

}

vector<Stock> HashTable::topStocks(int n) {

    vector<Stock> maxStocks;
    vector<Stock> top;
    for(int i = 0; i < companies.size(); i++) {
        int reducedIndex = hashFunc(companies[i]) % bucketSize;
        for (int j = 0; j < table[reducedIndex].size(); j++) {
            maxStocks.insert(maxStocks.end(), table[reducedIndex][j].second.begin(), table[reducedIndex][j].second.end());
        }
    }

    std::sort(maxStocks.begin(), maxStocks.end(),
              [] (Stock stock1, Stock stock2) {return stock1.adjClose > stock2.adjClose;});

    for(int i = 0; i < n; i++){
        top.push_back(maxStocks[i]);
    }

    printHeader();
    for(int i = 0; i < top.size(); i++){
        printTable(top[i]);
    }

    return top;

}
void HashTable::printHeader() {
    cout << left << setw(15) << "Stock Name"
         << setw(15) << "Date"
         << setw(15) << "Adj. Close"
         << setw(15) << "Volume" << endl;
    cout << string(60, '-') << endl;
}

void HashTable::printTable(const Stock& stonk) {
    cout << left << setw(15) << stonk.stockName
         << setw(15) << stonk.date
         << setw(15) << fixed << setprecision(2) << stonk.adjClose
         << setw(15) << stonk.totalVolume << endl;

    cout << string(60, '-') << endl;

}

vector<Stock> HashTable::dateRange(const string& date) {
    vector<Stock> dateStocks;
    tm date1 = {};


    int startDay = Stock::getDate(date);
    int startMonth = Stock::getMonth(date);
    int startYear = Stock::getYear(date);

    date1.tm_year = startYear - 1900;
    date1.tm_mon = startMonth- 1;
    date1.tm_mday = startDay;

    time_t timestamp1 = mktime(&date1);
    time_t timestamp2;

    for(int i = 0; i < dates.size(); i++) {
        tm date2 = {};

        int reducedIndex = hashFunc(dates[i]) % bucketSize;
        for (int j = 0; j < table[reducedIndex].size(); j++) {
            int stockDate = Stock::getDate(table[reducedIndex][j].first);
            int stockYear = Stock::getYear(table[reducedIndex][j].first);
            int stockMonth = Stock::getMonth(table[reducedIndex][j].first);

            date2.tm_year = stockYear- 1900;
            date2.tm_mon = stockMonth -1;
            date2.tm_mday = stockDate;

            timestamp2 = mktime(&date2);
            if(timestamp1 < timestamp2){
                dateStocks.insert(dateStocks.end(), table[reducedIndex][j].second.begin(), table[reducedIndex][j].second.end());
            }
        }

    }

    printHeader();
    for(int i = 0; i < dateStocks.size(); i++){
        printTable(dateStocks[i]);
    }

    return dateStocks;

}
