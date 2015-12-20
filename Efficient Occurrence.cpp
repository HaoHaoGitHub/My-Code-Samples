//
//  main.cpp
//  test2Q3
//
//  Created by Chelsey on 3/25/15.
//  Copyright (c) 2015 Chelsey. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;



void Occurrences(const vector<string> &data, const string &x, int low, int high, int &result, bool flag) {
    if (low > high) return;
    int mid = low + (high - low) / 2;
    if (data[mid] == x) {
        result = mid;
        if (flag)
            Occurrences(data, x, low, mid - 1, result, flag);
        else
            Occurrences(data,x, mid + 1, high, result, flag);
    } else if (data[mid] > x) {
        Occurrences(data, x, low, mid - 1, result, flag);
    } else {
        Occurrences(data, x, mid + 1, high, result, flag);
    }
}


int Occurrences(const vector<string> &data, const string &x) {
    int result1 = -1, result2 = -1;
    Occurrences(data, x, 0, data.size() - 1, result1, true);
    if (result1 != -1) {
        Occurrences(data, x,  0, data.size() - 1, result2, false);
        return result2 - result1 + 1;
    } else return 0;
}



int main() {
    vector<string> data;
    data.push_back("abe");
    data.push_back("abe");
    data.push_back("ace");
    data.push_back("ace");
    data.push_back("ace");
    data.push_back("ace");
    data.push_back("acg");
    data.push_back("acm");
    data.push_back("acn");
    data.push_back("aeg");
    string x = "ace";
    cout << Occurrences(data, x) << endl;
    return 0;
}




// ===========================================================================
// Another version

// the recursive helper function
int occurrences(const std::vector<std::string> &data, const std::string &element,
                int s1, int s2, int e1, int e2) {
    // s1 & s2 are the current range for the start / first occurence
    // e1 & e2 are the current range for the end / last occurence (+1)
    assert (s1 <= s2 && e1 <= e2);
    if (s1 < s2) {
        // first use binary search to find the first occurrence of element
        int mid = (s1 + s2) / 2;
        if (data[mid] >= element) {
            return occurrences(data,element,s1,mid,e1,e2);
        }
        return occurrences(data,element,mid+1,s2,e1,e2);
    } else if (e1 < e2) {
        // then use binary search to find the last occurrence of element (+1)
        int mid = (e1 + e2) / 2;
        // ==================================================
        if (data[mid] > element) {
        // ==================================================
            return occurrences(data,element,s1,s2,e1,mid);
        }
        return occurrences(data,element,s1,s2,mid+1,e2);
    } else {
        // the simply subtract these indices
        assert (s1 == s2 && e1 == e2 && e1 >= s1);
        return e1 - s1;
    }
}


















