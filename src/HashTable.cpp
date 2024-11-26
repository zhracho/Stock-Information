#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Stock.h"
using namespace std;

int HashTable::hashFunc(const string& stockName) {
    int sum = 0;
    //Iterate through all of the characters and sum the ascii values
    for(int i = 0; i < stockName.length(); i++){
        sum += (int)stockName[i];
    }
    return sum;
}

void HashTable::insert(Stock stonk, bool isDate = false) {

    //There are two data structures we want to implement in the table, one with company name and the other with date
    if(isDate){
        //Call the hash function and reduce the index based on the buckets we specify
        int reduceInd = hashFunc(stonk.date) % bucketSize;
        //If the entry exists add it to the big vector that we have
        vector<pair<string, vector<Stock>>> temp = table[reduceInd];

        //Iterate through the reduced index since we use separate chaining
        for(int i = 0; i < temp.size(); i++){
            //If the date already exists push it back in the existing record
            if(temp[i].first == stonk.date){
                table[reduceInd][i].second.push_back(stonk);
                return;
            }
        }

        //If the record does not exist extract the record
        vector<Stock> insert = {stonk};

        //Push it back in the same position but this time it acts as the first record in a row
        table[reduceInd].push_back(make_pair(stonk.date, insert));
        //Add the new date to our unique list of dates for easy traversal
        dates.push_back(stonk.date);
        elements++;
        //Calculate the load factor
        double loadFactor = (double)elements / bucketSize;

        //Rehash if we exceed the maximum load factor which we specify
        if(loadFactor >= threshold){
            rehash();
        }

    //This version is for storing company names with attributes
    }else{
        int reduceInd = hashFunc(stonk.stockName) % bucketSize;
        //If the entry exists add it to the big vector that we have
        vector<pair<string, vector<Stock>>> temp = table[reduceInd];

        //Iterate through the reduced index since separate chaining is used
        for(int i = 0; i < temp.size(); i++){
            //If the stock already exists, append to its position
            if(temp[i].first == stonk.stockName){
                table[reduceInd][i].second.push_back(stonk);
                return;
            }
        }

        vector<Stock> insert = {stonk};

        //Add the element to its new row since it doesnt have an assigned position
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
    //Initialize the bucket size in our constructor
    this->bucketSize = buckets;
    //Resize the hash table with the number of buckets specified
    table.resize(bucketSize);
}

void HashTable::rehash() {

    //We do not want to perform this operation in place so create a copy
    vector<vector<pair<string, vector<Stock>>>> newTable;
    //Double the current bucket size
    bucketSize = (int)table.size() * 2;
    newTable.resize(bucketSize);

    //Iterate through all elements in our table
    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            //Recalculate the hash function based on the new bucket size to assign new positions
            vector<Stock> allStock = table[i][j].second;
            int reduceInd = hashFunc(table[i][j].first) % bucketSize;
            newTable[reduceInd].push_back(make_pair(table[i][j].first,allStock));
        }

    }

    //Assign the copy table to the actual table
    table = newTable;

}

vector<Stock> HashTable::topNByCompany(const string& stockName, int n, bool print = false, bool sort = true) {

    vector<Stock> storeCompany;
    vector<Stock> ans;

    //If the company name exists in the massive vector we have execute the operations
    if(find(companies.begin(), companies.end(), stockName) != companies.end()){
        //Get the position it is located in
        int reducedIndex = hashFunc(stockName) % bucketSize;
        //Go through all possible spots in the vector since it is separate chaining
        for(int i = 0; i < table[reducedIndex].size(); i++){
            //We know we have found the attributes associated with the company
            if(table[reducedIndex][i].first == stockName){
                storeCompany = table[reducedIndex][i].second;
            }
        }

        //Used for function 3 if we want the top elements of a company
        if(sort){
            //Sort based on descending close price to mimic the max heap
            std::sort(storeCompany.begin(), storeCompany.end(),
                      [] (Stock stock1, Stock stock2) {return stock1.adjClose > stock2.adjClose;});

            //Store the top n elements that we have
            for(int i = 0; i < n; i++){
                ans.push_back(storeCompany[i]);
            }

            //This function is used multiple times in different functions so this flag allows it
            //only to be printed when we want to
            if(print){
                printHeader();
                for(int i = 0; i < ans.size(); i++){
                    printTable(ans[i]);
                }
            }
        //If we want all elements associated with a specific company
        }else{
            if(print){
                printHeader();
                for(int i = 0; i < storeCompany.size(); i++){
                    printTable(storeCompany[i]);
                }
            }
        }
    //Error handling to ensure we dont get a SEGFAULT when indexing
    }else{
        cout << "Not Found in the Data... Please Try Another Company!" << endl;
    }

    return ans;

}

