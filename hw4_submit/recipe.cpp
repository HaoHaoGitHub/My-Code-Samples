//
//  recipe.cpp
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#include "recipe.h"

// CONSTRUCTOR
Recipe::Recipe(const string& Name1){
    Name_ = Name1;
}

void Recipe::addIngredient(const string&Name2, int units){
    Ingredient ing(Name2,units);
    Ingredients_one.push_back(ing);
}


void Recipe::print_onerecipe (ostream &ostr) const {
    ostr << "To make " << get_recipename() << ", " << "mix together:" << endl;
    // Check whether the size of the list is bigger than 0
    assert(Ingredients_one.size() > 0);
    
    // First sort them alphabetically, then print each of them out:
    // I first make a copy, then use the copy to sort:
    list<Ingredient> copy_Ingredients_one(Ingredients_one);
    copy_Ingredients_one.sort(lessname);
    list<Ingredient>::iterator i = copy_Ingredients_one.begin();
    while (i != copy_Ingredients_one.end()) {
        if (i->getIngredient_unit() > 1) {
            ostr << "  " << i->getIngredient_unit() << " " << "units of " << i->getIngredient_name() << endl;
        } else {
            ostr << "  " << i->getIngredient_unit() << " " << "unit of " << i->getIngredient_name() << endl;
        }
        i++;
    }
}
