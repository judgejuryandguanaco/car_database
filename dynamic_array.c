#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

typedef struct dynamic_uint_array d_uIntArray_t;

const unsigned int INT_ARRAY_DEFAULT_SIZE = 10;

/* Static function prototypes */
static void expand_d_uIntArray(d_uIntArray_t*);

d_uIntArray_t* new_d_uIntArray(void) {
    d_uIntArray_t* new_array;
    
    new_array = (d_uIntArray_t*)malloc(sizeof(d_uIntArray_t));
    
    new_array->data = (unsigned int*)realloc(NULL, sizeof(unsigned int*)*INT_ARRAY_DEFAULT_SIZE);
    new_array->used = 0;
    new_array->available = INT_ARRAY_DEFAULT_SIZE;
    
    return(new_array);
}

void del_d_uIntArray(d_uIntArray_t* array) {
    free(array);
}

void append_d_uIntArray(d_uIntArray_t* array, unsigned int* data) {
    if(array->used == array->available) { expand_d_uIntArray(array); }
    array->data[array->used++] = *data;
}

void print_d_uIntArray(d_uIntArray_t* array) {
    const unsigned int max_array_position = array->used - 1;
    
    for(unsigned int i = 0; i < max_array_position - 1; i++) {
        printf("%u, ", array->data[i]);
    }
    
    printf("%u\n", array->data[max_array_position]);
}

static void expand_d_uIntArray(d_uIntArray_t* array) {
    unsigned int temp_available;
    unsigned int* temp_data;
    
    temp_available = array->available * 2;
    temp_data = (unsigned int*)realloc(array->data, sizeof(unsigned int*)*temp_available);
    
    if(temp_data == NULL) { printf("Something went wrong :O"); return; }
    else { array->data = temp_data; array->available = temp_available; return; }
}