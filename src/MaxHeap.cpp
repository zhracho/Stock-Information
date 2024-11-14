#include "MaxHeap.h"
#include <iostream>
using namespace std;

void MaxHeap::insert(string stockName, string date, double adjClose, int totalVolume) {
    Stock stock = Stock(stockName, date, adjClose, totalVolume);

    heap.push_back(stock);
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

    for(unsigned int i = 0; i < heap.size(); i ++){
        if(count == x)
            break;

        Stock search = copy.extractMax();
        if(search.stockName == stockName){
            ans.push_back(search);
            count++;
        }
    }

    for(auto & i : ans){
        cout <<"Date: " << i.date << " Company: " << i.stockName << " Adj. Close: " <<
        i.adjClose << " Volume: " << i.totalVolume<< endl;
    }

}

void MaxHeap::printMax() {
    Stock maxPrice = maxElement();

    cout <<"Date: " << maxPrice.date << " Company: " << maxPrice.stockName <<
    " Adj. Close: " << maxPrice.adjClose << " Volume: " << maxPrice.totalVolume<< endl;

}

int MaxHeap::getYear(const string& dateParse) {
    int month = dateParse.find('/');
    int day = dateParse.find('/', month + 1);

    return stoi(dateParse.substr(day + 1));

}

int MaxHeap::getMonth(const string& dateParse) {
    //https://cplusplus.com/reference/string/string/find/
    int month = dateParse.find('/');
    month = stoi(dateParse.substr(0, month));
    return month;
}

int MaxHeap::getDate(const string& dateParse) {
    //https://cplusplus.com/reference/string/string/find/
    int month = dateParse.find('/');
    int date = dateParse.find('/', month + 1);

    return stoi(dateParse.substr(month + 1, date - 1));
}

void MaxHeap::searchDate(const string& startDate) {

    MaxHeap copy;
    copy.heap = heap;
    vector<Stock> ans;

    int startDay = getDate(startDate);
    int startMonth = getMonth(startDate);
    int startYear = getYear(startDate);



    for(unsigned int i = 0; i < heap.size(); i ++){

        Stock search = copy.extractMax();
        if(getDate(search.date) >= startDay &&
        getYear(search.date) >=  startYear && getMonth(search.date) >= startMonth){
            ans.push_back(search);
        }
    }

    for(auto & i : ans){
        cout <<"Date: " << i.date << " Company: " << i.stockName << " Adj. Close: " <<
             i.adjClose << " Volume: " << i.totalVolume<< endl;
    }


}
