#include "queue.h"

void main(){
	Queue *q;

	int i;
	int n = 5;
	int val;

	q = createQueue();
	for(i=0;i<n;i++)
		enqueue(q,i);

	for(i=0;i<n;i++){
		val = dequeue(q);
		printf("%d", val);
	}
	printf("\n");
}