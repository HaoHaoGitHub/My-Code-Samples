//
//  main.cpp
//  test01p5
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> compound_detector(const std::vector<std::string> &words) {
    std::vector<std::string> answer;
    // loop over each word, testing to see if it is a compound word
    for (int w = 0; w < words.size(); w++) {
        bool found = false;
        for (int x = 0; !found && x < words.size(); x++) {
            for (int y = 0; !found && y < words.size(); y++) {
                // 2 word combinations
                if (words[w] == words[x]+words[y]) {
                    answer.push_back(words[w]);
                    found = true;
                }
                for (int z = 0; !found && z < words.size(); z++) {
                    // 3 word combinations
                    if (words[w] == words[x]+words[y]+words[z]) {
                        answer.push_back(words[w]);
                        found = true;
                    }
                } }
        } }
    return answer;
}

int main() {
    std::vector<std::string> matrix = {"a","back","backlog","backwoods","backwoodsman","cat","catalog" "less","log","man","none","nonetheless","ship","the","woods","woodsman"};
    std::vector<std::string> answer;
    answer = compound_detector(matrix);
    
    for (unsigned int i = 0; i < answer.size(); i++) {
        for (unsigned int j = 0; j < answer[i].size(); j++) {
            std::cout << matrix[i][j];
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    
    
    
    
    
    
    
    
    return 0;
}

