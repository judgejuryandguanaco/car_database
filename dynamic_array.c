#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dynamic_array.h"

struct dynamic_uint {
    unsigned int *data;
    unsigned int available;
    unsigned int used;
};

struct dynamic_char_array {
    unsigned char *data;
    unsigned int available;
    unsigned int used;
};

typedef struct dynamic_char_array dynamic_char_t;


const unsigned int INT_ARRAY_DEFAULT_SIZE = 10;
const unsigned int UCHAR_ARRAY_DEFAULT_SIZE  = 10;

/* Static function prototypes */
static void expand_d_uIntArray(struct dynamic_uint (*));

dynamic_char_t *new_dynamic_char_t(unsigned int available)
{
    struct dynamic_char_array *new_array;
    
    if( (available <= 0) || (available >= UINT_MAX) ){
        return(-1);
    }
    
    new_array = malloc(sizeof(*new_array));
    
    if(new_array == NULL) {
        printf("dynamic_uchar_t cannot be assigned\n");
        return(-2);
    }
    
    new_array->data = realloc(NULL, sizeof(char)*available);
    new_array->used = 0;
    new_array->available = UCHAR_ARRAY_DEFAULT_SIZE;
}

d_uIntArray_t *new_d_uIntArray(void)
{
    struct dynamic_uint *new_array;
    
    new_array = malloc(sizeof(*new_array));
    
    if(new_array == NULL) {
        printf("new_d_uIntArray cannot be assigned\n");
        return(NULL);
    }
    
    new_array->data = realloc(NULL, sizeof(unsigned int)*INT_ARRAY_DEFAULT_SIZE);
    new_array->used = 0;
    new_array->available = INT_ARRAY_DEFAULT_SIZE;
    
    return(new_array);
}

void del_d_uIntArray(d_uIntArray_t *array) 
{
    free(array);
}

void del_dynamic_uchar_t(dynamic_char_t *array) 
{
    free(array);
}

void append_d_uIntArray(d_uIntArray_t *array, unsigned int *data) {
    if(array->used == array->available)
        expand_d_uIntArray(array);
    array->data[array->used++] = *data;
}

void print_d_uIntArray(d_uIntArray_t *array)
{
    if (array->used == 0) {
        return;
    } else if (array->used == 1) {
        printf("%u\n", array->data[0]);
    } else {
        for(unsigned int i = 0; i < array->used - 1; i++) {
            printf("%u, ", array->data[i]);
        }
        printf("%u\n", array->data[array->used]);
        return;
    }
}

static void expand_d_uIntArray(struct dynamic_uint *array)
{
    unsigned int temp_available;
    unsigned int *temp_data;
    
    temp_available = array->available * 2;
    temp_data = (unsigned int*)realloc(array->data, sizeof(unsigned int)*temp_available);
    
    if(temp_data == NULL) {
        printf("Something went wrong :O"); 
        return; 
    } else { 
        array->data = temp_data; 
        array->available = temp_available; 
        return; 
    }
}