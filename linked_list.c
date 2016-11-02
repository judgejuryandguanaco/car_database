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
#include <stdarg.h>


#include "linked_list.h"
#include "dynamic_array.h"

typedef struct list list_t;

struct list {
    char* name;
    struct node *start;
    struct node *end;
    unsigned long numnodes;
    unsigned long numdata;
    char **datanames;
    int **types;
};

struct node {
    void **data;
    struct node* last;
    struct node* next;
};

static struct list **lists = NULL;
static unsigned long numlists = 0;

const unsigned int SIZE_OF_TYPES_ARRAY = sizeof(((struct list*)0)->types) / sizeof(char);
static const char *FILE_DELIMETER = " ";
static const char UNSIGNED_INT_MAX_DECIMAL_PLACES = 9;
static const char NULL_CHAR = 1;

/* Static Function Prototypes */
static struct node *getnode(const list_t *list, const unsigned long *num_node);
static void *get_data_address(struct node *temp_node, unsigned int *num_data);
static char* get_type_address(struct list *list, unsigned int *num_type);
static char *addname(const char *listname);
static unsigned long getnumdata(const char types[]);
static char **addtypenames(const char names[], const unsigned long *numtypes);
static int **addtypes(const int types[], const unsigned long *numtypes);
static struct list *getlist(const unsigned long *numlist);
static char *getname(const char** names, const unsigned long *datanum);
static char *gettype(const char** types, const unsigned long *numtype);

/* new_list()
 * Allocates memory for new list, returns address
 * 
 * The list struct is initialised, including a
 * calculation of list.data_size.
 * 
 * If something wrong happens, the function returns
 * NULL.
 */
unsigned long newlist(const char* listname, const int datatypes[], 
		      const char typenames[], const unsigned long *numdata)
{
	struct list *newlist = malloc(sizeof(*newlist));
    struct list **tmplists = NULL;
	
    if (newlist == NULL)
        return 0;
	newlist->name = addname(listname);
    if (newlist->name == NULL)
        return 0;
	newlist->numdata = *numdata;
    if (newlist->numdata <= 0)
        return 0;
	newlist->datanames = addtypenames(typenames, &newlist->numdata);
    if (newlist->datanames == NULL)
        return 0;
    newlist->types = addtypes(datatypes, numdata);
	newlist->start = NULL;
	newlist->end = NULL;
	newlist->numnodes = 0;
    if(lists == NULL) 
        lists = malloc(sizeof(*lists));
    else
        lists = realloc(lists, sizeof(*lists) * (numlists + 1));
    tmplists = lists;
    for(unsigned long i = 0; i < numlists; i++)
        tmplists++;
    *tmplists = newlist;
	return numlists++;
}

/*
 * newnode()
 * 
 */
unsigned long newnode(const unsigned long *numlist)
{
    struct list *tmplist = getlist(numlist);
    struct node *newnode = malloc(sizeof(*newnode));
    
    if(tmplist->numnodes >= ULONG_MAX) {
        free(newnode);
        newnode = NULL;
        return TOO_LARGE;
    }
    
    newnode->data = malloc(sizeof(*newnode->data) * tmplist->numdata);
    memset(newnode->data, NULL, sizeof(newnode->data) * tmplist->numdata);
    
    if (tmplist->numnodes == 0 && tmplist->start == NULL && tmplist->end == NULL) {
        newnode->next = NULL;
        newnode->last = NULL;
        tmplist->start = newnode;
        tmplist->end = newnode;
    } else if (tmplist->numnodes > 0 && tmplist->start != NULL && tmplist->end != NULL) {
        newnode->last = tmplist->end;
        tmplist->end->next = newnode;
        tmplist->end = newnode;
    } else {
        return BROKEN_LIST;
    }
    return ++tmplist->numnodes;
}

/*
 * delnode()
 * 
 */
void del_node(const unsigned long *numlist, const unsigned long *numnode)
{
    struct list *tmplist = getlist(numlist);
    struct node *tmpnode = NULL;
    void **tmpdata = NULL;

    if((*numnode < 1) || (*numnode > tmplist->numnodes)) {
        return;
    } else {
        tmpnode = getnode(tmplist, numnode);
        tmpdata = tmpnode->data;
        
        if((tmpnode == tmplist->start) && (tmpnode->next == NULL) && 
            (tmplist->numdata == 1)) {
            tmplist->start = NULL;
            tmplist->end = NULL;
        } else if ((tmpnode == tmplist->start) && (tmplist->numnodes > 1)) {
            tmplist->start = tmpnode->next;
            tmplist->start->last = NULL;
        } else if ((tmpnode == tmplist->end) && (tmplist->numnodes > 1)) {
            tmplist->end = tmpnode->last;
            tmplist->end->next = NULL;
        } else if (tmplist->numnodes > 1) {
            tmpnode->last->next = tmpnode->next;
            tmpnode->next->last = tmpnode->last;
        }
        tmplist->numnodes--;
        
        tmpnode->next = NULL;
        tmpnode->last = NULL;
        for (int i = 0; i < tmplist->numdata; i++) {
            // erase data?
            free(*tmpdata);
            *tmpdata = NULL;
            tmpdata++;
        }
        free(tmpnode->data);
        tmpnode->data = NULL;
        free(tmpnode);
    }
}

