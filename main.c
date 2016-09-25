/* main.c
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */ 


#include <stdlib.h>
#include <stdio.h>

#include "main.h"

typedef enum { STARTING, RUNNING, ENDING  } states_t;
typedef enum { FALSE, TRUE } bool_t;

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
	
car_t* Head = NULL;
car_t* Tail = NULL;
static bool_t isFirst = TRUE;
	


int car_new(char* model, int number_of_wheels, int number_of_seats, int number_of_doors)
{
	// get bytes from heap
	// if not enough memory, reject
	// add to car list
	
    printf("Head address: %u\n", (void*)Head);
    
	car_t* new_car = (car_t*)malloc(sizeof(car_t));
    printf("new_car address: %u\n", (void*)new_car);
    printf("Head address: %u\n", (void*)Head);
	
	memcpy(&new_car->model, model, 20);
	
	new_car->number_of_wheels = number_of_wheels;
	new_car->number_of_seats = number_of_seats;
	new_car->number_of_doors = number_of_doors;
	
	if(isFirst == TRUE){
	    Head = new_car;
        Tail = new_car;
        isFirst = FALSE;
        printf("\nNew head of chain\n");
        printf("Head->model: %s\n", Head->model, "\n");
        printf("Tail->model: %s\n", Tail->model, "\n");
        printf("new_car_address: %u\n", (void*)new_car);
        printf("Head address: %u\n", (void*)Head);
	}
	else {
        printf("\n", Head->model, "\n");
        
        Tail->next = new_car;
        new_car->last = Tail;
        Tail = new_car;
        printf("\nNew tail of chain\n");
        printf("Head->model: %s\n", Head->model, "\n");
        printf("Tail->model: %s\n", Tail->model, "\n");
        printf("Head->number_of_wheels: %u\n", Head->number_of_wheels);
        printf("Tail->number_of_wheels: %u\n", Tail->number_of_wheels);
        printf("new_car_address: %u\n", (void*)new_car);
        printf("Head address: %u\n", (void*)Head);
	}
	return(0);
}

int car_del(car_t* car){
    printf("In car_del()");
    
    if(car == Head) {
        printf("Old Head address: %u\n", (void*)Head);
        Head = car->next;
        printf("New Head address: %u\n", (void*)Head);
        Head->last = NULL;
    }
    else if(car == Tail) {
        printf("Old Tail address: %u\n", (void*)Tail);
        Tail = car->last;
        printf("New Tail address: %u\n", (void*)Tail);
        Tail->next = NULL;
    }
    else {
        printf("Not Head, not Tail");
        car->last->next = car->next;
        car->next->last = car->last;
    }
    
	free(car);
    
    return;
}

car_t* get_car(unsigned int* db_num) {
    car_t* db_entry;
    db_entry = Head;
    
    printf("db_entry_address: %u\n", (void*)db_entry);
    
    for(unsigned int i = 1; i < *db_num; i++) {
        printf("db_entry_address: %u\n", (void*)db_entry);
        db_entry = db_entry->next;
    }
    
    return(db_entry);
}


int main(void){
	states_t state = STARTING;
	states_t next_state;
    char key;
    car_t* car;
    unsigned int num_db_entry;
    char model[20];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
	
	while(1) {
        
	    switch (state) {
	    case STARTING:
	        printf("Loading database...\n");
		    // load CSV
		    // print some startup stuff
		    next_state = RUNNING;
	    break;
	
	    case RUNNING:
	        printf("New car (n)\n");
	        printf("Modify car (m)\n");
	        printf("Delete car (d)\n");
            printf("Display car (x)\n");
            printf("Quit (q)\n");
	        
	        scanf("%c", &key);
		
		    switch (key) {
                
		        case 'n':
                    printf("Name the car model: ");
                    scanf("%s", model);
                    printf("Number of wheels: ");
                    scanf("%u", &number_of_wheels);
                    printf("Number of seats: ");
                    scanf("%u", &number_of_seats);
                    printf("Number of doors: ");
                    scanf("%u", &number_of_doors);
                
                    printf("Calling car_new");
                    car_new(&model, number_of_wheels, number_of_seats, number_of_doors);
    		    break;
		
		        case 'm':
		            // select option to change
		            // change it
		        break;
		
		        case 'd':
                    printf("Which entry do you want to delete?\n");
                    scanf("%u", &num_db_entry);
                    car = get_car(&num_db_entry);
                    printf("Are you sure you want to delete %s?\n", car->model);
                    
                    scanf("%c", &key);
                    scanf("%c", &key);
                    
                    switch(key){
                        case 'y':
                            printf("Deleting it\n");
                            car_del(car);
                        break;
                        case 'n':
                        ;
                        default:
                        ;
                    }
                break;
                
                case 'x':
                    printf("Which number entry in the database?\n");
                    scanf("%u", &num_db_entry);
                    
                    car = get_car(&num_db_entry);
                    
                    printf("Model\tWheels\tSeats\tDoors\n");
                    printf("%s\t%u\t%u\t%u\n", car->model, car->number_of_wheels,
                                            car->number_of_seats, car->number_of_doors);
                break;
                    
		        case 's':
		            // save changes
		            // record changes and print them to list?
		            // save new and changed entries
		        break;
		
		        case 'q':
		            return(0);
		        break;
		
		        default:
		        break;
            }
		break;
	
		case ENDING:
		break;    
		}
		
		state = next_state;
	}

	return(-1);
}