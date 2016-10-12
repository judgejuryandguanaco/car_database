/* dynamic_array.h
 *  Create, control, and use a dynamic array
 * 
 *  Author: Mitchell Smith
 *  Date: 2016-10-09
 */
 
 #ifndef DYNAMIC_ARRAY_H
    #define DYNAMIC_ARRAY_H

/* Other source files need stdbool to use this one */

    
/* Preprocessor definintions */

/* Public types */
typedef struct dynamic_uint d_uIntArray_t;

/* Public declarations */
d_uIntArray_t *new_d_uIntArray(void);
void del_d_uIntArray(d_uIntArray_t *array);
void append_d_uIntArray(d_uIntArray_t *array, unsigned int *data);
void print_d_uIntArray(d_uIntArray_t *array);

#endif