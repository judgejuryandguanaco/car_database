/* main.c
 *  User interface to access and use features of
 *  car_database.c
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */ 

/* Libraries */
#include <stdio.h>
#include <stdlib.h>

#include "car_database.h"

/* Enums
 * List acceptable values of lists and menus. Abstract away assignment of values for those that don'e
 *  matter too much, and assign values to those that need specific values
 */
typedef enum { STARTING, RUNNING, ENDING } states_t; /* Different states of main state machine */
enum { NEW_ENTRY = 'n', MODIFY_ENTRY ='m', DELETE_ENTRY ='d', /* States of user menu */
                VIEW_ENTRY ='v', SAVE_DATABASE = 's', QUIT = 'q',
                LOAD_DATABASE = 'l', SEARCH_DATABASE = 'z'} menu;
enum { MODEL = 1, WHEELS = 2, SEATS = 3, DOORS = 4, LOCKS = 5 } data; /* States of modify entry menu */
enum { YES = 'y', NO = 'n', RETURN = 'r' } yes_no; /* States when user presented with yes/no choice; return for quitting */

/* main
 * Contains the user interface and various
 * text-based menus
 */
int main(void){
	states_t state; /* Initial state */
	states_t next_state;
    char key; /* Single char of user input to choose menus */
    unsigned int num_db_entry; /* Location in linked list of database entry user is interested in */
    /* Local variables to hold user input */
    char model[MAX_CAR_NAME_LENGTH];
    char filename[FILENAME_MAX];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
	
    state = STARTING;
    
    /* Infinite loop - should never leave this */
	while(1) { 
        
        /* Jump to case contained in state
         * If state matches no state, jump to 'default' case
         */
	    switch (state) {
        
        /* This could be for initialising data */
	    case STARTING:
		    next_state = RUNNING;
	    break;
	
        /* Bulk of program here */
	    case RUNNING:
            /* Unless otherwise, the next state is this one */
            next_state = RUNNING;
            /* Clear the console */
            system("cls");
	        /* List user options and wait for input */
            printf("New car (n)\n");
	        printf("Modify car (m)\n");
	        printf("Delete car (d)\n");
            printf("View car (v)\n");
            printf("Save to file (s)\n");
            printf("Load file (l)\n");
            printf("Search database (z)\n");
            printf("Quit (q)\n");
	        
	        scanf("%c", &key);
            /* Sometimes '\n' left in buffer, this clears it */
            while( getchar() != '\n');
            
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
                newCar(model, &number_of_wheels, &number_of_seats, &number_of_doors);
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
                
                while(!isValidNumber(&num_db_entry)) {
                    system("cls");
                    printf("%u is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
                    scanf("%u", &num_db_entry);
                    while( getchar() != '\n');
                }
                
                printf("Are you sure you want to delete %s? (y/n)\n", getCarModel(&num_db_entry));
                
                scanf("%c", &key);
                while( getchar() != '\n');
                    
                switch(key){
                case YES:
                    printf("Deleting %s\n\r", getCarModel(&num_db_entry));
                    deleteCar(&num_db_entry);
                    scanf("%u", &num_db_entry);
                    while( getchar() != '\n');
                break;
                case NO:
                    printf("Not deleting %s\n\r", getCarModel(&num_db_entry));
                    scanf("%u", &num_db_entry);
                    while( getchar() != '\n');
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
                
                while(!isValidNumber(&num_db_entry)) {
                    system("cls");
                    printf("%u is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
                    scanf("%u", &num_db_entry);
                    while( getchar() != '\n');
                }
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
                    printf("Press enter to return to menu\n");
                    while( getchar() != '\n');
                }
                else {
                    printf("Something went wrong :(\n");
                    printf("Press enter to return to menu\n");
                    while( getchar() != '\n');
                }
            break; // end of SAVE_DATABASE
            
            case LOAD_DATABASE:
                // Load file and add it to memory
                system("cls");
                printf("Please enter filename: ");
                scanf("%s", filename);
                while( getchar() != '\n');
                if(loadDatabase(filename) == 0) {
                    printf("Load complete!\n\r");
                    printf("Press enter to return to menu\n");
                    while( getchar() != '\n');
                }
                else {
                    printf("Something went wrong :(\n\r");
                    printf("Press enter to return to menu\n");
                    while( getchar() != '\n');
                }
            break; // end of LOAD_DATABASE
            
            case SEARCH_DATABASE:
            system("cls");
                printf("What do you want to search?\n");
                printf("(1) Model\n");
                printf("(2) Number of wheels\n");
                printf("(3) Number of seats\n");
                printf("(4) Number of doors\n");
                printf("(5) Doors Locked/Unlocked\n");
                scanf("%u", &key);
                
                switch(key){
                    case MODEL:
                        printf("What model do you want to search for?\n");
                        scanf("%s", model);
                        while( getchar() != '\n');
                        search_model(model);
                        while(getchar() != '\n');
                    break;
                    case WHEELS:
                        printf("How many wheels?\n");
                        scanf("%u", &number_of_wheels);
                        while( getchar() != '\n');
                        search_wheels(&number_of_wheels);
                        while(getchar() != '\n');
                    break;
                    case SEATS:
                        printf("How many seats?\n");
                        scanf("%u", &number_of_seats);
                        while( getchar() != '\n');
                        search_seats(&number_of_seats);
                        while(getchar() != '\n');
                    break;
                    case DOORS:
                        printf("How many doors?\n");
                        scanf("%u", &number_of_doors);
                        while( getchar() != '\n');
                        search_wheels(&number_of_doors);
                        while(getchar() != '\n');
                    break;
                    case LOCKS:
                    break;
                }
            break;
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