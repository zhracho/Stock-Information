#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MaxHeap.h"
#include "RedBlack.h"

using namespace std;

void userInterface(){
    cout << "=============================================================\n"
            "                   WELCOME TO MARKET MATRIX                  \n"
            "=============================================================\n"
            "         Get ready to explore performance between:\n"
            "                SPLAY TREE vs. MAX HEAP\n"
            "-------------------------------------------------------------\n" << endl;

}

int userChoice(){
    cout << "How would you like to store the data?" << endl;
    cout << "1: Max Heap" << endl;
    cout << "2: Red Black Tree" << endl;

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
        RedBlack stockTree;

        Stock stock = Stock("AAPL", "1/1/2024", 200.5, 2900);

        // Insert stock data
        stockTree.insert(stock);

        stock = Stock("AAPL", "1/2/2024", 400.5, 2900);
        stockTree.insert(stock);
        stock = Stock("AAPL", "1/3/2024", 100.5, 2900);
        stockTree.insert(stock);

        stock = Stock("AAPL", "1/3/2024", 500.5, 2900);
        stockTree.insert(stock);

        stock = Stock("AAPL", "1/3/2024", 700, 2900);
        stockTree.insert(stock);




        cout << "Menu Options:" << endl;
        cout << "1: Top 10 Stocks Total" << endl;
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
        }else if(userInput == 2){
            dataStructure = userChoice();
        }else if(userInput == 3){
            dataStructure = userChoice();
            if(dataStructure == 1){
                cout << "Please Enter the Company Name: ";
                string company;
                cin >> company;
                cout << "Please Enter the Number of Stocks: ";
                int num;
                cin >> num;
                cout << endl;
                stockHeap.searchCompany(num, company);

            }
        }else if(userInput == 4){
            dataStructure = userChoice();
            if(dataStructure == 1){
                stockHeap.printMax();
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

//    std::string filename = "proj3_sp500_stocks.csv"; // Replace with your CSV file name
//    std::ifstream file(filename);
//
//
//    std::string line;
//    std::vector<std::string> row;
//    while (std::getline(file, line)) {
//        // Process each line (row) of the CSV file here
//        std::cout << line << std::endl;
//    }
//
//    file.close();





    return 0;

}