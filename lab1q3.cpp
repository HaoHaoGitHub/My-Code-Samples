#include <iostream>
#include <vector> 
#include <algorithm>
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
    
    cout << "Result of the array: " << endl;
    for (unsigned int i = 0; i < V.size(); ++i) {
        cout << V[i] << " ";
    }
    cout << endl;
    int i = 0, j = n - 1;
    while (i < j) {
    	int sum = V[i] + V[j];
    	if (sum == 0) {
    		cout << i << " " << j << endl;
    		break;
    	}
    	else if (sum < 0) i++;
    	else if (sum > 0) j--;
    }
}