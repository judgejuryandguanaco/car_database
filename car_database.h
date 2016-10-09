<<<<<<< HEAD
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
  typedef struct car car_t;
  
  /* Public declarations */
  int newCar(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
              unsigned int* number_of_doors);
  int deleteCar(unsigned int* db_num);
  int changeCarName(char* model, unsigned int* db_num);
  int changeCarWheels(unsigned int* wheels, unsigned int* db_num);
  int changeCarDoors(unsigned int* doors, unsigned int* db_num);
  int changeCarSeats(unsigned int* seats, unsigned int* db_num);
  int lockCarDoors(unsigned int* db_num);
  int unlockCarDoors(unsigned int* db_num);
  char* getCarModel(unsigned int* db_num);
  unsigned int getCarWheels(unsigned int* db_num);
  unsigned int getCarSeats(unsigned int* db_num);
  unsigned int getCarDoors(unsigned int* db_num);
  bool areCarDoorsLocked(unsigned int* db_num);
  bool areCarDoorsUnlocked(unsigned int* db_num);
  bool isNextCarNull(unsigned int* db_num);
  bool isLastCarNull(unsigned int* db_num);
  int saveDatabase(char* filename);
  bool isValidNumber(unsigned int* db_num);
  bool isNotValidNumber(unsigned int* db_num);
  unsigned int getNumberOfEntries(void);
  int loadDatabase (char* filename);
 
=======
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
  int newCar(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
              unsigned int* number_of_doors);
  int deleteCar(unsigned int* db_num);
  int changeCarName(char* model, unsigned int* db_num);
  int changeCarWheels(unsigned int* wheels, unsigned int* db_num);
  int changeCarDoors(unsigned int* doors, unsigned int* db_num);
  int changeCarSeats(unsigned int* seats, unsigned int* db_num);
  int lockCarDoors(unsigned int* db_num);
  int unlockCarDoors(unsigned int* db_num);
  char* getCarModel(unsigned int* db_num);
  unsigned int getCarWheels(unsigned int* db_num);
  unsigned int getCarSeats(unsigned int* db_num);
  unsigned int getCarDoors(unsigned int* db_num);
  bool areCarDoorsLocked(unsigned int* db_num);
  bool areCarDoorsUnlocked(unsigned int* db_num);
  bool isNextCarNull(unsigned int* db_num);
  bool isLastCarNull(unsigned int* db_num);
  int saveDatabase(char* filename);
  bool isValidNumber(unsigned int* db_num);
  bool isNotValidNumber(unsigned int* db_num);
  unsigned int getNumberOfEntries(void);
  int loadDatabase (char* filename);
  void search_model(char* model);
  void search_wheels(unsigned int* number_of_wheels);
  void search_doors(unsigned int* number_of_doors);
  void search_seats(unsigned int* number_of_seats);
 
>>>>>>> refs/remotes/origin/Add-files
 #endif