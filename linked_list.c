/* linked_list.c
 * Generate linked list with dynamic number of variables
 * Author: Mitchell Smith
 * Date..: 2016-10-14
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "linked_list.h"
#include "dynamic_array.h"

typedef struct header list_t;

struct header {
    char* name;
    struct node* start;
    struct node* end;
    unsigned long num_nodes;
    char* data_names[5];
    char types[5];
};

struct node {
    void* data[5];
    struct node* last;
    struct node* next;
};

const unsigned int SIZE_OF_TYPES_ARRAY = sizeof(((struct header*)0)->types) / sizeof(char);
static const char *FILE_DELIMETER = " ";
static const char UNSIGNED_INT_MAX_DECIMAL_PLACES = 9;

/* Static Function Prototypes */
static struct node *get_node(const list_t *list, const unsigned long *num_node);

/* new_list()
 * Allocates memory for new header, returns address
 * 
 * The header struct is initialised, including a
 * calculation of header.data_size.
 * 
 * If something wrong happens, the function returns
 * NULL.
 */
list_t* new_list(const char *name, const char types[5])
{
    const unsigned int NULL_CHAR = 1;
    
    struct header *list = malloc(sizeof(list));
    
    list->name = malloc((strlen(name) + NULL_CHAR)*sizeof(*name));
    strcpy(list->name, name);
    
    list->start = NULL;
    list->end = NULL;
    list->num_nodes = 0;
    
    for(int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
        printf("%u\t", types[i]);
        list->types[i] = types[i];
    }
    return((list_t*)list);
}

/* new_db_entry()
 * Creates a new entry w/ reference to a
 * header.
 */
int new_node(list_t *list)
{
    struct node *temp_node;
    
    if(list->num_nodes >= ULONG_MAX)
        return(TOO_LARGE);
    
    temp_node = malloc(sizeof(*temp_node));
    
    for (int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
        temp_node->data[i] = NULL;
    }
    
    if( (list->num_nodes == 0) && 
        (list->start == NULL) && 
        (list->end == NULL) ) {
        list->start = temp_node;
        list->end = temp_node;
        temp_node->last = NULL;
        temp_node->next = NULL;
        list->num_nodes++;
    } else if( (list->num_nodes > 0) &&
               (list->start != NULL) &&
               (list->end != NULL) ){
        temp_node->last = list->end;
        list->end->next = temp_node;
        list->end = temp_node;
        list->num_nodes++;
    } else {
        free(temp_node);
        return(BROKEN_LIST);
    }
    
    return(0);
}

void del_node(list_t *list, const unsigned long *num_node)
{
    struct node *temp_node = NULL;
    unsigned int num_nodes = get_num_nodes(list);
    

    if((*num_node < 1) || (*num_node > num_nodes)) {
        return;
    } else {
        temp_node = get_node(list, num_node);
        if((temp_node == list->start) && (temp_node->next == NULL) && 
            (num_nodes == 1)) {
            list->start = NULL;
            list->end = NULL;
        } else if ((temp_node == list->start) && (num_nodes > 1)) {
            list->start = temp_node->next;
            list->start->last = NULL;
        } else if ((temp_node == list->end) && (num_nodes > 1)) {
            list->end = temp_node->last;
            list->end->next = NULL;
        } else if (num_nodes > 1) {
            temp_node->last->next = temp_node->next;
            temp_node->next->last = temp_node->last;
        }
        list->num_nodes--;
        for (int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
            free(temp_node->data[i]);
        }
        free(temp_node);
    }
}

int add_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data, const void* data)
{
    struct node *temp_node = NULL;
    const unsigned int NULL_CHAR = 1;
    
    //if valid node
    temp_node = get_node(list, num_node);
    
    if(list->types[*num_data] == PCHAR) {   
        temp_node->data[*num_data] = realloc(temp_node->data, (strlen(data) + NULL_CHAR)*sizeof(char));
        strcpy(temp_node->data[*num_data], data);
        return(0);
    } else {
        temp_node->data[*num_data] = realloc(temp_node->data[*num_data], sizeof(*data));
        strcpy(temp_node->data[*num_data], data);
        return(0);
    }
    return(-1);
}

int del_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data)
{
    struct node *temp_node = NULL;
    
    temp_node = get_node(list, num_node);
    // scrub_data ?
    free(temp_node->data[*num_data]);
    temp_node->data[*num_data] = NULL;
    return(0);
}

