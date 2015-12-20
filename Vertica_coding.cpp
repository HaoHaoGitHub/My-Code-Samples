// Nov 23 2015 Interview I
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <iomanip>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;
// First method: use sort, time complexity is O(nlogn + k), where n is the number of input
// Assume each of which has a value between 1 to 100 (inclusive)
int OutputSum_Version1(vector<int> sequence, int k) {
	 // Write the corner cases that can improve the speed
	 // If the input is empty or only has one element
     if (sequence.size() == 0) {return 0;}
     if (sequence.size() == 1) {
     	// make sure the value is between the range
     	assert(sequence[0] <= 100 && sequence[0] >= 0);
     	return sequence[0];
     }
     // Sort the vector and find the k largest number
     sort(sequence.begin(), sequence.end());
     // Make sure again the value is between the range
     int max = sequence[sequence.size() - 1];
     // Make sure again the value is between the range
     assert(max <= 100 && max >=1);
     if (k == 1) {return max;}
     int result = 0;
     while (k >= 1) {
        result += sequence[sequence.size() - k];
     	k--;
     }
     return result;
};

// Method 2: Max Heap method
// 1) Build a Max Heap tree in O(n)
// 2) Use Extract_Max k times to get k maximum elements from the Max Heap O(klogn)
// Time complexity: O(n + klogn)
int OutputSum_Version2(int *sequence, int n, int k);
void build_max_heap(int *sequence, int n);
void heapify_max(int *sequence, int n, int i);
int extract_max(int *sequence, int n);
void swap(int* sequence, int a, int b);

int OutputSum_Version2(int *sequence, int n, int k) {
    build_max_heap(sequence, n);
    int result = 0;
    for (int i = 0; i < k; i++) {
        result += extract_max(sequence, n);
    }
    return result;
}

void build_max_heap(int *sequence, int n) {
    // 这里以前的写错了，以前的是(n/2 - 1)
    for (int i = (n - 1)/ 2 ; i >= 0; --i) {
        heapify_max(sequence, n, i);
    }
}

// core function of building the max heap
// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void heapify_max(int *sequence, int n, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int max_ = i;
    if (left < n && sequence[left] > sequence[max_])  
        max_ = left;
    if (right < n && sequence[right] > sequence[max_])  
        max_ = right;
    if (max_ != i) {
        swap(sequence, i, max_);
        heapify_max(sequence, n, max_);
    }
}
// extract the max from our max heap
int extract_max(int *sequence, int n) {
    int tmp = sequence[0];
    sequence[0] = sequence[n-1];
    n--;
    heapify_max(sequence, n, 0);
    return tmp;
}

void swap(int* sequence, int a, int b) {
    int tmp = sequence[a];
    sequence[a] = sequence[b];
    sequence[b] = tmp;
}


int main () {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(23);
    v1.push_back(12);
    v1.push_back(9);
    v1.push_back(30);
    v1.push_back(2);
    v1.push_back(50);
    int k = 3;
    int result1 = OutputSum_Version1(v1, k);
    cout << "Result1 is:" << result1 << endl;
    int A[] = {1, 23, 12, 9, 30, 2, 50};
    int result2 = OutputSum_Version2(A, 7, k);
    cout << "Result2 is:" << result2 << endl;

	return 0;
}




// Time complexity of our algorithm
/* 
The first method: O(nlogn + k), where n is the number of input
The second method: O(n + klogn)
// 1) Build a Max Heap tree in O(n)
// 2) Use Extract_Max k times to get k maximum elements from the Max Heap O(klogn)

It is not the best solution, if depends.
For the first one: if n is very large, then sorting would be more costly than others.
For the second one: if is k is very large (for instance, k is closer or equal to n): then order nonation should
be the same as method 1; When k is much smaller than n, this method is better!
However, both them might not be optimal when n is large, There also has solutions like O(n+kLogk), which is better when
k is smaller than n. 

When m is a varibale: 
We need to examine m first, and then make corresponding operations:
1) When m is very large, leading the sum larger than INT_MAX, we need to have a long, or long long result
2) When m is very close to 1, we can can first simply find numbers between the range and then sum the k largest number
(which might be faster). If m is smaller than k, print error.

*/






