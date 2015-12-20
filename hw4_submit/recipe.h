//
//  recipe.h
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#ifndef __HW04__recipe__
#define __HW04__recipe__

#include <stdio.h>
#include <list>
#include <assert.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "ingredient.h"


using namespace std;


class Recipe {
public:
    // CONSTRUCTOR:
    Recipe(const string& Name1);
    
    // MEMBER FUNCTION:
    const string& get_recipename () const { return Name_;}
    const list<Ingredient>& get_IngredientsOne() const { return Ingredients_one;}
    void addIngredient(const string&Name2, int units);
    void print_onerecipe (ostream &ostr) const;
    
private:
    string Name_;
    list<Ingredient> Ingredients_one; // This includes the name and amount of each Ingredient of one recipe
};

#endif /* defined(__HW04__recipe__) */
