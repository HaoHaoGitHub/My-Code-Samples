#include <iostream>
#include <cstdlib>
using namespace std;

long long modexp(long long x, long long y, long long n) {
  long long z;
  if (y==0)
    return 1;
  else {
      z = modexp(x,y/2,n);
      if (y%2==0) return (z*z)%n;
      else return (x*((z*z)%n)%n);
  }
}

int prime(int n) {
  int k;
  int random_integer;
  k = 0;
  while (k < 15) {
      random_integer = (rand()%n)+1; 
      // cout << k << " " << random_integer << endl;
      if (random_integer%2 ==0) random_integer++;
      if (random_integer == n) random_integer -= 2;
      //cout << random_integer << endl;
      if (modexp((long long)random_integer,(long long)n-1,(long long)n)!=1) {
        // a^(p-1) = 1 mode p
	  //   cout << n << " is not a prime number\n"; 
	       return -1;
	    }
      k++;
  }
  cout << n << " is probabily a prime "<< endl;
  return 1;
}
int main(void)
{
  int i;
  for (i = 3; i< 100000000; i = i+2)
    prime(i);
  return 0;
}