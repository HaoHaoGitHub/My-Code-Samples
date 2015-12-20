// P6

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<std::string> vowels;

bool less_vowel(const std::string &vol1, const std::string &vol2);
void compute();



int main() {
    std::string temp;
    std::ifstream in_str("/Users/HaoChen/Desktop/DS_test/test1/P1/input.txt");
    while (in_str >> temp)){
        vowels.push_back(temp);
    }
    compute();
    sort(vowels.begin(),vowels.end(), less_vowel);
        for (unsigned int i = 0; i < vowels.size(); i++) {
            for (unsigned int j = 0; j < vowels[i].size()-1; j++) {
                std::cout << vowels[i][j];
            }
            std::cout << "   ";
        }
        std::cout << std::endl;
    
    return 0;

}



void compute(){
    for (unsigned int i = 0; i < vowels.size();i++){
        unsigned int count = 0;
        for (unsigned int j = 0; j < vowels[i].size(); j++){
            char character = vowels[i][j];
            if ((character == 'a') || (character == 'e') || (character == 'i') || (character == 'o') ||
                (character == 'u'))
                count ++;
        }
        vowels[i] += std::to_string(count);
    }
}

bool less_vowel(const std::string &vol1, const std::string &vol2){
    char temp1 = vol1[vol1.size() - 1];
    char temp2 = vol2[vol2.size() - 1];
    if ((temp1 == temp2 && vol1[0] < vol2[0]) || temp1 < temp2 )
       return true;
    else
       return false;
}
