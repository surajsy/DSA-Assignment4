#include "stack.h"

int currentVersion;

Stack* createStack(){
	Stack *s;
	s = ALLOC(Stack);
	s->topnode = ALLOC(TNode);
	s->topnode->version = currentVersion;
	s->topnode->snode = NULL;
	s->topnode->next = NULL;
	return s;
}

int peekTop(Stack* s,int version){
	TNode *t;
	t = s->topnode;
	while(t->version != version){
		t = t->next;
	}
	if(t->snode != NULL) return t->snode->val;
	else {
		printf("Stack was empty in version %d\n", version);
		return 0;
	}
}

void push(Stack *s,int val){
	TNode *t;
	SNode *n;

	n = ALLOC(SNode);
	n->val = val;
	n->next = s->topnode->snode;

	t = ALLOC(TNode);
	t->version = ++currentVersion;
	t->snode = n;
	t->next = s->topnode;
	s->topnode = t;
}

int pop(Stack *s){
	TNode *t;
	int val;

	t = ALLOC(TNode);
	t->version = ++currentVersion;
	t->snode = s->topnode->snode->next;

	val = s->topnode->snode->val;
	t->next = s->topnode;
	s->topnode = t;
	return val;
}