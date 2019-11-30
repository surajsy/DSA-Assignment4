#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

#ifndef ALLOC
#define ALLOC(x) (x*)malloc(sizeof(x))
#endif

#define COUNTMAX 10

typedef struct qnode
{
	int val;
	struct qnode* next;	
}QNode;

typedef struct q{
	int frontCount;
	int rearCount;
	QNode* front;
	QNode* rear;
}Queue;

Queue* createQueue();

void enqueue(Queue* q,int num);

int dequeue(Queue *q);

int qIsFull(Queue* q);

int qIsEmpty(Queue* q);

#endif