
#include <iostream>
#include <vector>
#include <algorithm>


std::vector<int> remove_duplicates(int a[], int n) {
    std::vector<int> v;
    
    for (unsigned int i = 0; i < n; ++i) { v.push_back(a[i]);}

    if (n == 1) {
    	return v;
    } else {
        std::sort(v.begin(), v.end());
        std::vector<int> without_duplicates;
        unsigned int i;
        for (i = 0; i < n - 1; i++) {
            if (v[i] != v[i+1]) { without_duplicates.push_back(v[i]);}
        }
        i --;
        // Consider the last element:
        if (v[i] != v[i+1]) { without_duplicates.push_back(v[i+1]);}
        return without_duplicates;
    }  
}

int main () {
	int n, a[n];
	std::cout << "Please enter the size: " << std::endl;
	std::cin >> n;
	for (unsigned int i = 0; i < n; ++i) {
		std::cout << "Pleaase enter: ";
		std::cin >> a[i]; 
	}

    std::vector<int> result;
    result = remove_duplicates(a, n);

    // Output the result:
    for (unsigned int i = 0; i < result.size(); ++i) { std::cout << result[i] << " ";}
    std::cout << std::endl;
} 