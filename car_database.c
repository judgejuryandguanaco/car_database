/* car_database.c
 *  Provides functions to create, edit, save, and load
 *  a database
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-10-01
 */
 
/* Need to use these libraries internally but other
 * source files don't need them to use car_database.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "car_database.h"
#include "linked_list.h"
#include "dynamic_array.h"

/* Type declarations */

/* Private declarations */

/* Custom types */

/* Private variables */
static list_t* car_database = NULL;

static const unsigned int MODEL = 0;
static const unsigned int NUMBER_OF_WHEELS = 1;
static const unsigned int NUMBER_OF_SEATS = 2;
static const unsigned int NUMBER_OF_DOORS = 3;
static const unsigned int IS_LOCKED = 4;
static const unsigned int NUMBER_OF_VARIABLES = 5;

int createCarDatabase(const char* name)
{
    char types[NUMBER_OF_VARIABLES];
    
    /* Model */
    types[MODEL] = PCHAR;
    /* Number of wheels */
    types[NUMBER_OF_WHEELS] = UINT;
    /* Number of seats */
    types[NUMBER_OF_SEATS] = UINT;
    /* Number of doors */
    types[NUMBER_OF_DOORS] = UINT;
    /* arecardoorslocked*/
    types[IS_LOCKED] = BOOL;
    
    car_database = new_list(name, types);
    
    printf("Hooray!\n");
    
    return(0);
}

int newCar(const char *model, const unsigned int *number_of_wheels, const unsigned int *number_of_seats, 
            const unsigned int *number_of_doors, const bool* is_locked)
{
    unsigned long num_node;
    
    new_node(car_database);
    num_node = get_num_nodes(car_database);
    add_PCHAR_data(car_database, &num_node, &MODEL, model);
    add_UINT_data(car_database, &num_node, &NUMBER_OF_WHEELS, number_of_wheels);
    add_UINT_data(car_database, &num_node, &NUMBER_OF_SEATS, number_of_seats);
    add_UINT_data(car_database, &num_node, &NUMBER_OF_DOORS, number_of_doors);
    add_BOOL_data(car_database, &num_node, &IS_LOCKED, is_locked);
    
	return(0);
}

/* Free memory of specified entry
 */
int deleteCar(const unsigned long *db_num)
{
    del_node(car_database, db_num);
    return(0);
}

/* Get address of specified entry
 * Can only be used within this source file
 */

/* changeCarName
 * Change value of car.model
 * for specified entry
 */
int changeCarName(const char *model, const unsigned long *db_num)
{
    add_PCHAR_data(car_database, db_num, &MODEL, model);
    return(0);
}

/* changeCarWheels
 * Change value of car.number_of_wheels
 * for specified entry
 */
int changeCarWheels(const unsigned int *wheels, const unsigned long *db_num) 
{
    add_UINT_data(car_database, db_num, &NUMBER_OF_WHEELS, wheels);
    return(0);
}

/* changeCarDoors
 * Change value of car.number_of_doors
 * for specified entry
 */
int changeCarDoors(const unsigned int *doors, const unsigned long *db_num)
{
    add_UINT_data(car_database, db_num, &NUMBER_OF_DOORS, doors);
    return(0);
}

/* changeCarSeats
 * Change value of car.number_of_seats
 * for specified entry
 */
int changeCarSeats(const unsigned int *seats, const unsigned long *db_num)
{
    add_UINT_data(car_database, db_num, &NUMBER_OF_SEATS, seats);
    return(0);
}

int changeIsDoorLocked(const bool *is_locked, const unsigned long *db_num)
{
    add_BOOL_data(car_database, db_num, &IS_LOCKED, is_locked);
    return(0);
}

/* lockCarDoors
 * Sets cars.areCarDoorsLocked to true
 * for specified entry
 */
int lockCarDoors(const unsigned long *db_num)
{
    return(0);
}

/* unlockCarDoors
 * Sets car.areCarDoorsLocked to false
 * for specified entyr
 */
int unlockCarDoors(const unsigned long *db_num)
{
    return(0);
}

/* areCarDoorsLocked
 * Returns value of car.areCarDoorsLocked
 * for specified entry
 */
bool areCarDoorsLocked(const unsigned long *db_num)
{
    return get_BOOL_data(car_database, db_num, &IS_LOCKED) ? true : false;
}

/* areCarDoorsUnlocked
 * If car.areCarDoorsUnlocked is true, returns false,
 * if car.areCarDoorsUnlocked is false, returns true
 * for specified entry
 */
bool areCarDoorsUnlocked(const unsigned long *db_num)
{
    return get_BOOL_data(car_database, db_num, &IS_LOCKED) ? false : true;
}

/* getCarModel
 * Returns value of car.number_of_doors for specified
 * entry
 */
char* getCarModel(const unsigned long *db_num)
{
    return get_PCHAR_data(car_database, db_num, &MODEL);
}

/* getCarWheels
 * Returns value of car.number_of_wheels for specified
 * entry
 */
unsigned int getCarWheels(const unsigned long *db_num)
{
    return get_UINT_data(car_database, db_num, &NUMBER_OF_WHEELS);
}

/* getCarSeats
 * Returns value of car.number_of_seats for specified
 * entry
 */
unsigned int getCarSeats(const unsigned long *db_num)
{
    return get_UINT_data(car_database, db_num, &NUMBER_OF_SEATS);
}

/* getCarDoors
 * Returns value of car.number_of_doors for specified
 * entry
 */
unsigned int getCarDoors(const unsigned long *db_num)
{
    return get_UINT_data(car_database, db_num, &NUMBER_OF_DOORS);
}

/* getNumberOfEntries
 * Returns number of entries in database
 */
unsigned int getNumberOfEntries(void)
{
    return get_num_nodes(car_database);
}

bool is_db_entry(const unsigned long *db_num)
{
    return((*db_num <= getNumberOfEntries()) ? true : false);
}

void search_model(const char* model)
{
    unsigned long num_nodes = getNumberOfEntries();
    
    for (unsigned long i = 1; i <= num_nodes; i++) {
        if (strcmp(model, getCarModel(&i)) == 0) {
            printf("%lu", i);
        }
    }
    return;
}

void search_wheels(const unsigned int *wheels)
{
    unsigned int num_nodes = getNumberOfEntries();
    
    for (unsigned long i = 1; i <= num_nodes; i++) {
        if (*wheels == getCarWheels(&i)) {
            printf("%lu", i);
        }
    }
    return;
}

void search_doors(const unsigned int *doors)
{
    unsigned int num_nodes = getNumberOfEntries();
    
    for (unsigned long i = 1; i <= num_nodes; i++) {
        if (*doors == getCarDoors(&i)) {
            printf("%lu", i);
        }
    }
    return;
}

void search_seats(const unsigned int *seats)
{
    unsigned int num_nodes = getNumberOfEntries();
    
    for (unsigned long i = 1; i <= num_nodes; i++) {
        if (*seats == getCarSeats(&i)) {
            printf("%lu", i);
        }
    }
    return;
}

int save(const char* filename)
{
    save_list(car_database, filename);
    return(0);
}