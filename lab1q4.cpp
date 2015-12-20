#include <iostream>
#include <vector> 
#include <algorithm>
#include <set>
using namespace std;


int main() {
	cout << "Enter the number of elements: " << endl; 
	int n;
	cin >> n; 
    std::vector<int> V;
    for (unsigned int i = 0; i < n; ++i) {
    	cout << "Enter element:" << endl;
    	int a;
        cin >> a;
        V.push_back(a);
    }
    
    sort(V.begin(),V.end()); // n*O(log(n))
    cout << endl;
    set< vector<int> > triplets;
    std::vector<int> triplet(3);
    
    for (unsigned int i = 0; i < n - 1; ++i) {
        int a = V[i];
        int start = i + 1;
        int end = n - 1;
        while (start < end) {
            int b = V[start];
            int c = V[end];
            if (a + b + c == 0) {
                triplet[0] = a;
                triplet[1] = b;
                triplet[2] = c;
                triplets.insert(triplet); // Eliminate those duplicates!!!
                cout << a << " " << b << " " << c << endl;
                start = start + 1;
                end = end - 1;
            } 
            else if (a + b + c > 0) end = end - 1;
            else start = start + 1;

        }

    }

    int result = triplets.size();

    cout << endl;
    cout << "Count is: " << result << endl;


}









