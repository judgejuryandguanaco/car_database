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

typedef struct header db_t;

struct header {
    char* name;
    struct node* start;
    struct node* end;
    unsigned long num_nodes;
    unsigned int data_length;
    char types[5];
};

struct node {
    void* data[5];
    struct node* last;
    struct node* next;
};

const unsigned int SIZE_OF_TYPES_ARRAY = sizeof(((struct header*)0)->types) / sizeof(char);

/* Static Function Prototypes */
static struct node* get_node(db_t *database, unsigned long num_node);

/* new_database()
 * Allocates memory for new header, returns address
 * 
 * The header struct is initialised, including a
 * calculation of header.data_size.
 * 
 * If something wrong happens, the function returns
 * NULL.
 */
db_t* new_list(char *name, char types[5])
{
    struct header *list = malloc(sizeof(list));
    
    list->name = name;
    list->start = NULL;
    list->end = NULL;
    list->num_nodes = 0;
    
    for(int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
        printf("%u\t", types[i]);
        list->types[i] = types[i];
    }
    return((db_t*)list);
}

/* new_db_entry()
 * Creates a new entry w/ reference to a
 * header.
 */
int new_node(db_t *database)
{
    struct node *temp_node;
    
    if(database->num_nodes >= ULONG_MAX)
        return(TOO_LARGE);
    
    temp_node = malloc(sizeof(*temp_node));
    
    for (int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
        temp_node->data[i] = NULL;
    }
    
    if( (database->num_nodes == 0) && 
        (database->start == NULL) && 
        (database->end == NULL) ) {
        database->start = temp_node;
        database->end = temp_node;
        temp_node->last = NULL;
        temp_node->next = NULL;
        database->num_nodes++;
    } else if( (database->num_nodes > 0) &&
               (database->start != NULL) &&
               (database->end != NULL) ){
        temp_node->last = database->end;
        database->end->next = temp_node;
        database->end = temp_node;
        database->num_nodes++;
    } else {
        free(temp_node);
        return(BROKEN_DATABASE);
    }
    
    return(0);
}

void del_node(db_t *database, unsigned long num_node)
{
    struct node *temp_node = NULL;
    unsigned int num_nodes = get_num_nodes(database);
    

    if((num_node < 1) || (num_node > num_nodes)) {
        return;
    } else {
        temp_node = get_node(database, num_node);
        if((temp_node == database->start) && (temp_node->next == NULL) && 
            (num_nodes == 1)) {
            database->start = NULL;
            database->end = NULL;
        } else if ((temp_node == database->start) && (num_nodes > 1)) {
            database->start = temp_node->next;
            database->start->last = NULL;
        } else if ((temp_node == database->end) && (num_nodes > 1)) {
            database->end = temp_node->last;
            database->end->next = NULL;
        } else if (num_nodes > 1) {
            temp_node->last->next = temp_node->next;
            temp_node->next->last = temp_node->last;
        }
        database->num_nodes--;
        for (int i = 0; i < SIZE_OF_TYPES_ARRAY; i++) {
            free(temp_node->data[i]);
        }
        free(temp_node);
    }
}

int add_PCHAR_data(db_t *database, unsigned long num_node, unsigned int num_data, char *data)
{
    struct node *temp_node = NULL;
    const unsigned int NULL_CHAR = 1;

    temp_node = get_node(database, num_node);
    
    if (temp_node->data[num_data] == NULL) {
        temp_node->data[num_data] = malloc((strlen(data) + NULL_CHAR)*sizeof(char));
        strcpy(temp_node->data[num_data], data);
    } else {
        temp_node->data[num_data] = realloc(temp_node->data[num_data], (strlen(data) + NULL_CHAR)*sizeof(char));
        strcpy(temp_node->data[num_data], data);
    }
    return(0);
}

int add_UINT_data(db_t *database, unsigned long num_node, unsigned int num_data, unsigned int *data)
{
    struct node *temp_node = NULL;
    
    temp_node = get_node(database, num_node);
    
    if (temp_node->data[num_data] == NULL) {
        temp_node->data[num_data] = malloc(sizeof(unsigned int));
        memcpy(temp_node->data[num_data], data, sizeof(*data));
    } else {
        memcpy(temp_node->data[num_data], data, sizeof(*data));
    }
    return(0);
}

char* get_name(db_t *database) 
{
    return(database->name);
}

unsigned long get_length(db_t *database)
{
    return(database->num_nodes);
}

static struct node *get_node(db_t *database, unsigned long num_node)
{
    struct node *temp;
    
    temp = database->start;
    
    if(num_node == 0) {
        return(NULL);
    } else {
        for(unsigned long i = 1; i < num_node; i++) {
            temp = temp->next;
        }
    }
    
    return(temp);
}

/* get_data_length()
 * Get number of bytes up to nth unit
 * 
 */
unsigned int get_data_length(db_t* linked_list, unsigned int array_num)
{
    unsigned int data_length = 0;
    
    if(array_num > SIZE_OF_TYPES_ARRAY) {
        return(0);
    } else {
        for(unsigned int i = 0; i < array_num; i++) {
            switch(linked_list->types[i]) {
            case CHAR:
                data_length += sizeof(char);
                break;
            case INT:
                data_length += sizeof(int);
                break;
            case UCHAR:
                data_length += sizeof(unsigned char);
                break;
            case UINT:
                data_length += sizeof(unsigned int);
                break;
            case PCHAR:
                data_length += sizeof(char*);
                break;
            case BOOL:
                data_length += sizeof(bool);
                break;
            case NONE:
                break;
            default:
                return(BROKEN_DATABASE);
                break;
            }
        }
    }
    return(data_length);
}

char* get_PCHAR_data(db_t* database, unsigned int num_node, unsigned int data_no)
{
    struct node *temp_entry = NULL;
    
    if((database->num_nodes >= num_node) && (num_node > 0)) {
        if(database->types[data_no] == PCHAR) {
            temp_entry = get_node(database, num_node);            
            return((char*)temp_entry->data[data_no]);
        }
    }
    return(NULL);
}

unsigned int get_UINT_data(db_t* database, unsigned int num_node, unsigned int data_no)
{
    struct node *temp_entry = NULL;
    unsigned int data_length = 0;
    
    if((database->num_nodes >= num_node) && (num_node > 0)) {
        if(database->types[data_no] == UINT) {
            temp_entry = get_node(database, num_node);
            return(*(unsigned int*)temp_entry->data[data_no]);
        }
    }
    return(0);
}

bool get_BOOL_data(db_t* database, unsigned int num_node, unsigned int data_no)
{
    struct node *temp_entry = NULL;
    unsigned int data_length = 0;
    
    if((database->num_nodes >= num_node) && (num_node > 0)) {
        if(database->types[data_no] == BOOL) {
            temp_entry = get_node(database, num_node);
            return(*(bool*)temp_entry->data[data_no]);
        }
    }
    return(0);
}

unsigned int get_num_nodes(db_t* database)
{
    return(database->num_nodes);
}