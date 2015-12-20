//
//  OlympicsTeam.h
//  test01p9
//
//  Created by 陈昊 on 2/21/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#ifndef __test01p9__OlympicsTeam__
#define __test01p9__OlympicsTeam__

#include <stdio.h>
#include <vector>
#include <string>

class OlympicTeam{
    
public:
    // Constructors
//    OlympicTeam();
//    OlympicTeam(const std::string &Name, int num_of_gold, int num_of_silver, int num_of_bronze);
    
    
    // Member functions:
    void addAthlete(const std::string &Name);
    void addMedal(const std::string &Name, const std::string &medalstyle);
    const int numAthletes() const;
    const double averageMedalsPerAthlete() const;
    bool hasWonGoldMedal(const std::string &Name) const;
    
    
private:
    std::vector<std::string> Winter_2014;
    std::vector<std::string> goldname;
    std::vector<std::string> silvername;
    std::vector<std::string> bronzename;
    std::string Name_;
    std::string medalstype_;
    int num_of_gold_;
    int num_of_silver_;
    int num_of_bronze_;
};



#endif /* defined(__test01p9__OlympicsTeam__) */
