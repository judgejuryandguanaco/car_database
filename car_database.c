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

#include "car_database.h"

#define SEARCH_LIST_INITIAL_SIZE 5

/* Type declarations */
typedef struct car car_t;
typedef struct database_result database_result_t;

/* Private declarations */
static car_t* getCar(unsigned int* db_num);
static print_database_result(database_result_t* result);

/* Custom types */

typedef struct car {
    //char* model;
    char model[MAX_CAR_NAME_LENGTH];
	unsigned int number_of_wheels;
	unsigned int number_of_seats;
	unsigned int number_of_doors;
	bool areCarDoorsLocked;
	
	car_t* last;
	car_t* next;
} car_t;

typedef struct database_result {
      unsigned int* results;
      unsigned int array_size;
      unsigned int num_results;
} database_result_t;

/* Private variables */
	
static car_t* Head = NULL;
static car_t* Tail = NULL;
static unsigned int num_db_entries = 0;

int newCar(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
            unsigned int* number_of_doors)
{
    /* Create a new instance of a car by dynamically allocating bytes
     * from the heap. If there isn't enough memory malloc returns NULL
     */
	car_t* new_car = (car_t*)malloc(sizeof(car_t));
	if(new_car == NULL) { return(-1); } /* If NULL something went wrong... */
    
    /* Copy model name into new instance of car */
	memcpy(new_car->model, model, MAX_CAR_NAME_LENGTH);
	
    /* Copy other values into new instance */
	new_car->number_of_wheels = *number_of_wheels;
	new_car->number_of_seats = *number_of_seats;
	new_car->number_of_doors = *number_of_doors;
    new_car->areCarDoorsLocked = false;
    new_car->last = NULL;
    new_car->next = NULL; 
	
    /* If this is the first entry into the database... */
	if(num_db_entries == 0){
	    /* Head and Tail are both the only entry... */
        Head = new_car;
        Tail = new_car;
        num_db_entries = 1;
	}
    /* If this is not the first entry into the database... */
	else {
        /* Link this car to last one */
        Tail->next = new_car;
        /* Link last car to this one */
        new_car->last = Tail;
        /* Make this car the new tail */
        Tail = new_car;

        num_db_entries++;
	}
	return(0);
}

/* Free memory of specified entry
 */
int deleteCar(unsigned int* db_num){
    car_t* car;
    
    /* Get the address of the car */
    car = getCar(db_num);
    
    /* If the car is the only entry in the database... */
    if( (car == Head) && (car->next == NULL) && (num_db_entries == 1) ) {
        /* No head and no tail because no entries */
        Head = NULL;
        Tail = NULL;
    }
    /* If the car is the head of the linked list and not the only entry... */
    else if( (car == Head) && (num_db_entries > 1) ) {
        /* Move head along one */
        Head = car->next;
        /* New head not linked to any prior entry */
        Head->last = NULL;
    }
    /* If the car is the tail of the linked list and not the only entry... */
    else if( (car == Tail) && (num_db_entries > 1) ) {
        /* Move tail down one */
        Tail = car->last;
        /* New tail not linked to any next entry */
        Tail->next = NULL;
    }
    /* If car is not the only entry... */
    else if(num_db_entries > 1){
        /* Link the two entries before and after this one together */
        car->last->next = car->next;
        car->next->last = car->last;
    }
    /* If car is none of these things... */
    else {
        printf("Something went terribly wrong\n\r");
        return(-1);
    }
    
    /* Scrub data within fields */
    memset(car->model, NULL, sizeof(car->model));
    car->number_of_wheels = NULL;
    car->number_of_seats = NULL;
    car->number_of_doors = NULL;
    car->areCarDoorsLocked = NULL;
    car->last = NULL;
    car->next = NULL;
    
    /* Deallocate the memory used for this object in the heap */
	free(car);
    num_db_entries--;
    
    return(0);
}

/* Get address of specified entry
 * Can only be used within this source file
 */
static car_t* getCar(unsigned int* db_num) {
    car_t* db_entry;
    
    /* Start search from the head */
    db_entry = Head;
    
    /* Cycle through entries until get to the right one
     * Can't jump straight to it due to dynamic allocation
     */
    for(unsigned int i = 1; i < *db_num; i++) {
        db_entry = db_entry->next;
    }

    /* Return the address of the entry */
    return(db_entry);
}

/* changeCarName
 * Change value of car.model
 * for specified entry
 */
int changeCarName(char* model, unsigned int* db_num){
    memcpy(&getCar(db_num)->model, model, MAX_CAR_NAME_LENGTH);
    return(0);
}

