//
//  ingredient.h
//  HW04
//
//  Created by Hao Chen on 2/28/15.
//  Copyright (c) 2015 Hao Chen. All rights reserved.
//

#ifndef __HW04__ingredient__
#define __HW04__ingredient__

#include <stdio.h>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Ingredient {
    
public:
    // Constructors
    Ingredient(const string& Name, int unit);
    
    // Accessors
    const string& getIngredient_name() const { return Name_;}
    const int getIngredient_unit() const { return unit_; }
    
    // Modifiers
    void setIngredient_name(const string& name); // 这里面的参数要加const 和 & 吗？？ 待确认！
    void setIngredient_unit(int unit);
    
private:
    string Name_;
    int unit_;
};

bool lessname(Ingredient& I1, Ingredient& I2);
bool lessname_quantity(Ingredient& I1, Ingredient& I2);
#endif /* defined(__HW04__ingredient__) */
