#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "MaxHeap.h"
#include "HashTable.h"
using namespace std::chrono;
using namespace std;

void userInterface(){
    //Print out the menu for the user to see to introduce them to the program
    cout << "=============================================================\n"
            "                   WELCOME TO MARKET MATRIX                  \n"
            "=============================================================\n"
            "         Get ready to explore performance between:\n"
            "                HASH TABLE vs. MAX HEAP\n"
            "-------------------------------------------------------------\n" << endl;

}

int userChoice(){
    //Prompts the user for input at every step of the way to test which data structure to use
    cout << "How would you like to store the data?" << endl;
    cout << "1: Max Heap" << endl;
    cout << "2: Hash Table" << endl;

    //Store the output in a variable which will be returned
    int dataStructure;
    cin >> dataStructure;
    cout << endl;

    return dataStructure;
}

//Chrono Operations: https://stackoverflow.com/questions/36751133/proper-method-of-using-stdchrono

int main() {
    //Print the menu for the user
    userInterface();

    //The duration of the program goes until the user specifies to exit
    bool exit = false;

    while(!exit){

        //Initialize our data structures
        MaxHeap stockHeap;
        HashTable stockTable = HashTable(500);
        HashTable stockTableDates = HashTable(300);

        //Read in the csv file which is in our c-make file
        std::string filename = "proj3_sp500_stocks.csv";
        std::ifstream file(filename);

        //Ignore the first row of the csv file which acts as our header
        string line;
        getline(file, line);
        while (getline(file, line)) {
            //Get each row of the CSV file
            stringstream ss(line);
            string value;
            //Acts as the values to pass in as a row
            vector<string> row;
            //Stop at each comma since it is a csv file and pass it in to the vector
            while(getline(ss, value, ',')){
                row.push_back(value);
            }

            //Insert each row into our data structures
            stockHeap.insert(Stock(row[0], row[1], stoi(row[2]), stod(row[3])));
            stockTable.insert(Stock(row[0], row[1], stoi(row[2]), stod(row[3])), false);
            stockTableDates.insert(Stock(row[0], row[1], stoi(row[2]), stod(row[3])), true);

        }

        //Close the csv file to make sure we get no errors
        file.close();

        //Menu options that will apear for the user
        cout << "Menu Options:" << endl;
        cout << "1: Top X Stocks Total" << endl;
        cout << "2: Search by Company" << endl;
        cout << "3: Top X Prices by Company" << endl;
        cout << "4: Get Maximum Price" << endl;
        cout << "5: Search by Date Range" << endl;
        cout << "6: Exit Program!" << endl;

        //Capture the user input and then execute based on what is typed in
        int userInput;
        int dataStructure;
        cin >> userInput;

        //Get the top num stocks in the entire dataset based on price (market cap was not an option)
        if(userInput == 1){
            dataStructure = userChoice();
            int num;
            //User specifies how many stocks they want
            cout << "Please Enter the Number of Stocks: ";
            cin >> num;
            cout << endl;

            //Perform the operation on the max heap and capture how long it takes
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.topN(num);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Perform the operation on the hash table and capture how long it takes
            }else if(dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTable.topStocks(num);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Capturing just in case the user hits a different number then expected
            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }

        //Search the company name and get all corresponding results
        }else if(userInput == 2){
            dataStructure = userChoice();
            //Capture the company which will be used for the arguments
            string company;
            cout << "Please Enter the Company Name: ";
            cin >> company;

            //Perform the operation on the max heap and capture how long it takes
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.searchCompany(0, company, true);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Perform the operation on the hash table and capture how long it takes
            }else if(dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTable.topNByCompany(company, 0, true, false);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Ensures that the proper input is being taken in by the user
            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }
        //Similar to the function above but we are getting the top elements specified by the user
        }else if(userInput == 3){
            dataStructure = userChoice();
            //Store the company as well as how many stocks are desired

            string company;
            cout << "Please Enter the Company Name: ";
            cin >> company;
            int num;
            cout << "Please Enter the Number of Stocks: ";
            cin >> num;
            cout << endl;

            //Perform the operation on the max heap and capture how long it takes
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.searchCompany(num, company, false);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            //Perform the operation on the hash table and capture how long it takes
            }else if(dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTable.topNByCompany(company, num, true, true);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }

        //Get the maximum price in the entire dataset and the corresponding attributes
        }else if(userInput == 4){
            dataStructure = userChoice();
            //If the data structures is the max heap perform its operation and capture the time
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.printMax();
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;

            //Now capture the output and time if it is chosen for the hash table
            }else if (dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTable.maxStock();
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }

        //Get all of the stock information after the date specified by the user
        }else if(userInput == 5){
            dataStructure = userChoice();
            //Prompting the user for a date in a specific format
            cout << "Please Enter the Date in m/d/yyyy Format: ";
            string date;
            cin >> date;

            //Perform the function on the max heap
            if(dataStructure == 1){
                auto start = high_resolution_clock::now();
                stockHeap.searchDate(date);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Perform the function on the hash table
            }else if(dataStructure == 2){
                auto start = high_resolution_clock::now();
                stockTableDates.dateRange(date);
                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by function: "
                     << duration.count() << " microseconds" << endl;
            //Invalid Input
            }else{
                cout << "Wrong Input Please Try Again" << endl;
            }
        //We want to exit the program
        }else if(userInput == 6){
            exit = true;
        }else{
            cout << "Invalid Input Please Try Again!" << endl;
        }

        cout << endl;

    }

    return 0;

}