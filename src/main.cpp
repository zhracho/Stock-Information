#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void userInterface(){
    cout << "=============================================================\n"
            "                   WELCOME TO MARKET MATRIX                  \n"
            "=============================================================\n"
            "         Get ready to explore performance between:\n"
            "                SPLAY TREE vs. MAX HEAP\n"
            "-------------------------------------------------------------\n" << endl;

}

int main() {
    userInterface();
    bool exit = false;

    while(!exit){

        cout << "Menu Options:" << endl;
        cout << "1: Top 10 Stocks" << endl;
        cout << "2: Print Stock Information" << endl;
        cout << "3: Search by Company" << endl;
        cout << "4: Get Maximum Price" << endl;
        cout << "5: Exit Program!" << endl;

        int userInput;
        cin >> userInput;

        if(userInput == 4){
            exit = true;
        }

    }

//    std::string filename = "proj3_sp500_stocks.csv"; // Replace with your CSV file name
//    std::ifstream file(filename);
//
//    if (!file.is_open()) {
//        std::cerr << "Error opening file: " << filename << std::endl;
//        return 1;
//    }
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