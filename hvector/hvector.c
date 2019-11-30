#include "hvector.h"

int currentVersion;

Node* createNode(val* vecVal,int type){
	Node* newNode;
	newNode = ALLOC(Node);
	newNode->type = type;
	switch(type){
		case INT:
			newNode->vecVal.int32 = *CAST(vecVal,int*);
			break;
		case FLOAT:
			newNode->vecVal.float32 = *CAST(vecVal,float*);
			break;
		case STR:
			newNode->vecVal.charc = *CAST(vecVal,char*);
			break;
		case PTR_INT:
			newNode->vecVal.ptr_int = CAST(vecVal,int*);
			break;
		case PTR_FLOAT:
			newNode->vecVal.ptr_float = CAST(vecVal,float*);
			break;
	}
	newNode->next = NULL;
	newNode->back = NULL;
	newNode->modTag = EMPTY;
	return newNode;
}

H* createHead(){
	H* Head;
	Head = ALLOC(H);
	Head->vhi = currentVersion;
	Head->vlow = currentVersion;
	Head->head = NULL;
	Head->next = NULL;
	return Head;
}

List* createList(){
	List* list;
	int i;
	list = ALLOC(List);
	list->H = createHead();
	return list;
}

Node* getPositon(List* list,int pos){
	int i = pos;
	Node *current, *prev;
	current = list->H->head;

	if(i == 0)
		return list->H->head;

	if(i==END){
		while(current!=NULL){
			prev = current;
			if(current->modTag == EMPTY){
				//printf("mod jump\n");
				current = current->next;
			}
			else{
				current = current->Mod.next;
				//printf("static jump\n");
			}
		}
		return prev;
	}

	while(i>0 && current!=NULL){
		prev = current;
		if(current->modTag == EMPTY)
			current = current->next;
		else
			current = current->Mod.next;
		i--;
	}

	if(i!=0 && current==NULL){
		printf("Invalid insert position\n");
		return NULL;
	}

	else return current;
}

void copyLatest(Node* fromNode,Node* toNode){
	toNode->back = fromNode->back;

	if(fromNode->modTag == FULL)
		toNode->next = fromNode->Mod.next;
	else
		toNode->next = fromNode->next;
}

void update(Node* prevNode,Node* node,List* list){

	Node* temp2;
	H* H;

	if(prevNode == NULL){
		H = createHead();
		H->head = node;
		if(node != NULL)
			node->back = NULL;
		H->next = list->H;
		list->H = H;
		return;
	}

	if(node == NULL){
		if(prevNode->modTag == EMPTY){
			prevNode->Mod.version = currentVersion;
			prevNode->Mod.next = NULL;
			prevNode->modTag = FULL;
			list->H->vhi = currentVersion;
			return;
		}
		else{
			temp2 = createNode(&(prevNode->vecVal),prevNode->type);
			copyLatest(prevNode,temp2);
			temp2->next = NULL;
			update(prevNode->back,temp2,list);
			return;
		}
	}

	if(prevNode->modTag == EMPTY){
		prevNode->Mod.version = currentVersion;
		prevNode->Mod.next = node;
		node->back = prevNode;
		prevNode->modTag = FULL;
		list->H->vhi = currentVersion;
		return;
	}

	else{
		temp2 = createNode(&(prevNode->vecVal),prevNode->type);
		copyLatest(prevNode,temp2);
		node->back = temp2;
		temp2->next = node;
		update(prevNode->back,temp2,list);
		return;
	}

}

void insert(val* vecVal,int type, int pos, List* list){

	Node *current,*prev;
	Node *node;

	if(pos>0){
		prev = getPositon(list,pos-1);
		if(prev == NULL){
			printf("invalid position\n");
	 		return;
	 	}
	}
	node = createNode(vecVal,type);
	++currentVersion;

	if (pos==0){
		current = list->H->head;
		node->next = current;
		if(current != NULL) current->back = node;
		node->back = NULL;
		update(node->back,node,list);
		return;
	}

	if (pos == END) prev = getPositon(list,END);

	if(prev->modTag == EMPTY)
		current = prev->next;
	else
		current = prev->Mod.next;

	node->next = current;
	if(current != NULL) node->next->back = node;
	update(prev,node,list);
}

void delete(int pos, List* list){
	int val;
	Node *current;

	current = getPositon(list,pos);
	
	++currentVersion;
	update(current->back,current->next,list);
}

void printList(List* list,int version){
	Node* current;
	H* H;
	H = list->H;
	while(H->vlow > version && H!=NULL){
		H = H->next;
	}

	if(H == NULL){
		printf("invalid version\n");
	}

	current = H->head;

	while(current!=NULL){
		switch(current->type){
			case INT:
				printf("%d->", CAST(current->vecVal.int32,int));
				break;
			case FLOAT:
				printf("%f->", CAST(current->vecVal.float32,float));
				break;
			case STR:
				printf("%c->", CAST(current->vecVal.charc,char));
				break;
			case PTR_FLOAT:
				printf("%p->",CAST(current->vecVal.ptr_float,void*));
				break;
			case PTR_INT:
				printf("%p->",CAST(current->vecVal.ptr_int,void*));
			}
		if(current->modTag == FULL && current->Mod.version <= version){
			current = current->Mod.next;
		}
		else{
			current = current->next;
		}
	}
	printf("NULL\n\n");
}