#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
int HashTable::hashFunc(const string& stockName) {
    int sum = 0;
    for(int i = 0; i < stockName.length(); i++){
        sum += (int)stockName[i];
    }
    return sum;
}

void HashTable::insert(Stock stonk) {

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
