#include <iostream>
#include <vector>

void calculate_LNS (std::vector<int>& D, std::vector<std::vector<int> >& L) {

	L[0].push_back(D[0]);

	for (int i = 1; i < D.size(); ++i) {
		for (int j = 0; j < i; ++j) {
		     if ((D[j] <= D[i]) && (L[i].size() < L[j].size() + 1)) {
		     	L[i] = L[j];
		     }
		}
		L[i].push_back(D[i]);
	}

}


int main(int argc, char const *argv[]) {
	int a[] = {-90, 20, 30, 30, 30, 4, 50};
	std::vector<int> arr(a, a + sizeof(a)/sizeof(a[0]));
    std::vector<std::vector<int> > L(arr.size());

	calculate_LNS(arr, L);
	int longest_length = 0;
    for (int i = 0; i < L.size(); i++) {
    	for (int j = 0; j < L[i].size(); ++j) {
    		std::cout << L[i][j] << " ";
    	}
    	if (L[i].size() > longest_length) {
    		longest_length = L[i].size();
    	}
    	std::cout << std::endl;
    }

    std::cout << "Longest length is: " << longest_length << std::endl;
	 
	return 0;
}