/*
 * adddata()
 * 
 */
int add_data(const unsigned long *numlist, const unsigned long *numnode,
             const unsigned long *numdata, void* data)
{
    struct list *tmplist = getlist(numlist);
    struct node *tmpnode = getnode(tmplist, numnode);
    unsigned long size = 0;
    
    char* type = gettype(tmplist->types, numdata);
    void** tmpdata = tmpnode->data;
    
    for (unsigned long i = 0; i < *numdata; i++) {
        tmpdata++;
    }
    
    switch(*type) {
    case CHAR:
        if (*tmpdata == NULL)
            *tmpdata = malloc(sizeof(char));
        memcpy(tmpdata, data, sizeof(char));
        break;
    case PCHAR:
        size = strlen(data) + 1;
        *tmpdata = realloc(*tmpdata, size*sizeof(char));
        strcpy(*tmpdata, data);
        break;
    case INT:
        if (*tmpdata == NULL)
            *tmpdata = malloc(sizeof(int));
        memcpy(*tmpdata, data, sizeof(int));
        break;
    case UINT:
        if (*tmpdata == NULL)
            *tmpdata = malloc(sizeof(unsigned int));
        memcpy(*tmpdata, data, sizeof(unsigned int));
        break;
    case UCHAR:
        if (*tmpdata == NULL)
            *tmpdata = malloc(sizeof(unsigned char));
        memcpy(*tmpdata, data, sizeof(unsigned char));
        break;
    case BOOL:
        if (*tmpdata == NULL)
            *tmpdata = malloc(sizeof(bool));
        memcpy(*tmpdata, data, sizeof(bool));
    default:
        break;
    }
    
    return 0;
}

/*
 * getname()
 * 
 */
char* get_name(const list_t *list) 
{
    return list->name;
}

unsigned long get_length(const list_t *list)
{
    return list->numnodes;
}

/* 
 * getnode()
 * 
 */
static struct node *getnode(const list_t *list, const unsigned long *numnode)
{
    struct node *tmpnode;
    
    tmpnode = list->start;
    
    if(*numnode == 0) {
        return(NULL);
    } else {
        for(unsigned long i = 1; i < *numnode; i++) {
            tmpnode = tmpnode->next;
        }
    }
    
    return tmpnode;
}

/* 
 * getdata()
 * 
 */
static void **getdata(struct node *usrnode, const unsigned long *numdata)
{
    void **tmpdata = usrnode->data;
    for (unsigned long i = 0; i < *numdata; i++)
        tmpdata++;
        
    return tmpdata;
}

/*
 * getPCHARdata()
 * 
 */
char* get_PCHAR_data(const unsigned long *numlist, const unsigned long *numnode,
                     const unsigned int *numdata)
{
    struct list *tmplist = getlist(numlist);
    struct node *tmpnode = getnode(tmplist, numnode);
    char* tmpdata = *(char**)getdata(tmpnode, numdata);
    return tmpdata;
}

/*
 * getUINTdata()
 *
 */
unsigned int get_UINT_data(const unsigned long *numlist, const unsigned long *numnode,
                           const unsigned int *numdata)
{
    struct list *tmplist = getlist(numlist);
    struct node *tmpnode = getnode(tmplist, numnode);
    unsigned int tmpdata = **(unsigned int**)getdata(tmpnode, numdata);
    return tmpdata;
}

/*
 * getBOOLdata()
 * 
 */
bool get_BOOL_data(const unsigned long *numlist, const unsigned long *numnode,
                   const unsigned int *numdata)
{
    struct list *tmplist = getlist(numlist);
    struct node *tmpnode = getnode(tmplist, numnode);
    bool tmpdata = **(bool**)getdata(tmpnode, numdata);
    return tmpdata;
}

/*
 * getnumnodes()
 * 
 */
