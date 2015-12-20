#include <iostream>
#include <vector>
using namespace std;

// Suppose we have infinite supply of belowing valued coins
// The idea is simple Greedy Algorithm. Start from largest possible denomination and
// keep adding denominations while remaining value is greater than 0;

int deno[] = {1, 5, 10, 25, 50};
int n = sizeof(deno)/sizeof(deno[0]);

void findMin (int V, int & min_number) {
	// Initialize result
	std::vector<int> answer;
	// Traverse through all denomination
	for (int i = n - 1; i >= 0; i--) {
		// Find denominations
		while (V >= deno[i]) {
			V -= deno[i];
			answer.push_back(deno[i]);
		}
	}

	// Print result
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i] << " ";
	}
	min_number = answer.size();

}

int main () {
	cout << "Please enter an input n" << endl;
	int n;
	cin >> n;
	cout << endl;
    cout << "Following is minimal number of change for " << n << " is ";
    int min_number;
    findMin(n, min_number);
    cout << endl;
    cout << "Minimum number of coins required that add up to n is: " << min_number << endl;
    return 0;
}