#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "MaxHeap.h"
#include "HashTable.h"
#include <iomanip>
using namespace std::chrono;
using namespace std;

void userInterface(){
    cout << "=============================================================\n"
            "                   WELCOME TO MARKET MATRIX                  \n"
            "=============================================================\n"
            "         Get ready to explore performance between:\n"
            "                HASH TABLE vs. MAX HEAP\n"
            "-------------------------------------------------------------\n" << endl;

}


int userChoice(){
    cout << "How would you like to store the data?" << endl;
    cout << "1: Max Heap" << endl;
    cout << "2: Hash Table" << endl;

    int dataStructure;
    cin >> dataStructure;
    cout << endl;

    return dataStructure;
}


int main() {
    userInterface();

    bool exit = false;

    while(!exit){

        MaxHeap stockHeap;
        HashTable stockTable = HashTable(500);

        std::string filename = "proj3_sp500_stocks.csv"; // Replace with your CSV file name
        std::ifstream file(filename);


        string line;
        getline(file, line);
        while (getline(file, line)) {
            // Process each line (row) of the CSV file here
            stringstream ss(line);
            string value;
            vector<string> row;
            while(getline(ss, value, ',')){
                row.push_back(value);
            }

            stockHeap.insert(Stock(row[0], row[1], stoi(row[2]), stod(row[3])));
            stockTable.insert(Stock(row[0], row[1], stoi(row[2]), stod(row[3])));

        }

        file.close();

        cout << "Menu Options:" << endl;
        cout << "1: Top X Stocks Total" << endl;
        cout << "2: Print Stock Information" << endl;
        cout << "3: Top X Prices by Company" << endl;
        cout << "4: Get Maximum Price" << endl;
        cout << "5: Search by Date Range" << endl;
        cout << "6: Exit Program!" << endl;

        int userInput;
        int dataStructure;
        cin >> userInput;

        if(userInput == 1){
            dataStructure = userChoice();
            int num;
            cout << "Please Enter the Number of Stocks: ";
            cin >> num;
            cout << endl;

            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.topN(num);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            }else if(dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTable.topStocks(num);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }


        }else if(userInput == 2){
            dataStructure = userChoice();

        }else if(userInput == 3){
            dataStructure = userChoice();
            string company;
            cout << "Please Enter the Company Name: ";
            cin >> company;
            int num;
            cout << "Please Enter the Number of Stocks: ";
            cin >> num;
            cout << endl;
            if(dataStructure == 1){

                auto start = high_resolution_clock::now();
                stockHeap.searchCompany(num, company);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            }else if(dataStructure == 2){

                auto start = high_resolution_clock::now();
                stockTable.topNByCompany(company, num, true);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            }
        }else if(userInput == 4){
            dataStructure = userChoice();
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.printMax();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            }else{
                auto start = high_resolution_clock::now();
                stockTable.maxStock();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            }
        }else if(userInput == 5){
            dataStructure = userChoice();
            if(dataStructure == 1){
                cout << "Please Enter the Date in m/d/yyyy Format: ";
                string date;
                cin >> date;
                stockHeap.searchDate(date);
            }
        }

        if(userInput == 6){
            exit = true;
        }

        cout << endl;

    }

    return 0;

}