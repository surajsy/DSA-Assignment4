#include "bst.h"

void main(){

	Tree* tree;
	int i;

	tree = createTree();
	insert(30,tree);
	insert(10,tree);
	insert(40,tree);
	insert(20,tree);
	insert(5,tree);
	insert(50,tree);
	delete(40,tree);
	delete(10,tree);

	for(i=0;i<9;i++){
		printf("version = %d\n", i);
		printf("postorder = ");printPostOrder(tree,i);
		printf("inorder = ");printInOrder(tree,i);
		printf("\n");
	}

	printf("sanity check!\n");
	printf("version = 3\n");
	printf("postorder = ");printPostOrder(tree,3);
	printf("inorder = ");printInOrder(tree,3);

}