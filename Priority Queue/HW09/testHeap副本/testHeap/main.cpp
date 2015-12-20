//
//  main.cpp
//  testHeap
//
//  Created by Chelsey on 15-4-24.
//  Copyright (c) 2015年 Chelsey. All rights reserved.
//

#include <iostream>
#include <string>
#include "Heap.h"
using namespace std;

int main() {
    Heap<string> heap1;
    heap1.add_element("George");
    heap1.add_element("Michael");
    heap1.add_element("Tom");
    heap1.add_element("Adam");
    heap1.add_element("Jones");
    heap1.add_element("Peter");
    
    while (heap1.get_size() > 0) {
        cout << heap1.remove_element() << " ";
    }
    cout << endl;
    
    int numbers[] = {8, 9, 2, 3, 4, 1, 5, 6, 7};
    Heap<int> heap2(numbers, 9);
    while (heap2.get_size() > 0) {
        cout << heap2.remove_element() << " ";
    }
    
    return 0;
}
