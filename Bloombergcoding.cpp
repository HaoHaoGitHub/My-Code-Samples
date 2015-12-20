#include <iostream>
#include <string>
#include <algorithm>
#include <climits> 
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string ToNumberSystem26(long n) {
	string s;
	while (n > 0) {
		int m = n % 26;
		if (m == 0) m = 26;
		s = (char) (m + 64) + s;
		n = (n - m) /26;
	}
	return s;
}



int main() {
	cout << "Please enter a integer:" << endl;
	long i;
	cin >> i;
	
	if ((i > pow(2,16)) || (i < 1)) {
		cout << "Invalid integer" << endl;
	}
     
    string result;
    result = ToNumberSystem26(i);
    cout << result << endl;
    return 0;
}