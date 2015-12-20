#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector< vector<ll> > matrix;
const ll p = 23456;

void print_matrix(matrix a) {
	for (int i = 0; i < a.size(); ++i) {
    	for (int j = 0; j < a[0].size(); ++j) {
    		cout << a[i][j] << " ";
    	}
    	cout << endl;
    }
}

// compute A * B
matrix mul(matrix A, matrix B) {
	matrix C(2, vector<ll>(2));
	C[0][0] = (A[0][0]*B[0][0] + A[0][1]*B[1][0]) % p;
	C[0][1] = (A[0][0]*B[0][1] + A[0][1]*B[1][1]) % p;
	C[1][0] = (A[1][0]*B[0][0] + A[1][1]*B[1][0]) % p;
    C[1][1] = (A[1][0]*B[0][1] + A[1][1]*B[1][1]) % p;
	return C;
}


// computes A ^ n (recursion)
matrix pow(matrix A, int n) {
    if (n == 1) return A;
    if (n % 2) return mul(A, pow(A, n-1));
    matrix X = pow(A, n/2);
    return mul(X, X);
}

int fib(int N) {
    std::vector<ll> F1(2);
    F1[0] = 0;
    F1[1] = 1;
    
    // create matrix T
    matrix T(2, std::vector<ll>(2));
    T[0][0] = 0; 
    T[0][1] = 1;
    T[1][0] = 1;
    T[1][1] = 1;

    // raise T to the (N - 1)th power
    if (N == 1) return 1;
    T = pow(T,N);

    ll result = 0;
    result = (T[0][0] * F1[0] + T[0][1] * F1[1]) % p;
    return result;
}



int main () {
    ll result;
    result = fib(23456);
    cout << result << endl;
}










