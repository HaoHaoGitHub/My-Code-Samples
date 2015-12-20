// Name: Hao Chen RIN: 661412823
#include <iostream>
#include <vector>


int replace_in_matrix(std::vector<std::vector<int>> &matrix, int old_value, int new_value);

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> matrix;
    unsigned int i;
    unsigned int j;
    unsigned int row = 3;
    unsigned int column = 5;
    matrix.resize(row);
    for (i = 0; i < matrix.size(); i++) {
        matrix[i].resize(column);
    }
    for (i = 0; i < matrix.size(); i++) {
        for (j = 0; j< matrix[i].size(); j++) {
            std::cout << "Please enter values: ";
            std::cin >> matrix[i][j];
        }
    }
    
    int result = replace_in_matrix(matrix, 3 , 9);
    std::cout << result << std::endl;
    
    // Print out the result to see whether it is right;
    for (i = 0; i < matrix.size(); i++) {
        for (j = 0; j< matrix[i].size(); j++) {
            std::cout <<  matrix[i][j];
        }
        std::cout << std::endl;
    }
    
    return 0;
}

int replace_in_matrix(std::vector<std::vector<int>> &matrix, int old_value, int new_value){
    unsigned int i;
    unsigned int j;
    unsigned int count = 0;
    for (i = 0; i < matrix.size(); i++) {
        for (j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == old_value) {
                matrix[i][j] = new_value;
                count ++;
            }
        }
        
    }
    return count;
    
}
