#include "stack.h"

void main(){
	Stack* s;
	int val;
	SNode *p;


	s = createStack();
//	printf("%d\n", s->topnode->version);
	push(s,10);
	push(s,20);
	push(s,30);
	
	val = pop(s);
	push(s,40);
	push(s,50);
	val = pop(s);

	p = s->topnode->snode;
	while(p!=NULL){
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
	printf("@3 top = %d\n",peekTop(s,3));
	printf("@6 top = %d\n",peekTop(s,6));
}