/* car_database.h
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */
 
 #ifndef CAR_DATABASE_H
    #define CAR_DATABASE_H

    /* Other source files need stdbool to use this one */
    #include <stdbool.h>
    
    /* Preprocessor definintions */
    #define MAX_CAR_NAME_LENGTH 20
    #define MAX_LIST_NAME_LENGTH 20
  
    /* Public types */
  
    /* Public declarations */
    int createCarDatabase(const char* name);
    int newCar(char const *model, const unsigned int *number_of_wheels, const unsigned int *number_of_seats, 
            const unsigned int *number_of_doors, const bool *is_locked);
    int deleteCar(const unsigned long *db_num);
    int changeCarName(const char *model, const unsigned long *db_num);
    int changeCarWheels(const unsigned int *wheels, const unsigned long *db_num);
    int changeCarDoors(const unsigned int *doors, const unsigned long *db_num);
    int changeCarSeats(const unsigned int *seats, const unsigned long *db_num);
    int changeIsDoorLocked(const bool *is_locked, const unsigned long *db_num);
    int lockCarDoors(const unsigned long *db_num);
    int unlockCarDoors(const unsigned long *db_num);
    bool areCarDoorsLocked(const unsigned long *db_num);
    bool areCarDoorsUnlocked(const unsigned long *db_num);
    char* getCarModel(const unsigned long *db_num);
    unsigned int getCarWheels(const unsigned long *db_num);
    unsigned int getCarSeats(const unsigned long *db_num);
    unsigned int getCarDoors(const unsigned long *db_num);
    unsigned int getNumberOfEntries(void);
    bool is_db_entry(const unsigned long *db_num);
    void search_model(const char* model);
    void search_wheels(const unsigned int *wheels);
    void search_doors(const unsigned int *doors);
    void search_seats(const unsigned int *seats);
    int save(const char* filename);
#endif