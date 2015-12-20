#include <iostream>
#include <vector>
using namespace std;

int main() {
	int location[] = {5, 6, 7, 12, 16, 46, 145};
	int p[] = {156, 143, 112, 90, 127, 55, 21};
	int Total_Profit[7] = {0};
	int k = 6;
	int max_profit = 0;

    //-------------------------------------------------------------------
    for(int i = 0; i < 7; i++) {

        for (int j = 0; j < i && location[i] - location[j] >= k; j++) {
        	if (Total_Profit[j] > max_profit) {
        		max_profit = Total_Profit[j];
        	}
        }

        Total_Profit[i] = max_profit + p[i];
    }
    //-------------------------------------------------------------------
    
    for(int i = 0; i < 7; i++) {
    	cout << Total_Profit[i] << endl;
    }
    
    for(int i = 0;i < 7; i++) {
    	if(max_profit < Total_Profit[i]) {
    		max_profit = Total_Profit[i];
    	}
    }
        
    cout << endl;
    cout << "Total_Profit is " << max_profit << endl;
}