int add_PCHAR_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data, const char *data)
{
    struct node *temp_node = NULL;
    const unsigned int NULL_CHAR = 1;

    temp_node = get_node(list, num_node);
    
    if (temp_node->data[*num_data] == NULL) {
        temp_node->data[*num_data] = malloc((strlen(data) + NULL_CHAR)*sizeof(char));
        strcpy(temp_node->data[*num_data], data);
    } else {
        temp_node->data[*num_data] = realloc(temp_node->data[*num_data], (strlen(data) + NULL_CHAR)*sizeof(*data));
        strcpy(temp_node->data[*num_data], data);
    }
    return(0);
}

int add_UINT_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data, const unsigned int *data)
{
    struct node *temp_node = NULL;
    
    temp_node = get_node(list, num_node);
    
    if (temp_node->data[*num_data] == NULL) {
        temp_node->data[*num_data] = malloc(sizeof(*data));
        memcpy(temp_node->data[*num_data], data, sizeof(*data));
    } else {
        memcpy(temp_node->data[*num_data], data, sizeof(*data));
    }
    return(0);
}

int add_BOOL_data(const list_t *list, const unsigned long *num_node, const unsigned int *num_data, const bool *data)
{
    struct node *temp_node = NULL;
    
    temp_node = get_node(list, num_node);
    
    if (temp_node->data[*num_data] == NULL) {
        temp_node->data[*num_data] = malloc(sizeof(*data));
        memcpy(temp_node->data[*num_data], data, sizeof(*data));
    } else {
        memcpy(temp_node->data[*num_data], data, sizeof(*data));
    }
    return(0);
}

char* get_name(const list_t *list) 
{
    return(list->name);
}

unsigned long get_length(const list_t *list)
{
    return(list->num_nodes);
}

static struct node *get_node(const list_t *list, const unsigned long *num_node)
{
    struct node *temp;
    
    temp = list->start;
    
    if(*num_node == 0) {
        return(NULL);
    } else {
        for(unsigned long i = 1; i < *num_node; i++) {
            temp = temp->next;
        }
    }
    
    return(temp);
}

char* get_PCHAR_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no)
{
    struct node *temp_entry = NULL;
    
    if((list->num_nodes >= *num_node) && (*num_node > 0)) {
        if(list->types[*data_no] == PCHAR) {
            temp_entry = get_node(list, num_node);            
            return((char*)temp_entry->data[*data_no]);
        }
    }
    return(NULL);
}

unsigned int get_UINT_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no)
{
    struct node *temp_entry = NULL;
    
    if((list->num_nodes >= *num_node) && (*num_node > 0)) {
        if(list->types[*data_no] == UINT) {
            temp_entry = get_node(list, num_node);
            return(*(unsigned int*)temp_entry->data[*data_no]);
        }
    }
    return(0);
}

bool get_BOOL_data(const list_t* list, const unsigned long *num_node, const unsigned int *data_no)
{
    struct node *temp_entry = NULL;
    
    if((list->num_nodes >= *num_node) && (*num_node > 0)) {
        if(list->types[*data_no] == BOOL) {
            temp_entry = get_node(list, num_node);
            return(*(bool*)temp_entry->data[*data_no]);
        }
    }
    return(0);
}

unsigned int get_num_nodes(const list_t* list)
{
    return(list->num_nodes);
}

void save_list(const list_t *list, const char* filename)
{
    FILE* file;
    struct node *temp_node;
    char string[50] = ""; // replace this w/ a dynamic array
    
    file = fopen(filename, "w");
    
    if (file == NULL) {
        return;
    } else {
        fprintf(file, "Model Wheels Seats Doors Locked\n");
        for (unsigned long num_node = 1; num_node <= list->num_nodes; num_node++) {
            memset(string, 0, sizeof(string));
            temp_node = get_node(list, &num_node);
            
            for (unsigned int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
                if (list->types[i] == PCHAR) {
                    strcat(string, (char*)temp_node->data[i]);
                    if(!(i == SIZE_OF_TYPES_ARRAY - 1))
                        strcat(string, FILE_DELIMETER);
                } else if  (list->types[i] == BOOL) {
                    strcat(string, *(bool*)temp_node->data[i] ? "true" : "false");
                    if(!(i == SIZE_OF_TYPES_ARRAY - 1))
                        strcat(string, FILE_DELIMETER);
                } else {
                    char num_to_string[UNSIGNED_INT_MAX_DECIMAL_PLACES];
                    sprintf(num_to_string, "%u", *(unsigned int*)temp_node->data[i]);
                    strcat(string, num_to_string);
                    if(!(i == SIZE_OF_TYPES_ARRAY - 1))
                        strcat(string, FILE_DELIMETER);
                }
            }
            fprintf(file, "%s\n", string);
        }
    }
    
    fclose(file);
    return;
}

void load_list();