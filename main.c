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
#include <stdbool.h>

#include "car_database.h"

#define clear_screen system("cls")
#define wait_for_input while(getchar() != '\n')

/* Enums
 * List acceptable values of lists and menus. Abstract away assignment of values for those that don'e
 *  matter too much, and assign values to those that need specific values
 */
enum { STARTING, RUNNING, ENDING} states;
enum { NEW_ENTRY = 'n', MODIFY_ENTRY ='m', DELETE_ENTRY ='d',
       VIEW_ENTRY ='v', SAVE_DATABASE = 's', QUIT = 'q',
       LOAD_DATABASE = 'l', SEARCH_DATABASE = 'z'} menu;
enum { MODEL = '1', WHEELS = '2', SEATS = '3', DOORS = '4', LOCKS = '5' } data;
enum { YES = 'y', NO = 'n', RETURN = 'r' } yes_no; 

static const int FOREVER = 1;

/* Function prototypes */
void running(void);
void new_entry(void);
void search_database(void);

void modify_entry(void);
void delete_entry(void);
void view_entry(void);
void save_database(void);
void load_database(void);

/* main
 * Contains the user interface and various
 * text-based menus
 */
int main(void)
{
	int state;
	int next_state;
	
    state = STARTING;
    
	while (FOREVER) { 
	    switch (state) {
	    case STARTING:
            createCarDatabase("Car database\0");
		    next_state = RUNNING;
            break;
	    case RUNNING:
            running();
            next_state = QUIT;
            break;
        case QUIT:
            next_state = ENDING;
            break;
        case ENDING:
            return(0);
            break; 
        default:
            break;   
		}
		state = next_state;
    }
	return(-1);
}

void running(void)
{
    char key;
    bool notQuit = false;

    while (!notQuit) {
        clear_screen;
        printf("New car (n)\n");
        printf("Modify car (m)\n");
        printf("Delete car (d)\n");
        printf("View car (v)\n");
        printf("Save to file (s)\n");
        printf("Load file (l)\n");
        printf("Search database (z)\n");
        printf("Quit (q)\n");
        scanf("%c", &key);
    
        switch (key) {
        case NEW_ENTRY:
            clear_screen;
            new_entry();
            break;
        case MODIFY_ENTRY:
            clear_screen;
            modify_entry();
            break;
        case SEARCH_DATABASE:
            clear_screen;
            search_database();
            break;
        case DELETE_ENTRY:
            clear_screen;
            delete_entry();
            break;
        case VIEW_ENTRY:
            clear_screen;
            view_entry();
            break;
        case SAVE_DATABASE:
            clear_screen;
            save_database();
            break;
        case LOAD_DATABASE:
            //clear_screen;
            //load_database();
            break; 
        case QUIT:
            notQuit = true;
            break;
        }
    }
}

void new_entry(void) 
{
    char model[MAX_CAR_NAME_LENGTH];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
    bool is_locked = false;

    printf("Name the car model: ");
    scanf("%s", model);
    wait_for_input;
    printf("Number of wheels: ");
    scanf("%u", &number_of_wheels);
    wait_for_input;
    printf("Number of seats: ");
    scanf("%u", &number_of_seats);
    wait_for_input;
    printf("Number of doors: ");
    scanf("%u", &number_of_doors);
    wait_for_input;
    newCar(model, &number_of_wheels, &number_of_seats, &number_of_doors, &is_locked);
    
    return;
}

