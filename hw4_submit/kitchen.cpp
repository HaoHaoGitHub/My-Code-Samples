//
//  kitchen.cpp
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#include "kitchen.h"

void Kitchen::addIngredient(string& Name, int units, int &count){
    list<Ingredient>::iterator i = Ingredients.begin();
     // Check to see if the Ingredient is already in the list:
    bool found = false;
    while (!found && i != Ingredients.end()) {
        found = i->getIngredient_name() == Name;
        if (!found) {
            i++;
        } else {
            // If found == true, then.........
            units += i->getIngredient_unit();
            i->setIngredient_unit(units); // add appripriate amount to this ingredient
            // In this situation, we also need to add the count(number of distinct ingredients added):
            count++;
        }
    }
    if (!found) {
        // If the ingredient is not in the list, add it to the list "Ingredients":
        Ingredient ing1(Name,units);
        Ingredients.push_back(ing1);
        count++;
    }
}

void Kitchen::changeIng_unit(const string& Name, int unit){
    list<Ingredient>::iterator i;
    for (i = Ingredients.begin() ; i != Ingredients.end(); i++) {
        if (i->getIngredient_name() == Name) {
            i->setIngredient_unit(unit);
        }
    }
}


void Kitchen::printIngredients(ostream& ostr){
    // Remove from the list of Ingredients if a particlular ingredient has been "used up"
    list<Ingredient>::iterator k = Ingredients.begin();
    while(k != Ingredients.end()) {
        if (k->getIngredient_unit() == 0) {
        //-------------------------------------------------------------------------------
            k = Ingredients.erase(k);
        //-------------------------------------------------------------------------------
        } else {
            k++;
        }
    }
    // Sort them first then print (sorted by quantity first, and then alphabetically for
    // items with equal quantity:
    list<Ingredient> copy_Ingredients(Ingredients);
    copy_Ingredients.sort(lessname_quantity);
    list<Ingredient>::iterator i;
    ostr << "In the kitchen:" << endl;
    for (i = copy_Ingredients.begin(); i != copy_Ingredients.end(); i++) {
        if (i->getIngredient_unit() > 1) {
            ostr << "  " << i->getIngredient_unit()<< " " << "units of " << i->getIngredient_name() << endl;
        } else {
            ostr << "  " << i->getIngredient_unit() << " " << "unit of " << i->getIngredient_name() << endl;
        }
    }

}


