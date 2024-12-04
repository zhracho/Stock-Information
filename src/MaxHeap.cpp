#include "MaxHeap.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
//The vector documentation page below was extremely helpful for building an optimized workflow
//https://cplusplus.com/reference/vector/vector/
void MaxHeap::insert(Stock stonk) {
    //Slide 28 of the Heaps Lecture Slides were helpful during this implementation
    //Push the stock to the end of the heap
    heap.push_back(stonk);

    //Get access to the child and parents nodes within the heap
    int child = heap.size() - 1;
    int parent = (child - 1)/2;

    //Essentially acts as our heapifyUp, swapping elements until each parents is greater than its children
    //and the top elements is the maximum value in the entire dataset
    while(parent >= 0 && (heap[parent].adjClose < heap[child].adjClose)){
        std::swap(heap[parent], heap[child]);
        child = parent;
        parent = (child - 1)/2;
    }

}

Stock MaxHeap::maxElement() {
    //The element at the top of the max heap is the largest element
    return heap[0];
}

void MaxHeap::heapifyDown(vector<Stock>& vec, int index) {
    //Code for this statement was taking from Programming Quiz 6 on Edugator
    //Slightly modified as I noticed some bugs when implementing on a larger scale

    //Get the left and right child
    int large = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    //If the left or right child index greater than size dont do anything
    if(left >= vec.size() && right >= vec.size())
        return;

    //If our array already has the larger element than the children dont do anything
    if(vec[left].adjClose < vec[large].adjClose && vec[right].adjClose < vec[large].adjClose)
        return;

    //If the left child is greater than the right child
    if(vec[left].adjClose > vec[right].adjClose){
        //Switch the elements
        std::swap(vec[left], vec[large]);
        //Recursive call moving to the left
        heapifyDown(vec, left);
    }

    //If the right child is greater than the left child
    else if(vec[left].adjClose <= vec[right].adjClose){
        //Switch the elements
        std::swap(vec[right], vec[large]);
        //Recursive call moving to the right
        heapifyDown(vec,  right);
    }

}

Stock MaxHeap::extractMax() {
    //Store the top element in a stock variable before deletion
    Stock extracted = heap[0];
    //Replace the first element with the last element in the heap
    heap[0] = heap[heap.size()-1];
    //Now we can get rid of that last element
    heap.pop_back();

    //Heapify down to correctly get our new max heap
    heapifyDown(heap, 0);

    return extracted;

}

void MaxHeap::searchCompany(int x, const string& stockName, bool all = false) {

    //Create a copy so we can keep extracting from without messing up our original structure
    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    int count = 0;

    string stockNameLower;

    //Basic input parsing that converts all the output to uppercase to ensure a match is found
    for(int i = 0; i < stockName.length(); i++){
        stockNameLower += (char)toupper(stockName[i]);
    }

    if(!all) {
        //Iterates through the entire heap or until n is achieved
        for (unsigned int i = 0; i < heap.size(); i++) {
            //Get our current maximum stock
            Stock search = copy.extractMax();
            //If we are already at the count we dont continue
            if (count == x)
                break;
            //If that stock is what we are looking for
            if (search.stockName == stockNameLower) {
                ans.push_back(search);
                count++;
            }
        }
    }else{
        for (unsigned int i = 0; i < heap.size(); i++) {
            //Get our current maximum stock
            Stock search = copy.extractMax();
            //If that stock is what we are looking for
            if (search.stockName == stockNameLower) {
                ans.push_back(search);
            }
        }
    }

    //Print the final output of stocks
    if(ans.empty()){
        cout << endl;
        cout << "No Companies Found for the Given Search" << endl;
    }else{
        printHeader();
        for(auto & i : ans){
            printTable(i);
        }
    }

}

void MaxHeap::printMax() {
    //Just gets the first element in the array and formats it as a table for printing
    Stock maxPrice = maxElement();
    printHeader();
    printTable(maxPrice);

}

void MaxHeap::searchDate(const string& startDate) {

    //Creates a copy of the heap for popping off the elements
    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    //Convert to a timestamp
    time_t timestamp1 = Stock::getDateTime(startDate);

    for(unsigned int i = 0; i < heap.size(); i ++){
        //Get the current maximum element
        Stock search = copy.extractMax();

        //Convert to timestamp
        time_t timestamp2 = Stock::getDateTime(search.date);

        //If the date comes after what we initialized push it back
        if(timestamp1 < timestamp2){
            ans.push_back(search);
        }
    }

    if(ans.empty()){
        cout << endl;
        cout << "No Dates Found for the Given Search" << endl;
    }else {
        printHeader();
        for (auto &i: ans) {
            printTable(i);
        }
    }

}

void MaxHeap::topN(int n) {

    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    for(int i = 0; i < n; i++){
        //For whatever the user specifies we pop off those elements and store them
        Stock top = copy.extractMax();
        ans.push_back(top);
    }

    //Creates the header of the table with all of the column names
    printHeader();
    for(auto & i : ans){
        //Print the current row in the table
        printTable(i);
    }

}

void MaxHeap::printHeader() {
    //Formatting all of our output as a table
    //https://en.cppreference.com/w/cpp/io/manip/setw
    cout << left << setw(15) << "Stock Name"
         << setw(15) << "Date"
         << setw(15) << "Adj. Close"
         << setw(15) << "Volume" << endl;
    cout << string(60, '-') << endl;
}

void MaxHeap::printTable(const Stock& stonk) {
    //Same format as the function above but allows for easy formatting as a tuple
    //https://en.cppreference.com/w/cpp/io/manip/setw
    cout << left << setw(15) << stonk.stockName
         << setw(15) << stonk.date
         << setw(15) << fixed << setprecision(2) << stonk.adjClose
         << setw(15) << stonk.totalVolume << endl;

    cout << string(60, '-') << endl;
}

