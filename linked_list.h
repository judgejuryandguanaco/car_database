/* linked_list.h */

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

/* Custom types */
typedef struct list list_t;

enum { CHAR, PCHAR, INT, UINT, UCHAR, BOOL, NONE } entry_data_types;

/* Error messages */
enum { TOO_WIDE = -2, TOO_NARROW = -3, TOO_LARGE = -4, IS_ZERO_OR_LESS = -5, 
        IS_NONE = -6, BROKEN_LIST = -7, IS_NULL = -8 };

/* Function prototypes */
list_t* new_list(const char *name, const char *types, const char **data_name, const unsigned int *num_vars);
unsigned long newnode(const unsigned long *numlist);
void del_node(const unsigned long *numlist, const unsigned long *numnode);
int add_data(const unsigned long *numlist, const unsigned long *numnode,
             const unsigned long *numdata, void* data);
int del_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data);
char* get_name(const list_t *list);
unsigned long get_length(const list_t *list);
char* get_PCHAR_data(const unsigned long *numlist, const unsigned long *numnode,
                     const unsigned int *numdata);
unsigned int get_UINT_data(const unsigned long *numlist, const unsigned long *numnode,
                           const unsigned int *numdata);
bool get_BOOL_data(const unsigned long *numlist, const unsigned long *numnode,
                   const unsigned int *numdata);
unsigned int get_num_nodes(unsigned long *numlist);
char *getdataname(unsigned long *numlist, unsigned long *datanum);
char *get_data_type(list_t *list, unsigned int *data_num);
#endif