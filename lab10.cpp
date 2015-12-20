#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main (int argc, char* argv[]) {
	
	int matrix[128][128];	// the distance between each nodes, obtained from input file
	bool visited[128];		// false if a node is not visited, true if visited

	std::vector< std::vector<int> > paths;	// the optimal paths that the salesman has taken each time
	std::vector<int> Total_distances;// the total length of the path

    int Num = 42;

    std::ifstream in_str(argv[1]);
    
    while (in_str >> n) { temp.push_back(n);}
    int Num = temp.size();
    for (int i = 0; i < Num; ++i) {
    	for (int j = 0; j < Num; ++j) {
    		in_str >> matrix[i][j];
    	}
    }

    // for (int i = 0; i < msize; ++i) {
    // 	for (int j = 0; j < msize; ++j) {
    // 		cout << matrix[i][j] << " ";
    // 	}
    // 	cout << endl;
    // }

	// All data has been processed
	for (int i = 0; i < Num; ++i) // i will be the starting node in each case
	{
		std::vector<int> path;	// Record the optimal path
		int Total_distance = 0;			
		int edge;

		int node = i;	// initialize node
		int next_node;

		for ( int j = 0; j < 128; ++j ) visited[j] = false;	// initialize visited status

		path.push_back(i); 	// path start with the starting node
		visited[i] = true;

		for ( int h = 0; h < Num-1; ++h ) {
			edge = INT_MAX;
			for ( int j = 0; j < Num; ++j ) {
				// find the next node greedily
				if (visited[j] == true) continue; 

				if ( matrix[node][j] < edge ) {
					edge = matrix[node][j]; 
					next_node = j;
				}
			}
			path.push_back(next_node);
			Total_distance += edge;
			node = next_node;
			visited[node] = true;
		}
        // add the length of path from last node back to start node
		Total_distance += matrix[i][next_node]; 

		paths.push_back(path);
		Total_distances.push_back(Total_distance);
	}

	for ( int i = 0; i < Num; ++i ) {
		std::cout<<"Start at " << i << " cost " << Total_distances[i];
		// std::cout<<" with best path: ";
		// for ( int j = 0; j < Num; ++j ) {
		//   std::cout<< paths[i][j ]<< " ";
		// }
		std::cout<<std::endl;
	}

	return 0;
}

