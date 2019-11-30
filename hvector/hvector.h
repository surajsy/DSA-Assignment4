#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define ALLOC(X) (X*)malloc(sizeof(X))
#define CAST(X,Y) (Y)X

#define EMPTY 0
#define FULL INT_MAX
#define END -1

#define NONE 0
#define INT 1
#define FLOAT 2
#define STR 3
#define PTR_INT 4
#define PTR_FLOAT 5

union value
{
	int int32;
	float float32;
	char charc;
	int* ptr_int;
	float* ptr_float;
};

typedef union value val;

struct mod
{
	int version;
	struct node* next;
};

struct node
{	
	val vecVal;
	int type;
	int modTag;
	struct node *next;
	struct node *back;
	struct mod Mod;
};

typedef struct node Node;
typedef struct mod Mod;

struct head
{
	Node* head;
	int vhi;
	int vlow;	
	struct head *next;
};

typedef struct head H;

struct list
{
	H* H;
};

typedef struct list List;

List* createList();

void insert(val* vecVal,int type, int pos, List* list);

void delete(int pos, List* list);

void printList(List* list,int version);