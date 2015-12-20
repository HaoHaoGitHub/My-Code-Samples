// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <typeinfo>

#include "traincar.h"

using namespace std;
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

void PushBack(TrainCar* &simple, TrainCar* car){
    if (simple == NULL) {
        simple = car;
    } else  {
        TrainCar *tmp = simple;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = car;
        car->prev = tmp;
    }
}

void DeleteAllCars(TrainCar* &head){
    if (head == NULL) {
        return;
    } else {
        TrainCar* car = head->next;
        delete head;
        DeleteAllCars(car);
    }
}


void TotalWeightAndCountCars(TrainCar* t, int &total_weight,int &num_engines, int &num_freight_cars,
                             int &num_passenger_cars,int &num_dining_cars,int &num_sleeping_cars){
    // Initianlize all the variables:
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    
    if (t == NULL) {
        return;
    } else {
        for (; t != NULL; t = t->next) {
            if (t->isEngine()) {
                num_engines++;
                total_weight += 150;
            } else if (t->isFreightCar()){
                num_freight_cars++;
                total_weight += t->getWeight();
            } else if (t->isPassengerCar()) {
                num_passenger_cars++;
                total_weight += 50;
            } else if (t->isDiningCar()){
                num_dining_cars++;
                total_weight += 50;
            } else {
                num_sleeping_cars ++;
                total_weight += 50;
            }
        }
    }
}


