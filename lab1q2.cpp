#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

int missSearch(int a[], int n){
    int total = n*(n+1)/2;
    for (unsigned int i = 0; i < n; ++i) {
    	total -= a[i];
    }
    return total;
}


int main() {
    cout << "Enter the number n: " << endl;
    int n;
    cin >> n;
    int T = pow(2,n) - 1;
    int a[T];
    for (unsigned int i = 0; i < T; ++i) {
    	cout << "Enter: " << endl;
    	cin >> a[i];
    }
    cout << endl;

    int result = missSearch(a, T);

    cout << result << endl;
    
}