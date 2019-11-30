#include <stdio.h>
#include <stdlib.h>

#define ALLOC(X) (X*)malloc(sizeof(X))
#define EMPTY 0
#define LEFT 1
#define RIGHT 2

struct mod
{
	int version;
	struct node *next;
};

struct node
{
	int val;
	struct node *left;
	struct node *right;
	int modTag;
	struct mod Mod;
	struct node *back;
};

struct root{
	struct node *root;
	int vhi;
	int vlow;
	struct root *next;
};

struct tree{
	struct root *R;
};

typedef struct mod Mod;
typedef struct node Tnode;
typedef struct root Root;
typedef struct tree Tree;

Tree* createTree();

void insert(int val,Tree* tree);

void delete(int val,Tree *tree);

void printInOrder(Tree* tree,int version);

void printPostOrder(Tree* tree,int version);