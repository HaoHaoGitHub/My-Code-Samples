#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;


int modular_pow(int base, int exponent, int modulus) {
	int c = 1;
	for (int i = 1; i <= exponent; i++) {
          c = (c * base) % modulus;
	}
	return c;
}

int main() {
	int example = modular_pow(2, 125, 127);
	cout << "The result is: " << example << endl;

}