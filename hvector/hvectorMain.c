#include "hvector.h"

void main(){
	List *list;
	int version = 1;
	int num;
	float frac;
	char c;

	list = createList();
	num = 10;
	insert(CAST(&num,val*),INT,0,list);
	frac = 20.452;
	insert(CAST(&frac,val*),FLOAT,0,list);
	c = 'a';
	insert(CAST(&c,val*),STR,1,list);
	c = '4';
	insert(CAST(&c,val*),STR,END,list);
	num = 50;
	insert(CAST(&num,val*),INT,2,list);
	insert(CAST(&num,val*),PTR_INT,2,list);

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