Stock HashTable::maxStock() {
    //https://cplusplus.com/reference/algorithm/max_element/
    vector<Stock> maxStocks;
    //Since we want the maximum price we want to iterate through all of the companies and get the maximum
    for(int i = 0; i < companies.size(); i++){
        maxStocks.push_back(topNByCompany(companies[i], 1)[0]);
    }

    //Get the maximum of all the potential maximum's based on closing price
    Stock ans = *std::max_element(maxStocks.begin(), maxStocks.end(),
                                  [] (Stock stock1, Stock stock2) {return stock1.adjClose < stock2.adjClose;});


    //Print the answer and return
    printHeader();
    printTable(ans);

    return ans;

}

vector<Stock> HashTable::topStocks(int n) {
    //https://cplusplus.com/reference/vector/vector/insert/
    //https://www.geeksforgeeks.org/how-to-erase-duplicates-and-sort-vector-in-cpp/
    vector<Stock> maxStocks;
    vector<Stock> top;
    //Iterate through the companies and get the index it belongs to
    for(int i = 0; i < companies.size(); i++) {
        int reducedIndex = hashFunc(companies[i]) % bucketSize;
        //Iterate through the row of possibilities
        for (int j = 0; j < table[reducedIndex].size(); j++) {
            //Insert it into the maxStocks vector by placing in elements to the vector
            maxStocks.insert(maxStocks.end(), table[reducedIndex][j].second.begin(),
                             table[reducedIndex][j].second.end());

        }
    }

    //Now we need to sort the vector based on closing price to get all of the prices in descending order
    std::sort(maxStocks.begin(), maxStocks.end(),
              [] (Stock stock1, Stock stock2) {return stock1.adjClose > stock2.adjClose;});

    //It was more efficient in terms of time complexity to use the insert operation and get rid of duplicates
    //I was going to use a set or map but think that would defeat the purpose of implementing the hash table
    auto it = std::unique(maxStocks.begin(), maxStocks.end(),
                          [] (Stock stock1, Stock stock2) {return stock1.adjClose == stock2.adjClose;});

    // Remove duplicates elements

    maxStocks.erase(it, maxStocks.end());
    //Print the top n elements as specified by the user
    printHeader();
    for(int i = 0; i < n; i++){
       printTable(maxStocks[i]);
    }

    return top;

}

void HashTable::printHeader() {
    //Format the table column header
    cout << left << setw(15) << "Stock Name"
         << setw(15) << "Date"
         << setw(15) << "Adj. Close"
         << setw(15) << "Volume" << endl;
    cout << string(60, '-') << endl;
}

void HashTable::printTable(const Stock& stonk) {
    //Format the rows as a table
    cout << left << setw(15) << stonk.stockName
         << setw(15) << stonk.date
         << setw(15) << fixed << setprecision(2) << stonk.adjClose
         << setw(15) << stonk.totalVolume << endl;

    cout << string(60, '-') << endl;

}

vector<Stock> HashTable::dateRange(const string& date) {
    printHeader();
    //Create a vector to store our information as well as creating the structure of our time
    vector<Stock> dateStocks;

    //Make it a time object for date comparisons
    time_t timestamp1 = Stock::getDateTime(date);

    //For each of the dates in the vector we want to see if it falls in the range
    for(int i = 0; i < dates.size(); i++) {
        //Navigate to the specific index
        int reducedIndex = hashFunc(dates[i]) % bucketSize;
        //Iterate through all possible options
        for (int j = 0; j < table[reducedIndex].size(); j++) {
            if(table[reducedIndex][j].first == dates[i]){
                time_t timestamp2 = Stock::getDateTime(table[reducedIndex][j].first);;
                //If it falls within the range assign the vector to it and iterate through and print
                if(timestamp1 < timestamp2){
                    dateStocks = table[reducedIndex][j].second;
                    for(int z = 0; z < dateStocks.size(); z++){
                        printTable(dateStocks[z]);
                    }
                }
            }

        }

    }

    return dateStocks;

}
