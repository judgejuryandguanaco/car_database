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
#include "dynamic_array.h"

/* Type declarations */
struct car;
struct database_result;

/* Private declarations */
static struct car *getCar(unsigned int* db_num);

/* Custom types */

struct car {
    char model[MAX_CAR_NAME_LENGTH];
	unsigned int number_of_wheels;
	unsigned int number_of_seats;
	unsigned int number_of_doors;
	bool areCarDoorsLocked;
	
	struct car *last;
	struct car *next;
};

/* Private variables */
	
static struct car *head = NULL;
static struct car *tail = NULL;
static unsigned int num_db_entries = 0;

int newCar(char *model, unsigned int *number_of_wheels, unsigned int *number_of_seats, 
            unsigned int *number_of_doors)
{
    /* Create a new instance of a car by dynamically allocating bytes
     * from the heap. If there isn't enough memory malloc returns NULL
     */
	struct car *new_car = malloc(sizeof(*new_car));
	if(new_car == NULL)
        return(-1); /* If NULL something went wrong... */
    
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
	if (num_db_entries == 0) {
	    /* head and tail are both the only entry... */
        head = new_car;
        tail = new_car;
        num_db_entries = 1;
	} else { /* If this is not the first entry into the database... */
        /* Link this car to last one */
        tail->next = new_car;
        /* Link last car to this one */
        new_car->last = tail;
        /* Make this car the new tail */
        tail = new_car;

        num_db_entries++;
	}
	return(0);
}

/* Free memory of specified entry
 */