/* changeCarWheels
 * Change value of car.number_of_wheels
 * for specified entry
 */
int changeCarWheels(unsigned int* wheels, unsigned int* db_num){
    getCar(db_num)->number_of_wheels = *wheels;;
    return(0);
}

/* changeCarDoors
 * Change value of car.number_of_doors
 * for specified entry
 */
int changeCarDoors(unsigned int* doors, unsigned int* db_num){
    getCar(db_num)->number_of_doors = *doors;
    return(0);
}

/* changeCarSeats
 * Change value of car.number_of_seats
 * for specified entry
 */
int changeCarSeats(unsigned int* seats, unsigned int* db_num){
    getCar(db_num)->number_of_seats = *seats;
    return(0);
}

/* lockCarDoors
 * Sets cars.areCarDoorsLocked to true
 * for specified entry
 */
int lockCarDoors(unsigned int* db_num){
    getCar(db_num)->areCarDoorsLocked = true;
    return(0);
}

/* unlockCarDoors
 * Sets car.areCarDoorsLocked to false
 * for specified entyr
 */
int unlockCarDoors(unsigned int* db_num){
    getCar(db_num)->areCarDoorsLocked = false;
    return(0);
}

/* areCarDoorsLocked
 * Returns value of car.areCarDoorsLocked
 * for specified entry
 */
bool areCarDoorsLocked(unsigned int* db_num) {
    return getCar(db_num)->areCarDoorsLocked ? true : false;
}

/* areCarDoorsUnlocked
 * If car.areCarDoorsUnlocked is true, returns false,
 * if car.areCarDoorsUnlocked is false, returns true
 * for specified entry
 */
bool areCarDoorsUnlocked(unsigned int* db_num) {
    return getCar(db_num)->areCarDoorsLocked ? false : true;
}

/* getCarModel
 * Returns value of car.number_of_doors for specified
 * entry
 */
char* getCarModel(unsigned int* db_num){
    return getCar(db_num)->model;
}

/* getCarWheels
 * Returns value of car.number_of_wheels for specified
 * entry
 */
unsigned int getCarWheels(unsigned int* db_num) {
    return getCar(db_num)->number_of_wheels;
}

/* getCarSeats
 * Returns value of car.number_of_seats for specified
 * entry
 */
unsigned int getCarSeats(unsigned int* db_num) {
    return getCar(db_num)->number_of_seats;
}

/* getCarDoors
 * Returns value of car.number_of_doors for specified
 * entry
 */
unsigned int getCarDoors(unsigned int* db_num) {
    return getCar(db_num)->number_of_doors;
}

/* getNumberOfEntries
 * Returns number of entries in database
 */
unsigned int getNumberOfEntries(void){
    return num_db_entries;
}

/* isNextCarNull
 * Checks if car.next is null
 */
bool isNextCarNull(unsigned int* db_num) {
    return getCar(db_num)->next == NULL ? true : false;
}

/* isLastCarNull
 * Checks if car.last is null
 */
bool isLastCarNull(unsigned int* db_num) {
    return getCar(db_num)->last == NULL ? true : false;
}

/* isValidNumber
 * Checks if specified database entry number is valid
 */
bool isValidNumber(unsigned int* db_num) {
    /* Items in the database are numbered 1 to n
       if *db_num is inside this range, it is a valid number
        otherwise, invalid
    */
    if( (*db_num > 0) && (*db_num <= num_db_entries) ) { return(true); }
    else { return(false); }
}

/* isNotValidNumber
 * Checks if specified database entry number is invalid
 */
bool isNotValidNumber(unsigned int* db_num) {
    if( (*db_num <= 0) && (*db_num > num_db_entries)) { return(true); }
    else { return(false); }
}

/* saveDatabase
 * Saves current working database in
 * human-readable format to custom
 * location
 */
int saveDatabase(char* filename){
    unsigned int num_db_entry = 1;
    bool isTail = false;
    FILE* file;
    
    /* Open the file in write mode */
    file = fopen(filename, "w");
    
    /* If the file cannot be opened... */
    if(file == NULL) { return(-1); }
    /* If the file can be opened... */
    else {
        /* Print the header */
        fprintf(file, "Model Wheels Seats Doors\n");
        
        /* Until reach end of linked list, print entries to file */
        while(!isTail){
            fprintf(file, "%s %u %u %u\n", getCarModel(&num_db_entry), getCarWheels(&num_db_entry),
                                                getCarSeats(&num_db_entry), getCarDoors(&num_db_entry));
            /* If 'car.next' is NULL then it must be the tail, and last entry to be printed */
            if(isNextCarNull(&num_db_entry)) { isTail = true; }
            num_db_entry++;
        }
    }
    
    /* Close the file for posterity */
    fclose(file);
    return(0);
}

