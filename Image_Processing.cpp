// Name:Hao Chen RIN:661412823
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// Function prototype
void replace(vector< string > matrix, vector<string> &newmatrix, char color, char replacecolor);
void dilation(vector< string > matrix, vector<string> &newmatrix, char color);
void erosion(vector< string> matrix, vector<string> &newmatrix, char color, char background);
void floodfill(vector<string> &newmatrix, int r, int c, int row, int col, char replacecolor, char aim_color);

// The main function:
//*******************************************************************************************************************************
int main(int argc, char* argv[]){
    
    ifstream in_str(argv[1]);
    
    if (!in_str.good()) {
        std::cerr << "Can't open the grades file" << endl;
        return 1;
    }
    if (!in_str.is_open()){
        cout << "Not successfully opened" << endl;
    }
    
    vector<string> matrix;
    vector<string> newmatrix;

    // Input the data
    string line;
    while (in_str >> line) matrix.push_back(line);

    newmatrix = matrix;
    
    // arguments
   
    string operation = argv[3];
    if (operation == "replace"){
        char color = *argv[4];
        char replacecolor = *argv[5];
        replace(matrix, newmatrix, color, replacecolor);
    }
    else if (operation == "dilation"){
        char color = *argv[4];
        dilation(matrix, newmatrix, color);
    }
    else if (operation == "erosion"){
        char color = *argv[4];
        char background = *argv[5];
        erosion(matrix, newmatrix, color, background);
    }
    else if (operation == "floodfill"){
        char* char_sr = argv[4];
        char* char_sc = argv[5];
        char replacecolor = *argv[6];
        int row = matrix.size();
        int col = matrix[0].size();

        // Convert C-style char array to an int:
        int sr = atof(char_sr);
        int sc = atof(char_sc);
        // Check out-of-bounds:
        if (sr < 0 || sr > row || sc < 0 || sc > col) {
            cerr <<  "Beyond Boundary, try another row and column! " << endl;
        } else {
            char aim_color = matrix[sr][sc];
            floodfill(newmatrix, sr, sc, row, col, replacecolor, aim_color);
        }
    }

    ofstream out_str(argv[2]);
    //create a file
    int row = matrix.size();
    for (int i = 0; i < row; ++i) {
        out_str << newmatrix[i] << endl;
    }
    out_str.close();
    
    return 0;
}

//****************************************************************************************************************************
// 1. Replacement:
void replace(vector< string > matrix, vector<string> &newmatrix, char color, char replacecolor){
    unsigned int row = matrix.size();
    unsigned int col = matrix[0].size();
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == color) {
                newmatrix[i][j] = replacecolor;
            }
        }
    }
}

// 2. dilation. Here we use " plus-shaped structuring element " to make adjustment
//*****************************************************************************************************************************
void dilation(vector< string > matrix, vector<string> &newmatrix, char color) {
    unsigned int row = matrix.size();
    unsigned int col = matrix[0].size();
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++) {
            if (matrix[i-1][j] == color || matrix[i][j-1] == color || matrix[i+1][j] == color|| matrix[i][j+1] == color ) {
                newmatrix[i][j] = color;
            }
        }
    }
}

// 3. erosion.
//*****************************************************************************************************************************
void erosion(vector< string > matrix, vector<string> &newmatrix, char color, char background) {
    unsigned int row = matrix.size();
    unsigned int col = matrix[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            newmatrix[i][j] = background;
        }
    }
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++) {
            if (matrix[i-1][j] == color && matrix[i][j-1] == color && matrix[i+1][j] == color && matrix[i][j+1] == color ) {
                newmatrix[i][j] = color;
            }
        }
    }
}

// 4. floodfill (Recursion)
//******************************************************************************************************************************
void floodfill(vector<string> &newmatrix, int r, int c, int row, int col, char replacecolor, char aim_color ) {
    // Print out the route
    cout << r << " " << c << endl;
    // Base cases 
    if (r < 0|| r > row || c < 0 || c > col) return;
    if (newmatrix[r][c] != aim_color) return;
    // Replace the color at (r,c)
    newmatrix[r][c] = replacecolor;
    // Recur for north, east, south, and west
    floodfill(newmatrix, r+1, c, row, col, replacecolor, aim_color);
    floodfill(newmatrix, r-1, c, row,col, replacecolor, aim_color);
    floodfill(newmatrix, r, c+1, row, col, replacecolor, aim_color);
    floodfill(newmatrix, r, c-1, row, col, replacecolor, aim_color);
}
//******************************************************************************************************************************





    






    
  
