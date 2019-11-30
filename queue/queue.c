#include "queue.h"

Queue* createQueue(){
	Queue *q;
	
	q = ALLOC(Queue);
	q->front = NULL;
	q->rear = NULL;
	q->frontCount = 0;
	q->rearCount = 0;
	return q;
}

void reverse(Queue* q){
	QNode *current,*prev,*ptr;
	current = q->rear;
	while(current!=NULL){
		prev = current;
		current = current->next;
		prev->next = q->front;
		q->front = prev;
	}

	q->rear = NULL;
	q->frontCount = q->rearCount;
	q->rearCount = 0;
}

void enqueue(Queue* q,int num){
	QNode* qnode;

	if(!qIsFull(q)){
		qnode = ALLOC(QNode);
		qnode->next = q->rear;
		q->rear = qnode;
		qnode->val = num;
		q->rearCount++;
	}
	
	else{
		printf("Queue is full\n");
	}
}

int dequeue(Queue *q){
	int num;
	QNode* current;
	if(!qIsEmpty(q)){
		if(q->frontCount == 0)
			reverse(q);
		current = q->front;
		num = current->val;
		q->front = current->next;
		q->frontCount--;
	}
	return num;
}

int qIsFull(Queue* q){
	if(q==NULL){
		printf("Queue pointer is NULL\n");
		exit(0);
	}
		
	if(q->rearCount > COUNTMAX-1)
		return 1;
	else 
		return 0;
}

int qIsEmpty(Queue* q){
	if(q==NULL){
		printf("Queue pointer is NULL\n");
		exit(0);
	}
	
	if(q->frontCount == 0 && q->rearCount == 0)
		return 1;
	else 
		return 0;
}