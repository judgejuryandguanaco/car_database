/* linked_list.h */

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

/* Custom types */
typedef struct header db_t;

enum { CHAR = 'c', PCHAR = 'p', INT = 'i', UINT = 'u', UCHAR = 'h', BOOL = 'b', NONE = '0' } entry_data_types;

/* Error messages */
enum { TOO_WIDE = -2, TOO_NARROW = -3, TOO_LARGE = -4, IS_ZERO_OR_LESS = -5, 
        IS_NONE = -6, BROKEN_DATABASE = -7, IS_NULL = -8 };

/* Function prototypes */
    db_t* new_list(char *name, char types[5]);
    int new_node(db_t *database);
    char* get_name(db_t *database);
    unsigned long get_length(db_t *database);
    unsigned int get_data_length(db_t* database, unsigned int array_num);
    int get_data(db_t* database, unsigned int num_node, unsigned int num_data, void* data);
    char* get_PCHAR_data(db_t* database, unsigned int entry_no, unsigned int data_no);
    unsigned int get_UINT_data(db_t* database, unsigned int entry_no, unsigned int data_no);
    bool get_BOOL_data(db_t* database, unsigned int entry_no, unsigned int data_no);
    unsigned int get_num_nodes(db_t* database);
#endif