float CalculateSpeed(TrainCar* t){
    float speed;
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    TotalWeightAndCountCars(t, total_weight,num_engines, num_freight_cars,
                            num_passenger_cars, num_dining_cars, num_sleeping_cars);
    //----------------------------------------------------------------
    float total_horsepower = num_engines * 3000;
    //----------------------------------------------------------------
    speed = (total_horsepower * 550 * 3600)/((20/.01)*.02*5280*total_weight);
    return speed;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// Try to find whether there are dining cars between engine cars, before engine cars and after engine cars
// If there exist dining cars, the average distance to dining cars is not infinite.
// Here I write this function recursively
bool is_infinite(TrainCar* t){
    if (t == NULL) {
        return false;
    }
    bool found_dinningcar = false;
    bool found_passagercar = false;
    bool found_noengine = false;
    while (!found_noengine) {
        if (!(t->isEngine()) || t->next == NULL){
            found_noengine = true;
        } else {
            t = t->next;
        }
    }
    
    for (; !(t->isEngine()) && t->next != NULL; t = t->next) {
        if (t->isDiningCar()) found_dinningcar = true;
        if (t->isPassengerCar()) found_passagercar = true;
    }
    if (t->isDiningCar()) found_dinningcar = true;
    if (t->isPassengerCar()) found_passagercar = true;
    // For infinite average distance, there are two conditions:
    // the first one is that there is no dinning cars between two engine cars,
    // the second one is that there exists passager cars between two engine cars:
    if ((!found_dinningcar)&&(found_passagercar)) {
        return true;
    } else {
        return is_infinite(t->next);
    }
}


float AverageDistanceToDiningCar(TrainCar* t){
    if (t == NULL) {
        return 0.0;
    }
    float result = 0.0;
    int count = 0;
    int distance = 0;
    int total_distance = 0;
    if (is_infinite(t)) {
        result = -1.0; // Return a negative number when the distance is infinite
    } else {
        while (t != NULL) {
            if (t->isPassengerCar()) {
                count ++;
                TrainCar* t_back = t;
                TrainCar* t_forward = t;
                int distance1 = 0;
                int distance2 = 0;
                bool found_dine_back = false;
                bool found_dine_forward = false;
                while (! t_back->isDiningCar() && t_back->prev != NULL &&
                       ! t_back->prev->isEngine()) {
                    distance1++;
                    t_back = t_back->prev;
                }
                if (t_back->isDiningCar()) {
                    found_dine_back = true;
                }
                while (! t_forward->isDiningCar() && t_forward->next != NULL &&
                       ! t_forward->next->isEngine()) {
                    found_dine_forward = true;
                    distance2++;
                    t_forward = t_forward->next;
                }
                if (t_forward->isDiningCar()) {
                    found_dine_forward = true;
                }
                
                if (found_dine_forward && found_dine_back) {
                    distance = std::min(distance1, distance2);
                } else if (found_dine_back && !found_dine_forward){
                    distance = distance1;
                } else {
                    distance = distance2;
                }
                total_distance += distance;
            }
            t = t->next;
        }
        result = float(total_distance)/float(count);
    }
    return result;
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
int ClosestEngineToSleeperCar(TrainCar* t){
    int min_distance;
    if (t == NULL) {
        min_distance = 0;
    } else {
        int count_total = 2;
        TrainCar* tempcount1 = t;
        while (tempcount1 != NULL) {
            tempcount1 = tempcount1->next;
            count_total ++;
        }
        min_distance = count_total;
        while (t != NULL) {
            bool foundsleep_left = false;
            bool foundsleep_right = false;
            TrainCar* temp_left = t;
            TrainCar* temp_right = t;
            if (t->isEngine()) {
                int count_left = 0;
                int count_right = 0;
                while (temp_left != NULL) {
                    if (temp_left->isSleepingCar()) {
                        foundsleep_left = true;
                        break;
                    }
                    count_left ++;
                    temp_left = temp_left->prev;
                }
                if (foundsleep_left) {
                    min_distance = std::min(min_distance, count_left);
                }
                while (temp_right != NULL) {
                    if (temp_right->isSleepingCar()) {
                        foundsleep_right = true;
                        break;
                    }
                    count_right ++;
                    temp_right = temp_right->next;
                }
                if (foundsleep_right) {
                    min_distance = std::min(min_distance, count_right);
                }
            }
            t= t->next;
        }
    }
    return min_distance;
}
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights,
                                   float min_speed, int max_car_per_train){
    std::vector<TrainCar*> result;
    int freight_weight;
    int engine_weight;
    int num_engines = 0;
    int num_freight_cars = 0;
    //---------------------------
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    int num_engines1 = 0;
    int num_freight_cars1 = 0;
    TotalWeightAndCountCars(freights, freight_weight, num_engines1, num_freight_cars,
                            num_passenger_cars, num_dining_cars, num_sleeping_cars);
    TotalWeightAndCountCars(engines, engine_weight, num_engines, num_freight_cars1,
                            num_passenger_cars, num_dining_cars, num_sleeping_cars);
    
    // First, calulate how much weight a engine can load apart from its own weight based on "the min_speed requirement":
    // freight_weight_one_engine = (3000*1*550*3600)/(min_speed*40*5280) - 150;
    // To make it computable, I calcuate it as follows:
    float a = 125*275*9;
    int b = min_speed*11;
    float freight_weight_one_engine = a/b - 150;
    
    //    int count_cars = 0; // return to zero everytime after shipping a train
    //    float temp_weight = 0; // return to zero everytime after shipping a train
    //    float i = 1.0; // [number of engines in the previous within one train]
    //    cout << num_freight_cars << " " << max_car_per_train <<  " " << freight_weight_one_engine << endl;
    //-----------------------------------------------------------------------------------
    if (num_freight_cars < max_car_per_train) { max_car_per_train = num_freight_cars; }
    //-----------------------------------------------------------------------------------
    
    // If the num_engines is not equal to zero, enter the function:
    while (freights != NULL && num_engines > 0) {
        TrainCar* one_train = train_constructing(engines, freights, min_speed, max_car_per_train,
                                                 freight_weight_one_engine, num_engines);
        result.push_back(one_train);
    }
    return result;
    
}

TrainCar* train_constructing(TrainCar* &engines, TrainCar* &freights, int min_speed, int max_car_per_train,
                             float freight_weight_one_engine, int &num_engines){
    TrainCar* head_of_one_train = engines; // Pointer to the head of the train.
    TrainCar* train_body = engines; // Pointer that is used to go through the train body.
    int count_cars = 1; // Record the number of cars within a single train.
    num_engines --;
    engines = engines->next;
    // Consider the corner case, if pointer is pointing to NULL, it cannot call engines->pre;
    if (engines != NULL) {
        engines->prev = NULL;
    }
    head_of_one_train->next = NULL; // Making it point to NULL, just to be safe in case
    
    // Enter the inside main loop:
    // connect and disconnect one car at a time:
    while (freights != NULL) {
        train_body->next = freights;
        train_body->next->prev = train_body;
        freights = freights->next;
        train_body = train_body->next;
        train_body->next = NULL;
        // Consider the corner case, if pointer is pointing to NULL, it cannot call engines->pre;
        if (freights != NULL) {
            freights->prev = NULL;
        }
        count_cars ++;
        
        // Caculate how many engines needed:
        TrainCar* temp = head_of_one_train;
        float i = Calculate_num_of_engines(temp);
        
        // Check different situations:
        if (count_cars <= (max_car_per_train*i/(i+1))+1 &&
            Calculate_weight(head_of_one_train) > i*freight_weight_one_engine) {
            num_engines --;
            if (num_engines >= 0 ) {
                // Insert this engine after the previous engine:
                TrainCar* temp = engines;
                engines = engines->next;
                if (engines != NULL) {
                    engines->prev = NULL;
                }
                // Below is to make sure the engine car is in order, lower number first:
                TrainCar* pointer = head_of_one_train;
                pointer = pointer->next;
                head_of_one_train->next = temp;
                head_of_one_train->next->prev = head_of_one_train;
                temp->next = pointer;
                temp->next->prev = temp;
                count_cars ++;
            } else {
                if (freights != NULL) {
                    freights->prev = train_body;
                    train_body->next = freights;
                    train_body = train_body->prev;
                    train_body->next = NULL;
                    freights = freights->prev;
                    freights->prev = NULL;
                } else {
                    freights = train_body;
                    train_body= train_body->prev;
                    freights->prev = NULL;
                    train_body->next = NULL;
                }
                count_cars--;
                return head_of_one_train;
            }
        } else if (count_cars > (max_car_per_train*i/(i+1))+1 &&
                   Calculate_weight(head_of_one_train) > i*freight_weight_one_engine) {
            // Which means it is unnecessary to add engines anymore:
            // Since, we step one more step forward, we need to reconnect the final freight back to the freight train
            if (freights != NULL) {
                freights->prev = train_body;
                freights->prev->next = freights;
                freights = freights->prev;
                train_body = train_body->prev;
                train_body->next = NULL;
                freights->prev = NULL;
            } else {
                freights = train_body;
                train_body = train_body->prev;
                freights->prev = NULL;
                train_body->next = NULL;
            }
            count_cars--;
            return head_of_one_train;
        } else if (count_cars == max_car_per_train &&
                   Calculate_weight(head_of_one_train) <= i*freight_weight_one_engine){
            return head_of_one_train;
        }
    }
    return head_of_one_train;
    
}


int Calculate_weight(TrainCar* head){
    int result = 0;
    int weight_of_engine = 0;
    while (head != NULL) {
        result += head->getWeight();
        if (head->isEngine()) {
            weight_of_engine += head->getWeight();
        }
        head = head->next;
    }
    result -= weight_of_engine; // result - 150;
    return result;
}

float Calculate_num_of_engines(TrainCar* head){
    float num = 0;
    while (head != NULL) {
        if (head->isEngine()) {
            num++;
        }
        head = head->next;
    }
    return num;
}

//=====================================================================================================
void remove_cars(TrainCar* &p){
    if (p->prev == NULL) {
        p->next->prev = NULL;
    } else if (p->next == NULL){
        p->prev->next = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
}

void insert_cars_prev(TrainCar* &car, TrainCar* &p){
    car->next = p;
    car->next->prev = car;
    p->next = NULL;
}
void insert_cars_next(TrainCar* &car, TrainCar* &p){
    car->prev = p;
    car->prev->next = car;
    p->prev = NULL;
}

void Separate_HELPER(TrainCar* train1,TrainCar* train2,TrainCar* train3, int num_nonengine_cars){
//    int num = Calculate_numcars_apart_from_engines(train1);
    int num_of_engine = Calculate_num_of_engines(train1);
    int num_trains = 2;
    int ideal_engine_first_car = num_of_engine / num_trains;
//    assert(ideal_engine_first_car != 0);
//    float temp_num_of_engine = num_of_engine;
//    int num_nonengine_cars = num * (ideal_engine_first_car / temp_num_of_engine);
//    float temp_stata = num * (ideal_engine_first_car / temp_num_of_engine);
//    if (num_nonengine_cars != temp_stata) {
//        // rounded to the closest integer
//        num_nonengine_cars = (int)(num * (ideal_engine_first_car / temp_num_of_engine) + 0.5);
//    }
//    assert(num_nonengine_cars != 0);
    int count = 0;
    int count_engine = 0;
    while (train1 != NULL) {
        if (! train1->isEngine()) {
            count ++;
        } else {
            count_engine++;
        }
        
        if (count == num_nonengine_cars) {
            // There are three situations:
            // If the number of engines of the first train is equal to the ideal engines number:
            //---------------------------------------------------------------------------------
            if (count_engine == ideal_engine_first_car) {
                train2 = train1;
                train3 = train1->next;
                train3->prev = NULL;
                train2->next = NULL;
                // Go back to the head
                while (train2->prev!= NULL) {
                    train2 = train2->prev;
                }
                
                while (train1->next != NULL) {
                    train1 = train1->next;
                }
            } else if (count_engine < ideal_engine_first_car){
                // count_engine > ideal_engine_first_car
                //--------------------------------------------------------------------------------------------------------------
                train2 = train1;
                // Go back to the head
                while (train2->prev!= NULL) {
                    train2 = train2->prev;
                }
                //-----------------------------------
                int needed_engines = ideal_engine_first_car - count_engine;
                int specialcounter = 0;
                int i =0;
                TrainCar* temp = train1;
                while (i < needed_engines) {
                    temp = temp->next;
                    if (temp->isEngine()) {i ++;}
                    specialcounter++;
                }
                //------------------------------------
                if (i == specialcounter) { // Special case
                    train3 = temp->next;
                    temp->next = NULL;
                    train3->prev = NULL;
                    
                } else {
                    TrainCar* p = train1->next;
                    train1->next = NULL;// train1 keep track of the ending car of the first train
                    p->prev = NULL;
                    train3 = p;
                    // Make train3 to the first nonengine car
                    while (train3->isEngine()) {
                        train3 = train3->next;
                    }
                    TrainCar* q = p;
                    i = 0;
                    while (i < needed_engines) {
                        q = p->next;
                        if (p->isEngine()) {
                            remove_cars(p);
                            insert_cars_prev(train1, p);
                            train1 = train1->next;
                            i ++;
                        }
                        p = q;
                    }
                    while (train3->prev != NULL) {
                        train3 = train3->prev;
                    }
                }
                while (train1->next != NULL) {
                    train1 = train1->next;
                }
            } else {
                // count_engine > ideal_engine_first_car
                //------------------------------------------------------------------------------------------
                train2 = train1;
                // Go back to the head
                while (train2->prev!= NULL) {
                    train2 = train2->prev;
                }
                //-----------------------------------
                train1 = train1->next;
                TrainCar* temp = train1;
                int needed_engines = count_engine - ideal_engine_first_car;
                int specialcounter = 0;
                int i =0;
                while (i < needed_engines) {
                    temp = temp->prev;
                    if (temp->isEngine()) {i ++;}
                    specialcounter++;
                }
                //------------------------------------------
                if (i == specialcounter) { // Special case
                    train3 = temp;
                    TrainCar* temp1 = temp->prev;
                    train3->prev = NULL;
                    temp1->next = NULL;
                } else {
                    train3 = temp;
                    TrainCar* p =train1->prev;
                    train1->prev = NULL;
                    p->next = NULL;
                    TrainCar* q = p;
                    i = 0;
                    while (i < needed_engines) {
                        q = p->prev;
                        if (p->isEngine()) {
                            remove_cars(p);
                            insert_cars_next(train1, p);
                            train1 = train1->prev;
                            i ++;
                        }
                        p = q;
                    }
                    while (train3->prev != NULL) {
                        train3 = train3->prev;
                    }
                }
                while (train1->next != NULL) {
                    train1 = train1->next;
                }
            }
        }
        train1 = train1->next;
    }
}

void Separate(TrainCar* &train1,TrainCar* &train2,TrainCar* &train3){
    int num = Calculate_numcars_apart_from_engines(train1);
    int num_of_engine = Calculate_num_of_engines(train1);
    int num_trains = 2;
    int ideal_engine_first_car = num_of_engine / num_trains;
    assert(ideal_engine_first_car != 0);
    float temp_num_of_engine = num_of_engine;
    int num_nonengine_cars1 = num * (ideal_engine_first_car / temp_num_of_engine);
    assert(num_nonengine_cars1 != 0);
    int num_noneengine_cars2 = num - num_nonengine_cars1;
    TrainCar* train11 = train1;
    TrainCar* train21 = train2;
    TrainCar* train31 = train3;
    TrainCar* train12 = train1;
    TrainCar* train22 = train2;
    TrainCar* train33 = train3;
    Separate_HELPER(train11, train21, train31, num_nonengine_cars1);
}

int Calculate_numcars_apart_from_engines(TrainCar* train1){
    int num = 0;
    while (train1 != NULL) {
        if (! train1->isEngine()) {
            num ++;
        }
        train1 = train1->next;
    }
    return num;
}

