void modify_entry(void)
{
    unsigned long num_db_entry;
    char model[MAX_CAR_NAME_LENGTH];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
    char key;
    
    printf("Which entry do you want to modify? (1 - %u)\n", getNumberOfEntries());
    scanf("%lu", &num_db_entry);
    while (getchar() != '\n');
    while(!is_db_entry(&num_db_entry)) {
        clear_screen;
        printf("%lu is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
        scanf("%lu", &num_db_entry);
        wait_for_input;
    }
    printf("So you want to modify %s?\n", getCarModel(&num_db_entry));
    wait_for_input;
    printf("Which variable do you want to modify?\n");
    printf("(1) Model\n");
    printf("(2) Number of wheels\n");
    printf("(3) Number of seats\n");
    printf("(4) Number of doors\n");
    printf("(5) Lock/unlock doors\n");
    scanf("%c", &key);
    switch(key){
    case MODEL:
        printf("Please enter new name: ");
        scanf("%s", model);
        wait_for_input;
        changeCarName(model, &num_db_entry);
        break;
    case WHEELS:
        printf("Please enter new number of wheels: ");
        scanf("%u", &number_of_wheels);
        wait_for_input;
        changeCarWheels(&number_of_wheels, &num_db_entry);
        break;
    case SEATS:
        printf("Please enter new number of seats: ");
        scanf("%u", &number_of_seats);
        wait_for_input;
        changeCarSeats(&number_of_seats, &num_db_entry); 
        break;
    case DOORS:
        printf("Please enter new number of doors: ");
        scanf("%u", &number_of_doors);
        wait_for_input;
        changeCarDoors(&number_of_doors, &num_db_entry);
        break;
    case LOCKS:
        if(areCarDoorsLocked(&num_db_entry)){
            printf("Unlocking car doors\n");
            lockCarDoors(&num_db_entry);
        } else if(areCarDoorsUnlocked(&num_db_entry)) {
            printf("Locking car doors\n");
            unlockCarDoors(&num_db_entry);
        }
        break;
    default:
        break;
    }
}

void delete_entry(void)
{
    unsigned long num_db_entry;
    char key;
    
    printf("Which entry do you want to delete?\n");
    scanf("%lu", &num_db_entry);
    wait_for_input;
    while (!is_db_entry(&num_db_entry)) {
        clear_screen;
        printf("%lu is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
        scanf("%lu", &num_db_entry);
        wait_for_input;
    }
    printf("Are you sure you want to delete %s? (y/n)\n", getCarModel(&num_db_entry));
    scanf("%c", &key);
    wait_for_input;
    switch(key){
    case YES:
        printf("Deleting %s\n\r", getCarModel(&num_db_entry));
        deleteCar(&num_db_entry);
        scanf("%lu", &num_db_entry);
        wait_for_input;
        break;
    case NO:
        printf("Not deleting %s\n\r", getCarModel(&num_db_entry));
        scanf("%lu", &num_db_entry);
        wait_for_input;
        break;
    default:
        break;
    }
}

void view_entry(void)
{
    unsigned long num_db_entry;

    if(getNumberOfEntries <= 0) {
        printf("Create or load a database, and add at least 1 entry.\n");
    }
    else {
        printf("Which number entry in the database? (1 to %u)\n", getNumberOfEntries());
        scanf("%lu", &num_db_entry);
        wait_for_input;
        while (!is_db_entry(&num_db_entry)) {
            clear_screen;
            printf("%lu is invalid. Choose between 1 and %u\n", num_db_entry, getNumberOfEntries());
            scanf("%lu", &num_db_entry);
            wait_for_input;
        }
        printf("Model\t\t\tWheels\tSeats\tDoors\tLocked?\n");
        printf("%s\t\t\t%u\t%u\t%u\t%u\n", getCarModel(&num_db_entry), getCarWheels(&num_db_entry),
                                        getCarSeats(&num_db_entry), getCarDoors(&num_db_entry), 
                                        areCarDoorsLocked(&num_db_entry));
    }
    printf("Press enter to return to menu\n");
    wait_for_input;
}

void save_database(void)
{
    char filename[FILENAME_MAX];

    printf("Please enter filename: ");
    scanf("%s", filename);
    wait_for_input;
    if (save(filename) == 0) {
        printf("Save complete!\n");
        printf("Press enter to return to menu\n");
        wait_for_input;
    } else {
        printf("Something went wrong :(\n");
        printf("Press enter to return to menu\n");
        wait_for_input;
    }
}

/*
void load_database(void)
{
    char filename[FILENAME_MAX];

    printf("Please enter filename: ");
    scanf("%s", filename);
    wait_for_input;
    if(loadDatabase(filename) == 0) {
        printf("Load complete!\n\r");
        printf("Press enter to return to menu\n");
        wait_for_input;
    } else {
        printf("Something went wrong :(\n\r");
        printf("Press enter to return to menu\n");
        wait_for_input;
    }
}
*/

void search_database(void)
{
    char key;
    char model[MAX_CAR_NAME_LENGTH];
    unsigned int number_of_wheels;
    unsigned int number_of_seats;
    unsigned int number_of_doors;
    bool isDone = false;

    while(!isDone) {
        clear_screen;
        printf("What do you want to search?\n");
        printf("(1) Model\n");
        printf("(2) Number of wheels\n");
        printf("(3) Number of seats\n");
        printf("(4) Number of doors\n");
        printf("(5) Doors Locked/Unlocked\n");
        scanf("%c", &key);
        wait_for_input;
        switch (key) {
        case MODEL:
            printf("What model do you want to search for?\n");
            scanf("%s", model);
            wait_for_input;
            search_model(model);
            wait_for_input;
            isDone = true;
            break;
        case WHEELS:
            printf("How many wheels?\n");
            scanf("%u", &number_of_wheels);
            wait_for_input;
            search_wheels(&number_of_wheels);
            wait_for_input;
            isDone = true;
            break;
        case SEATS:
            printf("How many seats?\n");
            scanf("%u", &number_of_seats);
            wait_for_input;
            search_seats(&number_of_seats);
            wait_for_input;
            isDone = true;
            break;
        case DOORS:
            printf("How many doors?\n");
            scanf("%u", &number_of_doors);
            wait_for_input;
            search_doors(&number_of_doors);
            wait_for_input;
            isDone = true;
            break;
        case LOCKS:
            break;
        default:
            break;
        }
    }
}