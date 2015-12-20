//
//  ingredient.cpp
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#include "ingredient.h"

Ingredient::Ingredient(const string& Name, int unit){
    Name_ = Name;
    unit_ = unit;
}

void Ingredient::setIngredient_name(const string& name){
    Name_ = name;
}

void Ingredient::setIngredient_unit(int unit){
    unit_ = unit;
}


bool lessname(Ingredient& I1, Ingredient& I2){
    return I1.getIngredient_name() < I2.getIngredient_name();
}


bool lessname_quantity(Ingredient& I1, Ingredient& I2){
    return (I1.getIngredient_unit() < I2.getIngredient_unit()) ||
    ((I1.getIngredient_unit() == I2.getIngredient_unit()) && (I1.getIngredient_name() < I2.getIngredient_name()));
}