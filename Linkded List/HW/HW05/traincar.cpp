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


void TotalWeightAndCountCars(TrainCar* t, int &total_weight,int &num_engines, int &num_freight_cars,int &num_passenger_cars,int &num_dining_cars,int &num_sleeping_cars){
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
    TotalWeightAndCountCars(t, total_weight,num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    //----------------------------------------------------------------
    float total_horsepower = num_engines * 3000;
    //----------------------------------------------------------------
    speed = (total_horsepower * 550 * 3600)/((20/.01)*.02*5280*total_weight);
    return speed;
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
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
    // For infinite average distance, there are two conditions: the first one is that there is no dinning cars between
    // two engine cars, the second one is that there exists passager cars between two engine cars:
    if ((!found_dinningcar)&&(found_passagercar)) {
        return true;
    } else {
        return is_infinite(t->next);
    }
}

// This code didn't take into account if there were two or more dining cars: !!!!!!!!!!!!!!!!!!!
void AverageDistance_DiningCar(TrainCar* t, int &denominator, int &numerator){
    if (t == NULL) {
        return;
    } else {
        int id_of_dinningcar = 0;
        bool found_noengine = false;
        while (!found_noengine) {
            if (!(t->isEngine()) || t->next == NULL){
                found_noengine = true;
            } else {
                t = t->next;
            }
        }
        TrainCar* tmp = t;
        while (tmp->isEngine() != true &&  tmp->next != NULL) {
            if (tmp->isDiningCar()) {id_of_dinningcar = tmp->getID();}
            tmp = tmp->next;
        }
        if (tmp->isDiningCar()) {id_of_dinningcar = tmp->getID();}
        // Use Prev to go back to the first place after the last engine car
        
        while (t->isEngine() != true && t->next != NULL) {
            if (t->isPassengerCar()) {
                numerator += abs(id_of_dinningcar - t->getID());
                denominator++;
            }
            t = t->next;
        }
        if (t->isPassengerCar()) {
            numerator += abs(id_of_dinningcar - t->getID());
            denominator++;
        }
        
        AverageDistance_DiningCar(t->next, denominator, numerator);
        }
}
// Helper function of the recusion:
float AverageDistanceToDiningCar(TrainCar* t){
    if (t == NULL) {
        return 0.0;
    }
    float result = 0.0;
    int  denominator = 0.0;
    int  numerator = 0.0;
    
    if (is_infinite(t)) {
        result = -1.0;
    } else {
        AverageDistance_DiningCar(t, denominator, numerator);
        result = float(numerator)/float(denominator);
    }
    return result;
}
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
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
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, float min_speed, int max_car_per_train){
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
    TotalWeightAndCountCars(freights, freight_weight, num_engines1, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    TotalWeightAndCountCars(engines, engine_weight, num_engines, num_freight_cars1, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    
    // First, calulate how much weight a engine can load apart from its own weight based on "the min_speed requirement":
    // freight_weight_one_engine = (3000*1*550*3600)/(min_speed*40*5280) - 150; To make it computable, I calcuate it as follows:
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
        TrainCar* one_train = train_constructing(engines, freights, min_speed, max_car_per_train, freight_weight_one_engine, num_engines);
        result.push_back(one_train);
    }
    return result;
    
}

TrainCar* train_constructing(TrainCar* &engines, TrainCar* &freights, int min_speed, int max_car_per_train, float freight_weight_one_engine, int &num_engines){
    TrainCar* head_of_one_train = engines;
    TrainCar* train_body = engines;
    int count_cars = 1;
    engines = engines->next;
    num_engines --;
    if (engines != NULL) {
        engines->prev = NULL;
    }
    head_of_one_train->next = NULL;
    train_body->next = NULL;
    
    while (freights != NULL) {
        train_body->next = freights;
        train_body->next->prev = train_body;
        freights = freights->next;
        if (freights != NULL) {
            freights->prev = NULL;
        }
        train_body = train_body->next;
        train_body->next = NULL;
        count_cars ++;
        
        // Caculate how many engines needed
        TrainCar* temp = head_of_one_train;
        float i = 0;
        while (temp != NULL) {
            if (temp->isEngine()) {
                i++;
            }
            temp = temp->next;
        }
        // Check different situations:
        if (count_cars <= (max_car_per_train*i/(i+1.0))+1 && Calculate_weight(head_of_one_train) > i*freight_weight_one_engine) {
//            cout << Calculate_weight(head_of_one_train) << endl;
            if (num_engines > 0 ) {
                head_of_one_train->prev = engines;
                engines = engines->next;
                if (engines != NULL) {
                    engines->prev = NULL;
                }
                head_of_one_train->prev->next = head_of_one_train;
                head_of_one_train = head_of_one_train -> prev;
                count_cars ++;
                num_engines --;
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
        } else if (count_cars > (max_car_per_train*i/(i+1.0))+1 && Calculate_weight(head_of_one_train) > i*freight_weight_one_engine) {
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
        } else if (count_cars == max_car_per_train && Calculate_weight(head_of_one_train) <= i*freight_weight_one_engine){
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
    result -= weight_of_engine;
    return result;
}

















































