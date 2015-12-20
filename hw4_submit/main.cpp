// Name: Hao Chen  RIN: 661412823

//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
//
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "recipe.h"
#include "kitchen.h"


// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);
void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen);


// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {
    // Check the number of arguments.
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
        return 1;
    }
    // Open and test the input file.
    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }
    // Open and test the output file.
    std::ofstream ostr(argv[2]);
    if (!ostr) {
        std::cerr << "Could not open " << argv[2] << " to write\n";
        return 1;
    }
    
    // the kitchen & recipe list
    Kitchen kitchen;
    std::list<Recipe> recipes;
    
    // some variables to help with parsing
    char c;
    while (istr >> c) {
        if (c == 'r') {
            // READ A NEW RECIPE
            readRecipe(istr,ostr,recipes);
            
        } else if (c == 'a') {
            // ADD INGREDIENTS TO THE KITCHEN
            addIngredients(istr,ostr,kitchen);
            
        } else if (c == 'p') {
            // PRINT A PARTICULAR RECIPE
            printRecipe(istr,ostr,recipes);
            
        } else if (c == 'm') {
            // MAKE SOME FOOD
            makeRecipe(istr,ostr,recipes,kitchen);
            
        } else if (c == 'k') {
            // PRINT THE CONTENTS OF THE KITCHEN
            kitchen.printIngredients(ostr);
            
        } else if (c == 's') {
            // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE
            //   CURRENT CONTENTS OF THE KITCHEN
            recipeSuggestions(ostr,recipes,kitchen);
            
        } else if (c == 'd') {
            // EXTRA CREDIT: SUGGEST THE COLLECTION OF RECIPES THAT CAN BE
            // MADE TOGETHER THAT USE THE MAXIMUM NUMBER OF UNITS OF
            // INGREDIENTS
        } else {
            std::cerr << "unknown character: " << c << std::endl;
            exit(0);
        }
    }
}



//------------------------------------------------------------------------------------------------------------
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
    int units;
    std::string name, name2;
    istr >> name; // Name of recipe
    // Part I
    //-----------------------------------------------------------------------------------------
    // Verify that there is not already a recipe with this name in the list of recipes
    bool found = false;
    for (list<Recipe>::iterator i = recipes.begin(); i != recipes.end() && !found;i++) {
        if (i->get_recipename() == name) {
            ostr << "Recipe for " << name << " already exists" << endl;
            found = true;
        }
    }
    // Part II
    //-----------------------------------------------------------------------------------------
    if (!found) {
        Recipe r(name);
        while (!found) {
            istr >> units;
            if (units == 0) break;
            assert (units > 0);
            istr >> name2;
            r.addIngredient(name2,units);
            
        }
        // build the new recipe and add it to the list
        recipes.push_back(r);
        ostr << "Recipe for " << name << " added" << std::endl;
    } else {
        // Notes: even though the recipe is already exists, we still need to read through them:
        while (found) {
            istr >> units;
            if (units == 0) break;
            istr >> name2;
        }
        
    }
}



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
    int units;
    std::string name;
    int count = 0;
    while (1) {
        istr >> units;
        if (units == 0) break;//
        assert (units > 0);
        istr >> name;
        // add the ingredients to the kitchen.
        // Here I make the count variable pass by reference so that I can access it outside:
        kitchen.addIngredient(name,units,count);
    }
    if (count == 1) {
        ostr << count << " ingredient added to kitchen" << std::endl;
    } else {
        ostr << count << " ingredients added to kitchen" << std::endl;
    }
}


//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes) {
    std::string name;
    istr >> name;
    // Verify that there is not already a recipe with this name in the list of recipes
    bool found = false;
    list<Recipe>::const_iterator i = recipes.begin();
    while (!found && i != recipes.end()) {
        found = i->get_recipename() == name;
        if (!found) {
          i++;
        } else {
            // sort by alphabetical of ingredients in a recipe first, then print the result
            i->print_onerecipe(ostr);
        }
    }
    if (!found) {
        ostr << "No recipe for " << name << endl;
    }
}


