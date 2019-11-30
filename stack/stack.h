#include <stdlib.h>
#include <stdio.h>

#define ALLOC(X) (X*)malloc(sizeof(X))

struct snode
{
	int val;
	struct snode* next;
};

struct topnode
{
	int version;
	struct snode* snode;
	struct topnode* next;
};

struct stack
{
	struct topnode* topnode;
};

typedef struct snode SNode;
typedef struct topnode TNode;
typedef struct stack Stack;

Stack* createStack();
int peekTop(Stack* s,int version);
void push(Stack *s,int val);
int pop(Stack *s);