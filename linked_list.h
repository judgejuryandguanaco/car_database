/* linked_list.h */

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

/* Custom types */
typedef struct header list_t;

enum { CHAR, PCHAR, INT, UINT, UCHAR, BOOL, NONE } entry_data_types;

/* Error messages */
enum { TOO_WIDE = -2, TOO_NARROW = -3, TOO_LARGE = -4, IS_ZERO_OR_LESS = -5, 
        IS_NONE = -6, BROKEN_LIST = -7, IS_NULL = -8 };

/* Function prototypes */
list_t* new_list(const char *name, const char types[5]);
int new_node(list_t *list);
void del_node(list_t *list, const unsigned long *num_node);
int add_data(const list_t *list, const unsigned long *num_node, 
			const unsigned int *num_data, const void* data);
int del_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data);
int add_PCHAR_data(const list_t *list, const unsigned long *num_node, 
                    const unsigned int *num_data, const char *data);
int add_UINT_data(const list_t *list, const unsigned long *num_node, 
				const unsigned int *num_data, const unsigned int *data);
int add_BOOL_data(const list_t *list, const unsigned long *num_node, 
                    const unsigned int *num_data, const bool *data);
char* get_name(const list_t *list);
unsigned long get_length(const list_t *list);
char* get_PCHAR_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no);
unsigned int get_UINT_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no);
bool get_BOOL_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no);
unsigned int get_num_nodes(const list_t* list);
#endif