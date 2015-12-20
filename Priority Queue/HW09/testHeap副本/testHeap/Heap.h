//
//  Heap.h
//  testHeap
//
//  Created by Chelsey on 15-4-24.
//  Copyright (c) 2015年 Chelsey. All rights reserved.
//

#ifndef _Heap_h
#define _Heap_h
#include <vector>

using namespace std;

template <class T>
class Heap {
public:
    Heap();
    Heap(T elements[], int size);
    int get_size();
    T remove_element();
    void add_element(T element);
    
private:
    vector<T> v;
};

template <class T>
Heap<T>::Heap() {}

template <class T>
Heap<T>::Heap(T elements[], int size) {
    for(int i = 0; i < size; i++) {
        add_element(elements[i]);
    }
}
        
template <class T>
int Heap<T>::get_size() {
    return v.size();
}

template <class T>
void Heap<T>:: add_element(T element) {
    // 在这写perculate_up
    v.push_back(element);
    int i = v.size() - 1;
    while (i > 0) {
        if (v[i] < v[(i - 1)/2]) {
            v[i] = v[(i - 1)/2];
            v[(i - 1)/2] = element;
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}


template <class T>
T Heap<T>::remove_element() {
    T removeElement = v[0];
    // 在这写perculate_down
    v[0] = v[v.size() - 1];
    v.pop_back();
    int i = 0;
    int temp = 0;
    while (2*i + 2 < v.size()) {
        if (v[2*i + 1] < v[2*i + 2]) {
            temp = 2*i + 1;
        } else {
            temp = 2*i + 2;
        }
        if (v[temp] < v[i]) {
            T temp_value = v[temp];
            v[temp] = v[i];
            v[i] = temp_value;
            i = temp;
        } else {
            break;
        }
    }
    return removeElement;
}


#endif
