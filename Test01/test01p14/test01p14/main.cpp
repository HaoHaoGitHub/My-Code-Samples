
//  main.cpp
//  test01p14
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

int main() {
    std::ifstream istr("/Users/HaoChen/Desktop/DS_test/test1/P9/little_engine_that_could.txt");
    std::string word;
    int num_chars = 0;
    int num_words = 0;
    int num_sentences = 0;
    while (istr >> word) {
        num_words ++;
        num_chars += word.size();
        // Find the end of a sentence:
        if (word[word.size()-1] == '.' || word[word.size()-1] == '!' || word[word.size()-1] == '?') {
            num_sentences ++;
            num_chars -= 1;
        std::cout << "sentence " << std::setw(3) << num_sentences << "  #words: " << std::setw(3) << num_words << "   avg chars/words:" << std::fixed << std::setprecision(1) << std::setw(5)
        << num_chars / double (num_words) << std::endl;
        // reset the counters:
        num_chars = 0;
        num_words = 0;
        }
   }
    return 0;
}