int deleteCar(unsigned int *db_num){
    struct car *car;
    
    car = getCar(db_num);
    
    if ((car == head)&&(car->next == NULL)&&(num_db_entries == 1)) {
        head = NULL;
        tail = NULL;
    } else if((car == head)&&(num_db_entries > 1)) {
        head = car->next;
        head->last = NULL;
    } else if((car == tail)&&(num_db_entries > 1)) {
        tail = car->last;
        tail->next = NULL;
    } else if (num_db_entries > 1) {
        car->last->next = car->next;
        car->next->last = car->last;
    } else {
        printf("Something went terribly wrong\n\r");
        return(-1);
    }
    
    /* Scrub data within fields */
    memset(car->model, '\0', sizeof(car->model));
    car->number_of_wheels = 0;
    car->number_of_seats = 0;
    car->number_of_doors = 0;
    car->areCarDoorsLocked = 0;
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
static struct car* getCar(unsigned int *db_num) {
    struct car *db_entry;
    
    /* Start search from the head */
    db_entry = head;
    
    /* Cycle through entries until get to the right one
     * Can't jump straight to it due to dynamic allocation
     */
    for (unsigned int i = 1; i < *db_num; i++)
        db_entry = db_entry->next;

    /* Return the address of the entry */
    return(db_entry);
}

/* changeCarName
 * Change value of car.model
 * for specified entry
 */
int changeCarName(char *model, unsigned int *db_num) {
    memcpy(&getCar(db_num)->model, model, MAX_CAR_NAME_LENGTH);
    return(0);
}

/* changeCarWheels
 * Change value of car.number_of_wheels
 * for specified entry
 */
int changeCarWheels(unsigned int *wheels, unsigned int *db_num) {
    getCar(db_num)->number_of_wheels = *wheels;
    return(0);
}

/* changeCarDoors
 * Change value of car.number_of_doors
 * for specified entry
 */
int changeCarDoors(unsigned int *doors, unsigned int *db_num) {
    getCar(db_num)->number_of_doors = *doors;
    return(0);
}

/* changeCarSeats
 * Change value of car.number_of_seats
 * for specified entry
 */
int changeCarSeats(unsigned int *seats, unsigned int *db_num) {
    getCar(db_num)->number_of_seats = *seats;
    return(0);
}

/* lockCarDoors
 * Sets cars.areCarDoorsLocked to true
 * for specified entry
 */
int lockCarDoors(unsigned int *db_num) {
    getCar(db_num)->areCarDoorsLocked = true;
    return(0);
}

/* unlockCarDoors
 * Sets car.areCarDoorsLocked to false
 * for specified entyr
 */
int unlockCarDoors(unsigned int *db_num) {
    getCar(db_num)->areCarDoorsLocked = false;
    return(0);
}

/* areCarDoorsLocked
 * Returns value of car.areCarDoorsLocked
 * for specified entry
 */
bool areCarDoorsLocked(unsigned int *db_num) {
    return getCar(db_num)->areCarDoorsLocked ? true : false;
}

/* areCarDoorsUnlocked
 * If car.areCarDoorsUnlocked is true, returns false,
 * if car.areCarDoorsUnlocked is false, returns true
 * for specified entry
 */
bool areCarDoorsUnlocked(unsigned int *db_num) {
    return getCar(db_num)->areCarDoorsLocked ? false : true;
}

/* getCarModel
 * Returns value of car.number_of_doors for specified
 * entry
 */
char* getCarModel(unsigned int *db_num) {
    return getCar(db_num)->model;
}

/* getCarWheels
 * Returns value of car.number_of_wheels for specified
 * entry
 */
unsigned int getCarWheels(unsigned int *db_num) {
    return getCar(db_num)->number_of_wheels;
}

/* getCarSeats
 * Returns value of car.number_of_seats for specified
 * entry
 */
unsigned int getCarSeats(unsigned int *db_num) {
    return getCar(db_num)->number_of_seats;
}

/* getCarDoors
 * Returns value of car.number_of_doors for specified
 * entry
 */
unsigned int getCarDoors(unsigned int *db_num) {
    return getCar(db_num)->number_of_doors;
}

/* getNumberOfEntries
 * Returns number of entries in database
 */
unsigned int getNumberOfEntries(void) {
    return num_db_entries;
}

/* isNextCarNull
 * Checks if car.next is null
 */
bool isNextCarNull(unsigned int *db_num) {
    return getCar(db_num)->next == NULL ? true : false;
}

/* isLastCarNull
 * Checks if car.last is null
 */
bool isLastCarNull(unsigned int *db_num) {
    return getCar(db_num)->last == NULL ? true : false;
}

/* isValidNumber
 * Checks if specified database entry number is valid
 */
bool isValidNumber(unsigned int *db_num) {
    /* Items in the database are numbered 1 to n
       if *db_num is inside this range, it is a valid number
        otherwise, invalid
    */
    if((*db_num > 0)&&(*db_num <= num_db_entries))
        return(true);
    else
        return(false);
}

/* isNotValidNumber
 * Checks if specified database entry number is invalid
 */
bool isNotValidNumber(unsigned int *db_num) {
    if((*db_num <= 0)&&(*db_num > num_db_entries))
        return(true);
    else
        return(false);
}

/* saveDatabase
 * Saves current working database in
 * human-readable format to custom
 * location
 */
int saveDatabase(char *filename){
    unsigned int num_db_entry = 1;
    bool istail = false;
    FILE* file;
    
    /* Open the file in write mode */
    file = fopen(filename, "w");
    
    /* If the file cannot be opened... */
    if (file == NULL) {
        return(-1);
    } else {/* If the file can be opened... */
        /* Print the header */
        fprintf(file, "Model Wheels Seats Doors\n");
        
        /* Until reach end of linked list, print entries to file */
        while (!istail) {
            fprintf(file, "%s %u %u %u\n", getCarModel(&num_db_entry), getCarWheels(&num_db_entry),
                                                getCarSeats(&num_db_entry), getCarDoors(&num_db_entry));
            /* If 'car.next' is NULL then it must be the tail, and last entry to be printed */
            if (isNextCarNull(&num_db_entry))
                istail = true;
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
int loadDatabase (char *filename) {
    bool isEOF;
    int i;
    int line_number = 0;
    bool isEndOfLine;
    char buffer[255];
    FILE *file;
    
    char model[MAX_CAR_NAME_LENGTH];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
    
    char *pch;
    
    /* Open the file in read mode */
    file = fopen(filename, "r");
    
    /* If the file cannot be opened... */
    if (file == NULL) { 
        fclose(file);
        return(-1);
    } else { /* Otherwise... */
        isEOF = false;
        
        /* Read file until we find the EOF character, when we do isEOF assigned true */
        while (!isEOF) {
            i = 0;
            isEndOfLine = false;
            
            /* Clear buffer by copying NULL into each element of array */
            memset(buffer, '\0', sizeof(buffer));
            
            while (!isEndOfLine){
                
                /* Copy characters into buffer char by char */
                buffer[i] = fgetc(file);
                
                /* If this particular char is the EOF... */
                if (buffer[i] == EOF) { 
                    isEOF = true; 
                    isEndOfLine = true;
                } else if (buffer[i] == '\n') { /* If this particular char is the next line */
                    
                    /* First line of file should always be headings, so don't add
                     * these to database */
                    if (line_number > 0) {
                        
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
                    isEndOfLine = true;
                }
                i++;
            } /* End of while(!isEndOfLine) */
        } /* End of while(!ifEOF) */
    } /* end of else */
    
    fclose(file);
    return(0);
} /* End of loadDatabase */

/* Search model returns the location in db of all
 * entries matching string */
void search_model(char *model) {
    struct car *entry;
    unsigned int db_num;
    bool isResults;
    d_uIntArray_t *results; /* dynamic array */
    
    isResults = false;
    db_num = 1;
    entry = head;
    
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    results = new_d_uIntArray();
    
    if(results == NULL) {
        printf("Insufficient memory to conduct search\n");
    }
    
    while (entry != NULL) {
        if (strcmp(entry->model, model) == 0) {
            append_d_uIntArray(results, &db_num);
            isResults = true;
        }
        entry = entry->next;
        db_num++;
    }
    
    if (isResults)
        print_d_uIntArray(results);
    else if (!isResults)
        printf("No results.\n");
    
    del_d_uIntArray(results);
    
    return;
}

void search_wheels(unsigned int *number_of_wheels) {
    struct car *entry;
    unsigned int db_num;
    bool isResults;
    d_uIntArray_t *results;
    
    isNull = false;
    isResults = false;
    db_num = 1;
    entry = head;
    
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    results = new_d_uIntArray();
    
    while (entry != NULL) {
        if (entry->number_of_wheels == *number_of_wheels) {
            append_d_uIntArray(results, &db_num);
            isResults = true;
        }
        entry = entry->next;
        db_num++;
    }
    
    if (isResults)
        print_d_uIntArray(results);
    else if (!isResults)
        printf("No results.\n");

    del_d_uIntArray(results);
    
    return;
}

void search_seats(unsigned int *number_of_seats) {
    struct car *entry;
    unsigned int db_num;
    bool isResults;
    d_uIntArray_t *results;
    
    isNull = false;
    isResults = false;
    db_num = 1;
    entry = head;
    
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    results = new_d_uIntArray();
    
    while (entry != NULL) {
        if(entry->number_of_seats == *number_of_seats) {
            append_d_uIntArray(results, &db_num);
            isResults = true;
        }
        entry = entry->next;
        db_num++;
    }
    
    if (isResults)
        print_d_uIntArray(results);
    else if (!isResults)
        printf("No results.\n");
    del_d_uIntArray(results);
    
    return;
}

void search_doors(unsigned int *number_of_doors) {
    struct car *entry;
    unsigned int db_num;
    bool isResults;
    d_uIntArray_t *results;
    
    isNull = false;
    isResults = false;
    db_num = 1;
    entry = head;
    
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    results = new_d_uIntArray();
    
    while(entry != NULL) {
        if(entry->number_of_doors == *number_of_doors) {
            append_d_uIntArray(results, &db_num);
            isResults = true;
        }
        entry = entry->next;
        db_num++;
    }
    
    if (isResults)
        print_d_uIntArray(results);
    else if (!isResults)
        printf("No results.\n");
        
    del_d_uIntArray(results);
    
    return;
}