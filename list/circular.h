#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define ALLOC(X) (X*)malloc(sizeof(X))

#define EMPTY 0
#define FULL 1
#define END -1

struct mod
{
	int version;
	struct node* next;
};

struct node
{
	int val;
	int version;
	int modTag;
	struct node *next;
	struct node *prev;
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

List* createListC();

void insertC(int val, int pos, List* list);

int deleteC(int pos, List* list);

void printListC(List* list,int version);