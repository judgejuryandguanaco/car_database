/* main.c
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */
/* Need to use stdlib and stdio internally but other
 * source files don't need them to use car_database.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "car_database.h"

typedef struct car {
    char model[MAX_CAR_NAME_LENGTH];
	unsigned int number_of_wheels;
	unsigned int number_of_seats;
	unsigned int number_of_doors;
	bool areCarDoorsLocked;
	char* engine_size;
	int efficiency;
	
	car_t* last;
	car_t* next;
} car_t;
	
static car_t* Head = NULL;
static car_t* Tail = NULL;
static bool isFirst = true;
static unsigned int num_db_entries = 0;

int newCar(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
            unsigned int* number_of_doors)
{
	// get bytes from heap
	// if not enough memory, reject
	// add to car list
    
	car_t* new_car = (car_t*)malloc(sizeof(car_t));
	
	memcpy(&new_car->model, model, MAX_CAR_NAME_LENGTH);
	
	new_car->number_of_wheels = *number_of_wheels;
	new_car->number_of_seats = *number_of_seats;
	new_car->number_of_doors = *number_of_doors;
    new_car->areCarDoorsLocked = false;
    new_car->last = NULL;
    new_car->next = NULL;
	
	if(isFirst == true){
	    Head = new_car;
        Tail = new_car;
        isFirst = false;
        num_db_entries = 1;
	}
	else {
        Tail->next = new_car;
        new_car->last = Tail;
        Tail = new_car;
        num_db_entries++;
	}
	return(0);
}

int deleteCar(unsigned int* db_num){
    car_t* car = getCar(db_num);
    if(car == Head) {
        Head = car->next;
        Head->last = NULL;
    }
    else if(car == Tail) {
        Tail = car->last;
        Tail->next = NULL;
    }
    else {
        car->last->next = car->next;
        car->next->last = car->last;
    }
    
	free(car);
    num_db_entries--;
    
    return(0);
}

static car_t* getCar(unsigned int* db_num) {
    car_t* db_entry;
    db_entry = Head;
    
    for(unsigned int i = 1; i < *db_num; i++) {
        db_entry = db_entry->next;
    }
    
    return(db_entry);
}

int changeCarName(char* model, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    memcpy(&getCar(db_num)->model, model, MAX_CAR_NAME_LENGTH);
    return(0);
}

int changeCarWheels(unsigned int* wheels, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    getCar(db_num)->number_of_wheels = *wheels;;
    return(0);
}

int changeCarDoors(unsigned int* doors, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    getCar(db_num)->number_of_doors = *doors;
    return(0);
}

int changeCarSeats(unsigned int* seats, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    getCar(db_num)->number_of_seats = *seats;
    return(0);
}

int lockCarDoors(unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    getCar(db_num)->areCarDoorsLocked = true;
    return(0);
}

int unlockCarDoors(unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return(-1); }
    getCar(db_num)->areCarDoorsLocked = false;
    return(0);
}

bool areCarDoorsLocked(unsigned int* db_num) {
    return getCar(db_num)->areCarDoorsLocked ? true : false;
}

bool areCarDoorsUnlocked(unsigned int* db_num) {
    return getCar(db_num)->areCarDoorsLocked ? false : true;
}

char* getCarModel(unsigned int* db_num){
    return getCar(db_num)->model;
}

unsigned int getCarWheels(unsigned int* db_num) {
    return getCar(db_num)->number_of_wheels;
}

unsigned int getCarSeats(unsigned int* db_num) {
    return getCar(db_num)->number_of_seats;
}

unsigned int getCarDoors(unsigned int* db_num) {
    return getCar(db_num)->number_of_doors;
}

bool isNextCarNull(unsigned int* db_num) {
    return getCar(db_num)->next == NULL ? true : false;
}

bool isLastCarNull(unsigned int* db_num) {
    return getCar(db_num)->last == NULL ? true : false;
}

int saveDatabase(char* filename){
    unsigned int num_db_entry = 1;
    bool isTail = false;
    
    FILE *file = fopen(filename, "w");
    if(file == NULL) { return(-1); }
    else {
        fprintf(file, "Model\t\t\tWheels\tSeats\tDoors\n");
        
        while(!isTail){
            fprintf(file, "%s\t\t\t\%u\t%u\t%u\n", getCarModel(&num_db_entry), getCarWheels(&num_db_entry),
                                                getCarSeats(&num_db_entry), getCarDoors(&num_db_entry));
            if(isNextCarNull(&num_db_entry)) { isTail = true; }
            num_db_entry++;
        }
    }
    fclose(file);
    return(0);
}