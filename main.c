/* main.c
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "car_database.h"

/* Enums
 * List acceptable values of lists and menus. Abstract away assignment of values for those that don'e
 *  matter too much, and assign values to those that need specific values
 */
typedef enum { STARTING, RUNNING, ENDING } states_t; /* Different states of main state machine */
typedef enum { NEW_ENTRY = 'n', MODIFY_ENTRY ='m', DELETE_ENTRY ='d', /* States of user menu */
                VIEW_ENTRY ='v', SAVE_DATABASE = 's', QUIT = 'q' } menu_t;
typedef enum { MODEL = 1, WHEELS = 2, SEATS = 3, DOORS = 4, LOCKS = 5 } data_t; /* States of modify entry menu */

int main(void){
	states_t state = STARTING; /* Initial state */
	states_t next_state;
    char key; /* Single char of user input to choose menus */
    unsigned int num_db_entry; /* Location in linked list of database entry user is interested in */
    /* Local variables to hold user input */
    char model[MAX_CAR_NAME_LENGTH];
    char filename[FILENAME_MAX];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
	
	while(1) { /* Infinite loop - should never leave this */
	    switch (state) {
	    case STARTING: /* This could be for initialising data - eg loading database */
		    next_state = RUNNING;
	    break;
	
	    case RUNNING: /* Bulk of program here */
            next_state = RUNNING; /* Assume RUNNING */
            system("cls"); /* Clear the console */
	        /* List user options and wait for input */
            printf("New car (n)\n");
	        printf("Modify car (m)\n");
	        printf("Delete car (d)\n");
            printf("View car (v)\n");
            printf("Save to file (s)\n");
            printf("Quit (q)\n");
	        
	        scanf("%c", &key);
            while( getchar() != '\n'); /* Sometimes '\n' left in buffer, this clears it */
		
            
		    switch (key) {
            case NEW_ENTRY:
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
                newCar(&model, &number_of_wheels, &number_of_seats, &number_of_doors);
            break; // end of NEW_ENTRY
            
            case MODIFY_ENTRY:
                system("cls");
                printf("Which entry do you want to modify? (1 - %u)\n", getNumberOfEntries());
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                while(!isValidNumber(&num_db_entry)) {
                    system("cls");
                    printf("%u is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
                    scanf("%u", &num_db_entry);
                    while( getchar() != '\n');
                }
                
                printf("So you want to modify %s?\n", getCarModel(&num_db_entry));
                while( getchar() != '\n');
                printf("Which variable do you want to modify?\n");
                printf("(1) Model\n");
                printf("(2) Number of wheels\n");
                printf("(3) Number of seats\n");
                printf("(4) Number of doors\n");
                printf("(5) Lock/unlock doors\n");
                scanf("%u", &key);
                
                switch(key){
                    case MODEL:
                        printf("Please enter new name: ");
                        scanf("%s", model);
                        while( getchar() != '\n');
                        changeCarName(model, &num_db_entry);
                    break;
                    case WHEELS:
                        printf("Please enter new number of wheels: ");
                        scanf("%u", &number_of_wheels);
                        while( getchar() != '\n');
                        changeCarWheels(&number_of_wheels, &num_db_entry);
                    break;
                    case SEATS:
                        printf("Please enter new number of seats: ");
                        scanf("%u", &number_of_seats);
                        while( getchar() != '\n');
                        changeCarSeats(&number_of_seats, &num_db_entry); 
                    break;
                    case DOORS:
                        printf("Please enter new number of doors: ");
                        scanf("%u", &number_of_doors);
                        while( getchar() != '\n');
                        changeCarDoors(&number_of_doors, &num_db_entry);
                    break;
                    case LOCKS:
                        if(areCarDoorsLocked(&num_db_entry)){
                            printf("Unlocking car doors\n");
                            lockCarDoors(&num_db_entry);
                        }
                        else if(areCarDoorsUnlocked(&num_db_entry)) {
                            printf("Locking car doors\n");
                            unlockCarDoors(&num_db_entry);
                        }
                    break;
                    default:
                    break;
                }
            break; // end of MODIFY_ENTRY
		
            case DELETE_ENTRY:
                system("cls");
                printf("Which entry do you want to delete?\n");
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                printf("Are you sure you want to delete %s? (y/n)\n", getCarModel(&num_db_entry));
                
                scanf("%c", &key);
                while( getchar() != '\n');
                    
                switch(key){
                case 'y':
                    printf("Deleting it\n");
                    deleteCar(&num_db_entry);
                break;
                case 'n':
                    ;
                default:
                    ;
                }
            break; // end of DELETE_ENTRY
            
            case VIEW_ENTRY:
                system("cls");
                printf("Which number entry in the database?\n");
                scanf("%u", &num_db_entry);
                while( getchar() != '\n');
                    
                printf("Model\t\t\tWheels\tSeats\tDoors\tLocked?\n");
                printf("%s\t\t\t%u\t%u\t%u\t%u\n", getCarModel(&num_db_entry), getCarWheels(&num_db_entry),
                                            getCarSeats(&num_db_entry), getCarDoors(&num_db_entry), 
                                            areCarDoorsLocked(&num_db_entry));
                printf("Press enter to return to menu\n");
                while( getchar() != '\n');
            break; // end of VIEW_ENTRY
            
            case SAVE_DATABASE:
                // save changes
                // record changes and print them to list?
                // save new and changed entries
                system("cls");
                printf("Please enter filename: ");
                scanf("%s", filename);
                while( getchar() != '\n');
                if(saveDatabase(filename) == 0){
                    printf("Save complete!\n");
                }
                else {
                    printf("Something went wrong :(\n");
                }
            break; // end of SAVE_DATABASE
            
            case QUIT:
                next_state = ENDING;
            break; // end of QUIT
            default:
            break;
            }
		break;
	
		case ENDING:
            return(0);
		break;    
		}
		
		state = next_state;
        }

	return(-1);
}