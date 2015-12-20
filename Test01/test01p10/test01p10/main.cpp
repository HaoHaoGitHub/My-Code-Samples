// Name: Hao Chen   RIN: 661412823

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool lesslength_reversealpha(const std::string &aword1, const std::string &aword2);

int main() {
    std::vector<std::string> words;
    words = {"dog", "snake", "cat", "ferret", "gorilla", "bird", "jaguar"};
    sort(words.begin(), words.end());
    for (unsigned int i = 0; i < words.size(); i++) {
        for (unsigned int j = 0; j < words[i].size(); j++) {
            std::cout << words[i][j];
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    sort(words.begin(), words.end(), lesslength_reversealpha);
    for (unsigned int i = 0; i < words.size(); i++) {
        for (unsigned int j = 0; j < words[i].size(); j++) {
            std::cout << words[i][j];
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

bool lesslength_reversealpha(const std::string &aword1, const std::string &aword2){
    if ((aword1.size() < aword2.size()) || ((aword1.size() == aword2.size()) && aword1 > aword2))
        return  true;
    else
        return false;
}