//
//  kitchen.h
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#ifndef __HW04__kitchen__
#define __HW04__kitchen__

#include <stdio.h>
#include <list>
#include <assert.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream> 
#include "ingredient.h"

using namespace std;

class Kitchen {
public:
   // Member Functions:
    const string& get_ingredient_name () const { return Name_;}
    const list<Ingredient>& get_Ingredients() const { return Ingredients;}
    void addIngredient(string& Name, int units, int &count);
    void printIngredients(ostream& ostr);
    void changeIng_unit(const string& Name, int unit);
    
private:
    string Name_;
    list<Ingredient> Ingredients;
};

#endif /* defined(__HW04__kitchen__) */
