//
//  OlympicsTeam.cpp
//  test01p9
//
//  Created by 陈昊 on 2/21/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include "OlympicsTeam.h"
#include <iostream>
#include <string>
#include <vector>

void OlympicTeam::addAthlete(const std::string &Name){
    int indicator = 0;
    for (unsigned int i = 0; i < Winter_2014.size(); i++) {
        if ( Name == Winter_2014[i])
            indicator++;
    }
    if (indicator != 0)
      std::cerr << "can not add duplicate athlete " << Name << std::endl;
     else
         Winter_2014.push_back(Name);

}

void OlympicTeam::addMedal(const std::string &Name, const std::string &medalstyle){
    int indicator = 0;
    for (unsigned int i = 0; i < Winter_2014.size(); i++) {
        if (Winter_2014[i] == Name)
            indicator ++;
    }
    if (indicator == 0)
        std::cerr << "athelete " << Name << " is not a member of this team" << std::endl;
        
    else if (medalstyle == "gold") {
         goldname.push_back(Name);
    }
    else if (medalstyle == "silver"){
         silvername.push_back(Name);
    }
    else if (medalstyle == "bronze"){
         silvername.push_back(Name);
    }
    else
         std::cerr << "unknown medal color " << medalstyle << std:: endl;
    
}

const int OlympicTeam::numAthletes() const{
    return Winter_2014.size();
}

bool OlympicTeam::hasWonGoldMedal(const std::string &Name) const{
    for (unsigned int i = 0; i < goldname.size(); i++) {
        if (Name==goldname[i])
            return true;
    }
            return false;
}

const double OlympicTeam::averageMedalsPerAthlete() const{
    double sum = goldname.size() + silvername.size() + bronzename.size() ;
    double result = sum / (Winter_2014.size());
    return result;
}











