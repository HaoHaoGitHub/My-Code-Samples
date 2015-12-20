//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

std::vector<std::vector<std::string>> city;
void find_location (const std::vector<std::vector<std::string>> &city, const std::string &store, int &x, int &y);
void give_directions(const std::vector<std::vector<std::string>> &city, const std::string &starting, const std::string &ending);

int main(int argc, const char * argv[]) {
    std::ifstream in_str("/Users/HaoChen/Desktop/DS_test/test1/P2/input.txt");
    std::vector<std::string> line1;
    std::string store1;
    for (unsigned int i = 0; i < 4; i++ ) {
        in_str >> store1;
        line1.push_back(store1);
    }
    city.push_back(line1);
    for (unsigned int i = 0; i < 5; i++) {
        std::vector<std::string> line;
        for (unsigned int i = 0; i < 5; i++) {
            std::string store;
            in_str >> store;
            line.push_back(store);
        }
        city.push_back(line);
    }
    
    for (unsigned int i = 0; i < city.size();i++ ) {
        for (unsigned int j = 0; j < city[i].size(); j++) {
            for (unsigned int k = 0; k < city[i][j].size(); k++) {
                std::cout << city[i][j][k];
            }
            std::cout << "  ";
        }
        std::cout << std::endl;
    }


    give_directions(city, "gap", "cvs");
    
    
    return 0;
}

void find_location(const std::vector<std::vector<std::string>> &city, const std::string &store, int &x, int &y){
    for (unsigned int i = 0; i < city.size(); i++) {
        for (unsigned int j = 0; j < city[i].size(); j++) {
                if (city[i][j] == store) {
                    x = i;
                    y = j;
           }
        }
    }
}

void give_directions(const std::vector<std::vector<std::string>> &city, const std::string &starting, const std::string &ending){
    int startingx, startingy, endingx, endingy;
    find_location(city, starting, startingx, startingy);
    find_location(city, ending, endingx, endingy);
    // There are four situations:

    if ((startingx < endingx) && (startingy < endingy)) {
        // column ways
        for (unsigned int i = startingx; i < endingx; i++) {
            std::cout << " Walk from " << " " << city[i][startingy] << " " << "to" << " " << city[i+1][startingy];
            std::cout << std::endl;
        }
        // row ways
        for (unsigned int i = startingy; i < endingy ; i++) {
            std::cout << " Walk from " << " " << city[endingx][i] << " " << "to" << " " << city[endingx][i+1];
            std::cout << std::endl;
        }
    }
    if ((startingx < endingx) && (startingy > endingy)) {
        // column ways
        for (unsigned int i = startingx; i < endingx; i++) {
            std::cout << " Walk from " << " " << city[i][startingy] << " " << "to" << " " << city[i+1][startingy];
            std::cout << std::endl;
        }
        // row ways
        for (unsigned int i = startingy; i > endingy ; i--) {
            std::cout << " Walk from " << " " << city[endingx][i] << " " << "to" << " " << city[endingx][i-1];
            std::cout << std::endl;
        }
    }
    //********************************************************************************
    if ((startingx > endingx) && (startingy < endingy)) {
        // column ways
        for (unsigned int i = startingx; i < endingx; i++) {
            std::cout << " Walk from " << " " << city[i][startingy] << " " << "to" << " " << city[i+1][startingy];
            std::cout << std::endl;
        }
        // row ways
        for (unsigned int i = startingy; i > endingy ; i--) {
            std::cout << " Walk from " << " " << city[endingx][i] << " " << "to" << " " << city[endingx][i-1];
            std::cout << std::endl;
        }
    }
    if ((startingx > endingx) && (startingy < endingy)) {
        // column ways
        for (unsigned int i = startingx; i < endingx; i++) {
            std::cout << " Walk from " << " " << city[i][startingy] << " " << "to" << " " << city[i+1][startingy];
            std::cout << std::endl;
        }
        // row ways
        for (unsigned int i = startingy; i > endingy ; i--) {
            std::cout << " Walk from " << " " << city[endingx][i] << " " << "to" << " " << city[endingx][i-1];
            std::cout << std::endl;
        }
    }


    if ((startingx > endingx) && (startingy < endingy)) {
        // column ways
        for (unsigned int i = startingx; i < endingx; i++) {
            std::cout << " Walk from " << " " << city[i][startingy] << " " << "to" << " " << city[i+1][startingy];
            std::cout << std::endl;
        }
        // row ways
        for (unsigned int i = startingy; i > endingy ; i--) {
            std::cout << " Walk from " << " " << city[endingx][i] << " " << "to" << " " << city[endingx][i-1];
            std::cout << std::endl;
        }
    }

    
    
    
    
    
}














