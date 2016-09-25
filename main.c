/* main.c
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */ 


#include <stdlib.h>
#include <stdio.h>

#include "main.h"

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
	
car_t* Head = NULL;
car_t* Tail = NULL;
static bool isFirst = true;
	


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
	}
	else {
        Tail->next = new_car;
        new_car->last = Tail;
        Tail = new_car;
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
    memcpy(&get_car(db_num)->model, model, 20);
    return(0);
}

int change_car_wheels(unsigned int* wheels, unsigned int* db_num){
    get_car(db_num)->number_of_wheels = *wheels;;
    return(0);
}

int change_car_doors(unsigned int* doors, unsigned int* db_num){
    get_car(db_num)->number_of_doors = *doors;
    return(0);
}

int change_car_seats(unsigned int* seats, unsigned int* db_num){
    get_car(db_num)->number_of_seats = *seats;
    return(0);
}

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

int main(void){
	states_t state = STARTING;
	states_t next_state;
    bool isTail;
    char key;
    car_t* car;
    unsigned int num_db_entry;
    char model[20];
    char filename[FILENAME_MAX];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
	
	while(1) {
        
	    switch (state) {
	    case STARTING:
		    next_state = RUNNING;
	    break;
	
	    case RUNNING:
            system("cls");
	        printf("New car (n)\n");
	        printf("Modify car (m)\n");
	        printf("Delete car (d)\n");
            printf("Display car (x)\n");
            printf("Save to file (s)\n");
            printf("Quit (q)\n");
	        
	        scanf("%c", &key);
            while( getchar() != '\n');
		
		    switch (key) {
            case 'n':
                system("cls");
                printf("Name the car model: ");
                scanf("%s", model);
                while( getchar() != '\n');
                printf("Number of wheels: ");
                scanf("%u", &number_of_wheels);
                while( getchar() != '\n');
                printf("Number of seats: ");
                scanf("%u", &number_of_seats);
                while( getchar() != '\n');
                printf("Number of doors: ");
                scanf("%u", &number_of_doors);
                while( getchar() != '\n');
                car_new(&model, &number_of_wheels, &number_of_seats, &number_of_doors);
            break;
            case 'm':
                system("cls");
                printf("Which entry do you want to modify?\n");
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                printf("So you want to modify %s?\n", get_car_model(&num_db_entry));
                while( getchar() != '\n');
                printf("Which variable do you want to modify?\n");
                printf("(1) Model\n");
                printf("(2) Number of wheels\n");
                printf("(3) Number of seats\n");
                printf("(4) Number of doors\n");
                scanf("%u", &key);
                
                if(key == 1){
                    printf("Please enter new name: ");
                    scanf("%s", model);
                    while( getchar() != '\n');
                    change_car_name(model, &num_db_entry);
                    
                }
                else if(key == 2){
                    printf("Please enter new number of wheels: ");
                    scanf("%u", &number_of_wheels);
                    while( getchar() != '\n');
                    change_car_wheels(&number_of_wheels, &num_db_entry);
                }
                else if (key == 3){
                    printf("Please enter new number of seats: ");
                    scanf("%u", &number_of_seats);
                    while( getchar() != '\n');
                    change_car_seats(&number_of_seats, &num_db_entry); 
                }
                else if(key == 4){
                    printf("Please enter new number of doors: ");
                    scanf("%u", &number_of_doors);
                    while( getchar() != '\n');
                    change_car_doors(&number_of_doors, &num_db_entry);
                }
            break;
		
            case 'd':
                system("cls");
                printf("Which entry do you want to delete?\n");
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                printf("Are you sure you want to delete %s?\n", get_car_model(&num_db_entry));
                
                scanf("%c", &key);
                while( getchar() != '\n');
                    
                switch(key){
                case 'y':
                    printf("Deleting it\n");
                    car_del(&num_db_entry);
                break;
                case 'n':
                    ;
                default:
                    ;
                }
            break;
            case 'x':
                system("cls");
                printf("Which number entry in the database?\n");
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                    
                printf("Model\t\t\tWheels\tSeats\tDoors\n");
                printf("%s\t\t\t%u\t%u\t%u\n", get_car_model(&num_db_entry), get_car_wheels(&num_db_entry),
                                            get_car_seats(&num_db_entry), get_car_doors(&num_db_entry));
                printf("Press enter to return to menu\n");
                while( getchar() != '\n');
            break;
            case 's':
                // save changes
                // record changes and print them to list?
                // save new and changed entries
                system("cls");
                printf("Please enter filename: ");
                scanf("%s", filename);
                while( getchar() != '\n');
                FILE *f = fopen(filename, "w");
                if(f == NULL){
                    printf("Error openening file\n");
                    break;
                }
                fprintf(f, "Model\t\t\tWheels\tSeats\tDoors\n");
                
                num_db_entry = 1;
                isTail = false;
                while(!isTail){
                    car = get_car(&num_db_entry);
                    fprintf(f, "%s\t\t\t\%u\t%u\t%u\n", get_car_model(&num_db_entry), get_car_wheels(&num_db_entry),
                                            get_car_seats(&num_db_entry), get_car_doors(&num_db_entry));
                    if(is_car_next_null(&num_db_entry)) { isTail = true; }
                    num_db_entry++;
                }

                fclose(f);
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