//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
    std::string name;
    istr >> name;
    // Verify that there is not already a recipe with this name in the list of recipes
    bool found = false;
    list<Recipe>::const_iterator i = recipes.begin();
    while (!found && i != recipes.end()) {
        found = i->get_recipename() == name;
        if (!found) {
           i++;
        } else {
            // If ingredients are sufficient, remove appropriate amounts
            //-----------------------------------------------------------------------------------------
            list<Ingredient> RecipeIngredients = i->get_IngredientsOne();
            list<Ingredient> currentIngredients = kitchen.get_Ingredients();
            list<Ingredient> Ingredient_Needed;
            list<int> finalunit;
            list<string> finalname;
            list<Ingredient>::iterator itr1;
            list<Ingredient>::iterator itr2;
            
            // Part I
            //-----------------------------------------------------------------------------------------
            int count = 0;
            list<string> Name_exist;
            for (itr1 = RecipeIngredients.begin(); itr1 != RecipeIngredients.end(); itr1++) {
                for (itr2 = currentIngredients.begin(); itr2 != currentIngredients.end(); itr2++) {
                    if (itr1->getIngredient_name() == itr2->getIngredient_name()) {
                        Name_exist.push_back(itr1->getIngredient_name());
                        // If ingredients are sufficient, remove appropriate amounts
                        if (itr1->getIngredient_unit() <= itr2->getIngredient_unit()) {
                            count ++;
                            int unit = itr2->getIngredient_unit();
                            unit -= itr1->getIngredient_unit();
                            // Put the unit needed to change inside a list and make a change later:
                            finalunit.push_back(unit);
                            finalname.push_back(itr1->getIngredient_name());
                        } else {
                        // If insufficient: print what and how much need to buy and list them in order:
                            int unit_needed = (itr1->getIngredient_unit()) - (itr2->getIngredient_unit());
                            Ingredient ing2(itr1->getIngredient_name(), unit_needed);
                            Ingredient_Needed.push_back(ing2);
                        }
                    }
                }
            }
            // Part II
            //-----------------------------------------------------------------------------------------
            if (count == RecipeIngredients.size()) {
                //If ingredients are sufficient, remove appropriate amounts. Then print "made name":
                // Note: There is a loop inside!!!!
                list<int>::iterator n = finalunit.begin();
                list<string>::iterator m = finalname.begin();
                while (n != finalunit.end()) {
                    kitchen.changeIng_unit(*m, *n);
                    n++;
                    m++;
                }
                ostr << "Made " << i->get_recipename() << endl;
            }
            
            
            // Part III
            //-----------------------------------------------------------------------------------------------
            // Check whether there are Ingredients that exist in the recipe, but doesn't exist in the kitchen:
            list<string>::iterator q;
            // earse the Ingredients of Name_exist from Ingredients of Recipe, then the Ingredients left in the
            // Recipe is those that exist in the recipe, but doesn't exist in the kitchen
            itr1 = RecipeIngredients.begin();
            bool found = false;
            while (itr1 != RecipeIngredients.end()) {
                for (q = Name_exist.begin(); q != Name_exist.end(); q++) {
                    if (itr1->getIngredient_name() == *q) {
                        itr1 = RecipeIngredients.erase(itr1);
                        found = true;
                    }
                }
                if (!found) {
                    itr1++;
                } else {
                    found = false;
                }
            }
            // Now the list RecipeIngredients has been changed:
            // Add those Ingredients that exist in the recipe, but doesn't exist in the kitchen to the
            // list of Ingredient_Needed
            for (list<Ingredient>::iterator t = RecipeIngredients.begin(); t != RecipeIngredients.end(); t++) {
                Ingredient ing3(t->getIngredient_name(), t->getIngredient_unit());
                Ingredient_Needed.push_back(ing3);
            }
            
            // Part IV
            //----------------------------------------------------------------------------------------------
            if (Ingredient_Needed.size() != 0) {
                ostr << "Cannot make " << i->get_recipename() << ", " << "need to buy:\n";
            }
            // print out "ingredients needed" alphabetically:
            Ingredient_Needed.sort(lessname);
            list<Ingredient>::iterator k = Ingredient_Needed.begin();
            
            while (k != Ingredient_Needed.end()) {
                // Distinguishes between singular and plural quantities:
                if (k->getIngredient_unit() > 1) {
                    ostr << "  " << k->getIngredient_unit() << " " << "units of " << k->getIngredient_name() << endl;
                } else {
                    ostr << "  " << k->getIngredient_unit() << " " << "unit of " << k->getIngredient_name() << endl;
                }
                k++;
            }
            //-----------------------------------------------------------------------------------------
        }
        
    }
    // If the program does not have the requested recipe, print:
    if (!found) {
        ostr << "Don't know how to make " << name << endl;
    }
}



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen) {
    list<string> prepared_recipe;
    list<Recipe>::const_iterator i = recipes.begin();
    // Part I
    //----------------------------------------------------------------------------------------------
    while (i != recipes.end()) {
        list<Ingredient> RecipeIngredients = i->get_IngredientsOne();
        list<Ingredient> currentIngredients = kitchen.get_Ingredients();
        list<Ingredient>::iterator itr1;
        list<Ingredient>::iterator itr2;
        int count = 0;
        for (itr1 = RecipeIngredients.begin(); itr1 != RecipeIngredients.end(); itr1++) {
            for (itr2 = currentIngredients.begin(); itr2 != currentIngredients.end(); itr2++) {
                if (itr1->getIngredient_name() == itr2->getIngredient_name()) {
                    //--------------------------------------------------------------------------------
                    // If ingredients are sufficient
                    if (itr1->getIngredient_unit() <= itr2->getIngredient_unit()) {
                        count ++;
                    }
                }
            }
        }
        
        if (count == RecipeIngredients.size()) {
            prepared_recipe.push_back(i->get_recipename());
        }
        i ++;
    }
    
    // Part II
    //----------------------------------------------------------------------------------------------
    if (prepared_recipe.size() == 0) {
        ostr << "No recipes can be prepared" << endl;
    } else {
       prepared_recipe.sort();
       unsigned int count = prepared_recipe.size();
        if (count == 1) {
            ostr << "Recipe that can be prepared:\n";
        } else {
            ostr << "Recipes that can be prepared:\n";
        }
       list<string>::iterator itr = prepared_recipe.begin();
       while (itr != prepared_recipe.end()) {
           ostr << "  " << *itr << endl;
           itr ++;
       }
    }
}
//------------------------------------------------------------------------------------------------------------