/* loadDatabase
 * Loads a database file from custom location then
 * adds to current working one
 */
int loadDatabase (char* filename) {
    bool isEOF;
    int i;
    int line_number = 0;
    bool isEndOfLine;
    char buffer[255];
    FILE* file;
    
    char model[MAX_CAR_NAME_LENGTH];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
    
    char* pch;
    
    /* Open the file in read mode */
    file = fopen(filename, "r");
    
    /* If the file cannot be opened... */
    if(file == NULL) { return(-1); }
    /* Otherwise... */
    else {

        isEOF = false;
        
        /* Read file until we find the EOF character, when we do isEOF assigned true */
        while(!isEOF){
            i = 0;
            isEndOfLine = false;
            
            /* Clear buffer by copying NULL into each element of array */
            memset(buffer, NULL, sizeof(buffer));
            
            while(!isEndOfLine){
                
                /* Copy characters into buffer char by char */
                buffer[i] = fgetc(file);
                
                /* If this particular char is the EOF... */
                if(buffer[i] == EOF) { isEOF = true; isEndOfLine = true; }
                
                /* If this particular char is the next line */
                else if (buffer[i] == '\n') {
                    
                    /* First line of file should always be headings, so don't add
                     * these to database */
                    if(line_number > 0){
                        
                        /* Get model */
                        pch = strtok(buffer, " ");
                        memcpy(model, pch, sizeof(pch));
                        
                        /* Get wheels */
                        pch = strtok(NULL, " ");
                        number_of_wheels = strtoul(pch, NULL, 0);
                    
                        /* Get seats*/
                        pch = strtok(NULL, " ");
                        number_of_seats = strtoul(pch, NULL, 0);
                    
                        /* Get doors */
                        pch = strtok(NULL, " ");
                        number_of_doors = strtoul(pch, NULL, 0);
                    
                        newCar(model, &number_of_wheels, &number_of_seats, &number_of_doors);
                    } /* End of if(line_number > 0) */
                    
                line_number++;
                isEndOfLine = true;}
                i++;
            } /* End of while(!isEndOfLine) */
        } /* End of while(!ifEOF) */
    } /* end of else */
    
    fclose(file);
    return(0);
} /* End of loadDatabase */

/* Search model returns the location in db of all
 * entries matching string */
void search_model(char* model) {
    car_t* entry;
    unsigned int db_num;
    bool isNull;
    
    database_result_t list; /* dynamic array */
    
    list.results = (unsigned int*)malloc(sizeof(unsigned int)*SEARCH_LIST_INITIAL_SIZE);
    list.num_results = 0;
    list.array_size = SEARCH_LIST_INITIAL_SIZE;
    
    isNull = false;
    db_num = 1;
    entry = Head;
    
    while(isNull == false) {
        if(strcmp(entry->model, model) == 0) {
            if(list.results >= list.array_size) {
                unsigned int* temp;
                list.array_size *= list.array_size;
                list.results = (unsigned int*)realloc(list.results, sizeof(unsigned int)*list.array_size);
            }
            list.results[list.num_results++] = db_num;
        }
        entry = entry->next;
        db_num++;
        if(entry == NULL) { isNull = true; }
    }
    
    print_database_result(&list);
    
    free(list.results);
    
    return;
}

void search_wheels(unsigned int* number_of_wheels) {
    car_t* entry;
    unsigned int db_num;
    bool isNull;
    
    database_result_t list; /* dynamic array */
    7
    list.results = (unsigned int*)malloc(sizeof(unsigned int)*SEARCH_LIST_INITIAL_SIZE);
    list.num_results = 0;
    list.array_size = SEARCH_LIST_INITIAL_SIZE;
    
    isNull = false;
    db_num = 1;
    entry = Head;
    
    while(isNull == false) {
        if(entry->number_of_wheels == *number_of_wheels) {
            if(list.results >= list.array_size) {
                list.array_size *= list.array_size;
                list.results = (unsigned int*)realloc(list.results, sizeof(unsigned int)*list.array_size);
            }
            list.results[list.num_results++] = db_num;
        }
        entry = entry->next;
        db_num++;
        if(entry == NULL) { isNull = true; }
    }
    
    print_database_result(&list);
    
    free(list.results);
    
    return;
}

static int print_database_result(database_result_t* result) {
    if(result == NULL) { return(-1); }
    else {
        printf("%u entries\n", result->num_results);
        for(int i = 0; i < result->num_results; i++) {
            printf("%u\n", result->results[i]);
        }
    }
    return(0);
}