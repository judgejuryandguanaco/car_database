/* main.c
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */ 
#include <stdlib.h>

#include "car_database.h"

typedef enum { STARTING, RUNNING, ENDING } states_t;
typedef struct car car_t;

typedef struct car {
    char model[20];
	unsigned int number_of_wheels;
	unsigned int number_of_seats;
	unsigned int number_of_doors;
	//[is each door locked?]
	char* engine_size;
	int efficiency;
	
	car_t* last;
	car_t* next;
} car_t;
	
static car_t* Head = NULL;
static car_t* Tail = NULL;
static bool isFirst = true;
static num_db_entries = 0;

int car_new(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
            unsigned int* number_of_doors)
{
	// get bytes from heap
	// if not enough memory, reject
	// add to car list
    
	car_t* new_car = (car_t*)malloc(sizeof(car_t));
	
	memcpy(&new_car->model, model, 20);
	
	new_car->number_of_wheels = *number_of_wheels;
	new_car->number_of_seats = *number_of_seats;
	new_car->number_of_doors = *number_of_doors;
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

int car_del(unsigned int* db_num){
    car_t* car = get_car(db_num);
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
    
    return;
}

static car_t* get_car(unsigned int* db_num) {
    car_t* db_entry;
    db_entry = Head;
    
    for(unsigned int i = 1; i < *db_num; i++) {
        db_entry = db_entry->next;
    }
    
    return(db_entry);
}

int change_car_name(char* model, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return -1; }
    memcpy(&get_car(db_num)->model, model, 20);
    return(0);
}

int change_car_wheels(unsigned int* wheels, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { -1; }
    get_car(db_num)->number_of_wheels = *wheels;;
    return(0);
}

int change_car_doors(unsigned int* doors, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return -1; }
    get_car(db_num)->number_of_doors = *doors;
    return(0);
}

int change_car_seats(unsigned int* seats, unsigned int* db_num){
    if( (*db_num <=0) || (*db_num > num_db_entries) ) { return -1; }
    get_car(db_num)->number_of_seats = *seats;
    return(0);
}

 areDoorsLocked(unsigned int* db_num)

char* get_car_model(unsigned int* db_num){
    return get_car(db_num)->model;
}

unsigned int get_car_wheels(unsigned int* db_num) {
    return get_car(db_num)->number_of_wheels;
}

unsigned int get_car_seats(unsigned int* db_num) {
    return get_car(db_num)->number_of_seats;
}

unsigned int get_car_doors(unsigned int* db_num) {
    return get_car(db_num)->number_of_doors;
}

bool is_car_next_null(unsigned int* db_num) {
    return get_car(db_num)->next == NULL ? true : false;
}

bool is_car_last_null(unsigned int* db_num) {
    return get_car(db_num)->last == NULL ? true : false;
}