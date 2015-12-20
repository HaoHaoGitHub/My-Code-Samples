//
//  main.cpp
//  test01p9
//
//  Created by 陈昊 on 2/21/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include "OlympicsTeam.h"

int main(int argc, const char * argv[]) {
    OlympicTeam US_Winter_2014;
    US_Winter_2014.addAthlete("Sage_Kotsenburg");
    US_Winter_2014.addAthlete("Hannah_Kearney");
    US_Winter_2014.addAthlete("Gracie_Gold");
    US_Winter_2014.addAthlete("Lindsey_Van");
    US_Winter_2014.addAthlete("Shani_Davis");
    US_Winter_2014.addMedal("Sage_Kotsenburg","gold");
    US_Winter_2014.addMedal("Hannah_Kearney","bronze");
    US_Winter_2014.addAthlete("Gracie_Gold");
    US_Winter_2014.addMedal("Michael_Phelps","gold");
    US_Winter_2014.addMedal("Lindsey_Van","pewter");
    std::cout << "The US Winter Olympics team has " << US_Winter_2014.numAthletes()
    << " athletes and has won on average " << US_Winter_2014.averageMedalsPerAthlete()
    << " medals per athlete." << std::endl;
    if (US_Winter_2014.hasWonGoldMedal("Sage_Kotsenburg")) {
        std::cout << "Sage_Kotsenburg has won a gold medal." << std::endl;
    } else {
        std::cout << "Sage_Kotsenburg has not (yet) won a gold medal." << std::endl;
    }
    if (US_Winter_2014.hasWonGoldMedal("Lindsey_Van")) {
        std::cout << "Lindsey_Van has won a gold medal." << std::endl;
    } else {
        std::cout << "Lindsey_Van has not (yet) won a gold medal." << std::endl;
    }
    
    
    return 0;
}