unsigned int get_num_nodes(unsigned long *numlist)
{
    struct list *tmplist = getlist(numlist);
    return tmplist->numnodes;
}

void save_list(const list_t *list, const char* filename)
{
    FILE* file;
    struct node *temp_node;
    char string[50] = ""; // replace this w/ a dynamic array
    
    file = fopen(filename, "w");
    
    if (file == NULL) {
        fclose(file);
        return;
    } else {
        fprintf(file, "%s%s%u\n", list->name, FILE_DELIMETER, SIZE_OF_TYPES_ARRAY);
        fprintf(file, "Model Wheels Seats Doors Locked\n");
        for (unsigned long num_node = 1; num_node <= list->numnodes; num_node++) {
            memset(string, 0, sizeof(string));
            temp_node = getnode(list, &num_node);
            
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

list_t *load_list(const char* filename)
{
    FILE* file;
    struct list *temp_list;
    
    char* buffer = NULL;
    char* pch = NULL;
    char* list_name = NULL;
    unsigned int data_t;
    char temp_string[100];
    
    file = fopen(filename, "r");
    
    if (file == NULL) {
        fclose(file);
        return(NULL);
    } else {
        buffer = fgetc(file);
        /* Get list name */
        list_name = strtok(buffer, FILE_DELIMETER);
        
        /* Get number of dats */
    }
    
    fclose(file);
    return temp_list;
}

void merge_database()
{
    return;
}

/*
 * getdataname()
 * 
 */
char *getdataname(unsigned long *numlist, unsigned long *datanum)
{
    struct list *tmplist = getlist(numlist);
    char* tmpname = getname(tmplist->datanames, datanum);
    
    return tmpname;
}

/*
 * getname()
 * 
 */
static char *getname(const char** names, const unsigned long *datanum)
{
    char **tmpnames = names;
    
    for(unsigned long i = 0; i < *datanum; i++) {
        tmpnames++;
    }
    
    return *tmpnames;
}

/* 
 * addname()
 * Calculates the size of string passed to it, allocates memory space, and then
 * copies it into the new space before returning the address.
 */
static char *addname(const char *listname)
{
	char* tmpname;
	unsigned long namelen;
	unsigned long namesize;
	
	namelen = strlen(listname) + NULL_CHAR;
	namesize = namelen * sizeof(*tmpname);
	tmpname = malloc(namesize);
	strcpy(tmpname, listname);
	
	return tmpname;
}

/*
 * getnumdata()
 * Calculate the number of elements in array of chars, then return that
 * number.
 */
static unsigned long getnumdata(const char types[])
{
    char* offset = NULL;
    char* address = types;
    bool exit = false;
    unsigned int i = 0;
	
	do {
		if(*address = '\0')
			exit = true;
        address++;
		i++;
	} while (!exit);
	return i;
}

/*
 * addtypenames()
 * Allocate memory space to store strings, then create an array to
 * hold the location of the strings, then returns that.
 */
static char **addtypenames(const char names[], const unsigned long *numtypes)
{
	char **tmparray = NULL;
    char **offset = NULL;
	char **tmpname = names;
	unsigned int lenname;
	
	tmparray = malloc(sizeof(*tmparray) * *numtypes);
    offset = tmparray;
    for (unsigned long i = 0; i < *numtypes; i++) {
		lenname = strlen(*tmpname) + 1;
		*offset = malloc(sizeof(**offset) * lenname);
		strcpy(*offset, *tmpname);
        offset++;
        tmpname++;
	}
	return tmparray;
}

/*
 * getlist()
 * 
 */
static struct list *getlist(const unsigned long *numlist) 
{
    struct list** tmplists = lists;
    
    for(unsigned long i = 0; i < *numlist; i++)
        tmplists++;
    return *tmplists;
}

/*
 * addtypes()
 * Allocate memory space to store types, allocate memory for each
 * data type, copy data into these before returning address of array
 */
static int **addtypes(const int types[], const unsigned long *numtypes)
{
    int **tmparray = malloc(sizeof(*tmparray) * *numtypes);
    int **offset = tmparray;
    int *tmptype = types;
    
    for (unsigned long i = 0; i < *numtypes; i++) {
        *offset = malloc(sizeof(**offset));
        memcpy(*offset, tmptype, sizeof(**offset));
        offset++;
        tmptype++;
    }
    return tmparray;
}

/*
 * gettype()
 * 
 */
static char *gettype(const char** types, const unsigned long *numtype)
{
    char **tmptypes = types;
    
    for(unsigned long i = 0; i < *numtype; i++)
        tmptypes++;
    return *tmptypes;
}