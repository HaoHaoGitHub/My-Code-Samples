#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T = 0;
    int N, K, P;
    int *A, *B, *PA, *PB;   // PA[i]: minimum total penalty after arriving at A[i]
    int costAA=999999, costAB=999999, costBA=999999, costBB=999999;
    cin >> T;
    for (int testIndex = 0; testIndex < T; testIndex ++)
    {
        costAA=999999, costAB=999999, costBA=999999, costBB=999999;
        cin >> N >> K >> P;
        A = new int [N];    B = new int [N];
        PA = new int [N];   PB = new int [N];
        for (int i=0; i<N; i++)
            cin >> A[i];
        for (int i=0; i<N; i++)
            cin >> B[i];
        if (K>=N)
        {
            costAA = A[0]+A[N-1];
            costBB = B[0]+B[N-1];
            costAB = A[0]+B[N-1]+P;
            costBA = B[0]+A[N-1]+P;
            costAA = min(costAA,costBB);
            costAA = min(costAA,costAB);
            costAA = min(costAA,costBA);
            cout << costAA << '\n';
        }
        else
        {
            PA[N-1] = A[N-1]; PB[N-1] = B[N-1];
            for (int i=1; i<=K; i++)
            {
                PA[N-1-i] = A[N-1-i]+min(P+PB[N-1],PA[N-1]);
                PB[N-1-i] = B[N-1-i]+min(P+PA[N-1],PB[N-1]);
            }
            for (int i=N-1-K-1; i>=0; i--)
            {            
                costAA=costAB=costBA=costBB=999999;
                for (int step=1; step<=K; step++)
                {
                    costAA = min(costAA,PA[i+step]);
                    costBB = min(costBB,PB[i+step]);
                    costAB = min(costAB,PB[i+step]);
                    costBA = min(costBA,PA[i+step]);
                }
                PA[i] = min(costAA,costAB+P)+A[i];
                PB[i] = min(costBB,costBA+P)+B[i];
            }
            cout << min(PA[0],PB[0]) << '\n';
        }
        delete [] A; delete [] B;
        delete [] PA; delete [] PB;
    }
    return 0;
}