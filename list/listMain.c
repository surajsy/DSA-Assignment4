#include "list.h"

void main(){
	List *list;
	int version = 1;
	list = createList();
	insert(10,0,list);
	insert(20,0,list);
	insert(30,1,list);
	insert(40,END,list);
	insert(50,2,list);
	insert(60,2,list);

	delete(2,list);
	delete(0,list);
	delete(1,list);
	delete(END,list);

	for(version=0;version<11;version++){
		printf("version = %d\n", version);
		printList(list,version);
	}

	printf("sanity check! structure actually persitent\n");
	printf("version = 4\n");
	printList(list,4);
	printf("version = 7\n");
	printList(list,7);

}
