#include "MaxHeap.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void MaxHeap::insert(Stock stonk) {

    heap.push_back(stonk);
    int child = heap.size() - 1;
    int parent = (child - 1)/2;

    while(parent >= 0 && (heap[parent].adjClose < heap[child].adjClose)){
        std::swap(heap[parent], heap[child]);
        child = parent;
        parent = (child - 1)/2;
    }

}

void MaxHeap::printHeap() {

    for(auto & i : heap){
        cout << i.stockName << " " << i.adjClose << endl;
    }

}

Stock MaxHeap::maxElement() {
    return heap[0];
}

void MaxHeap::heapifyDown(vector<Stock>& vec, int index) {

    int large = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    //If the left or right child index greater than size dont do anything
    if(left > vec.size() || right > vec.size())
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
    else if(vec[left].adjClose < vec[right].adjClose){
        //Switch the elements
        std::swap(vec[right], vec[large]);
        //Recursive call moving to the right
        heapifyDown(vec,  right);
    }

}

Stock MaxHeap::extractMax() {
    Stock extracted = maxElement();
    heap.pop_back();
    heap[0] = heap[heap.size()];
    heapifyDown(heap, 0);

    return extracted;

}

void MaxHeap::searchCompany(int x, const string& stockName) {

    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    int count = 0;

    string stockNameLower;

    for(int i = 0; i < stockName.length(); i++){
        stockNameLower += (char)toupper(stockName[i]);
    }

    for(unsigned int i = 0; i < heap.size(); i ++){
        if(count == x)
            break;

        Stock search = copy.extractMax();
        if(search.stockName == stockNameLower){
            ans.push_back(search);
            count++;
        }
    }

    printHeader();
    for(auto & i : ans){
        printTable(i);
    }

}

void MaxHeap::printMax() {
    Stock maxPrice = maxElement();


    printHeader();
    printTable(maxPrice);

}

void MaxHeap::searchDate(const string& startDate) {

    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    tm date1 = {};


    int startDay = Stock::getDate(startDate);
    int startMonth = Stock::getMonth(startDate);
    int startYear = Stock::getYear(startDate);

    date1.tm_year = startYear - 1900;
    date1.tm_mon = startMonth- 1;
    date1.tm_mday = startDay;

    time_t timestamp1 = mktime(&date1);
    time_t timestamp2;

    for(unsigned int i = 0; i < heap.size(); i ++){

        Stock search = copy.extractMax();
        tm date2 = {};

        int stockDate = Stock::getDate(search.date);
        int stockYear = Stock::getYear(search.date) - 1900;
        int stockMonth = Stock::getMonth(search.date) - 1;

        date2.tm_year = stockYear;
        date2.tm_mon = stockMonth;
        date2.tm_mday = stockDate;

        timestamp2 = mktime(&date2);

        if(timestamp1 < timestamp2){
            ans.push_back(search);
        }
    }

    printHeader();
    for(auto & i : ans){
        printTable(i);
    }


}

void MaxHeap::topN(int n) {

    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    for(int i = 0; i < n; i++){
        Stock top = copy.extractMax();
        ans.push_back(top);
    }

    printHeader();
    for(auto & i : ans){
        printTable(i);
    }

}

void MaxHeap::printHeader() {
    cout << left << setw(15) << "Stock Name"
         << setw(15) << "Date"
         << setw(15) << "Adj. Close"
         << setw(15) << "Volume" << endl;
    cout << string(60, '-') << endl;
}

void MaxHeap::printTable(const Stock& stonk) {
    cout << left << setw(15) << stonk.stockName
         << setw(15) << stonk.date
         << setw(15) << fixed << setprecision(2) << stonk.adjClose
         << setw(15) << stonk.totalVolume << endl;

    cout << string(60, '-') << endl;
}
