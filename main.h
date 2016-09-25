/* main.h
 *  Manage a database of cars
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-09-25
 */
 
 #ifndef CAR_DATABASE_H
    #define CAR_DATABASE_H

    #include <stdbool.h>
  
  /* Public types */
  typedef struct car car_t;
  
  /* Public declarations */
  int car_new(char* model, unsigned int* number_of_wheels, unsigned int* number_of_seats, 
              unsigned int* number_of_doors);
  int car_del(unsigned int* db_num);
  int change_car_name(char* model, unsigned int* db_num);
  int change_car_wheels(unsigned int* wheels, unsigned int* db_num);
  int change_car_doors(unsigned int* doors, unsigned int* db_num);
  int change_car_seats(unsigned int* seats, unsigned int* db_num);
  char* get_car_model(unsigned int* db_num);
  unsigned int get_car_wheels(unsigned int* db_num);
  unsigned int get_car_seats(unsigned int* db_num);
  unsigned int get_car_doors(unsigned int* db_num);
  bool is_car_next_null(unsigned int* db_num);
  bool is_car_last_null(unsigned int* db_num);
  
  /* Private declarations */
  static car_t* get_car(unsigned int* db_num);
 
 #endif