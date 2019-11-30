#include "bst.h"

int currentVersion;

Root* createRoot(){
	Root *R;
	R = ALLOC(Root);
	R->vhi = currentVersion;
	R->vlow = currentVersion;
	R->root = NULL;
	R->next = NULL;
	return R;
}

Tree* createTree(){
	Tree *tree;
	tree = ALLOC(Tree);
	tree->R = createRoot();
}

Tnode* createNode(int val){
	Tnode* newNode;
	newNode = ALLOC(Tnode);
	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->back = NULL;
	newNode->modTag = EMPTY;
	return newNode;
}

void copyLatest(Tnode* fromNode,Tnode* toNode){
	toNode->back = fromNode->back;

	if(fromNode->modTag == LEFT){
		toNode->left = fromNode->Mod.next;
		toNode->right = fromNode->right;
		if(fromNode->right != NULL) fromNode->right->back = toNode;
		if(fromNode->Mod.next != NULL) fromNode->Mod.next->back = toNode;
	}
	else if(fromNode->modTag == RIGHT){
		toNode->right = fromNode->Mod.next;
		toNode->left = fromNode->left;
		if(fromNode->left != NULL) fromNode->left->back = toNode;
		if(fromNode->Mod.next != NULL) fromNode->Mod.next->back = toNode;
	}
	else{
		toNode->left = fromNode->left;
		toNode->right = fromNode->right;
		if(fromNode->left != NULL) fromNode->left->back = toNode;
		if(fromNode->right != NULL) fromNode->right->back = toNode;
	}
}

void update(Tnode* root,Tnode* leaf,Tree* tree,int mod){
	Tnode* temp2;
	Root* R;

	if(root == NULL){
		R = createRoot();
		R->root = leaf;
//		if(leaf != NULL) printf("new root for %d\n",leaf->val);
		R->next = tree->R;
		tree->R = R;
		return;
	}

	if(leaf == NULL){
		if(root->modTag == EMPTY){
//			printf("mod changed at node %d to NULL\n", root->val);
			root->Mod.version = currentVersion;
			root->Mod.next = NULL;
			root->modTag = mod;
			tree->R->vhi = currentVersion;
			return;
		}
		else{
			temp2 = createNode(root->val);
			copyLatest(root,temp2);
			if(mod == LEFT) temp2->left = NULL;
			else temp2->right = NULL;
			if(root->back != NULL && root->back->val > temp2->val)
				update(root->back,temp2,tree,LEFT);
			else
				update(root->back,temp2,tree,RIGHT);
			return;
		}
	}

	if(root->modTag == EMPTY){
//		printf("mod changed at node %d to %d\n", root->val,leaf->val);
		root->Mod.version = currentVersion;
		root->Mod.next = leaf;
		leaf->back = root;
		root->modTag = mod;
		tree->R->vhi = currentVersion;
		return;
	}

	else{
		temp2 = createNode(root->val);
		copyLatest(root,temp2);
		leaf->back = temp2;
		
//		printf("static update at new node %d to %d\n", root->val, leaf->val);
		if(mod == LEFT)
			temp2->left = leaf;
		else
			temp2->right = leaf;

		if(root->back != NULL && root->back->val > temp2->val)
			update(root->back,temp2,tree,LEFT);
		else
			update(root->back,temp2,tree,RIGHT);
		return;
	}	
}

void insert(int val,Tree* tree){
	Tnode *tnode, *leaf, *root;
	root = tree->R->root;

	tnode = NULL;
	while(root!=NULL){
		tnode = root;
		if(val > root->val){
			if(root->modTag == EMPTY || root->modTag == LEFT)
				root = root->right;
			else
				root = root->Mod.next;
		}
		else if(val < root->val){
			if(root->modTag == EMPTY || root->modTag == RIGHT)
				root = root->left;
			else
				root = root->Mod.next;
		}
		else{
			printf("value already in the tree. cannot insert\n");
			return;
		}
	}

//	if(tnode!= NULL) printf("%d\n", tnode->val);
	++currentVersion;
	leaf = createNode(val);

	if(tnode != NULL && tnode->val > leaf->val)
		update(tnode,leaf,tree,LEFT);
	else
		update(tnode,leaf,tree,RIGHT);
}

Tnode* findPredecessor(Tnode *root){
	Tnode *pred;
	if(root->modTag == LEFT)
		pred = root->Mod.next;
	else
		pred = root->left;

	while(pred!=NULL && pred->right!=NULL){
		if(pred->modTag == RIGHT)
			pred = pred->Mod.next;
		else
			pred = pred->right;
	}

	return pred;
}

void delete(int val,Tree *tree){
	Tnode *root, *tnode, *leaf, *tnode2, *back;
	Tree *temp;
	root = tree->R->root;

	if(root == NULL){
		printf("Tree is empty. Cannot delete\n");
		return;
	}

	while(root!=NULL){
		if(val > root->val){
			if(root->modTag == EMPTY || root->modTag == LEFT)
				root = root->right;
			else
				root = root->Mod.next;
		}
		else if(val < root->val){
			if(root->modTag == EMPTY || root->modTag == RIGHT)
				root = root->left;
			else
				root = root->Mod.next;
		}
		else break;
	}

	if(root==NULL){
		printf("value not found.\n");
		return;
	}

	++currentVersion;
	tnode = findPredecessor(root);

	if(tnode == NULL){
		if(root->back != NULL && root->back->val > root->val)
			if(root->modTag == RIGHT)
				update(root->back,root->Mod.next,tree,LEFT);
			else
				update(root->back,root->right,tree,LEFT);
		else{
			if(root->modTag == RIGHT)
				update(root->back,root->Mod.next,tree,RIGHT);
			else
				update(root->back,root->right,tree,RIGHT);
		}
	}
	else{
		temp = createTree();
		if(root->modTag == LEFT)
			temp->R->root = root->Mod.next;
		else
			temp->R->root = root->left;

		back = temp->R->root->back;
		temp->R->root->back = NULL;

		if(tnode->modTag == LEFT){
			update(tnode->back,tnode->Mod.next,temp,RIGHT);
		}
		else{
			update(tnode->back,tnode->left,temp,RIGHT);
		}

		tnode2 = createNode(tnode->val);
		if(root->modTag == EMPTY || root->modTag == LEFT)
			tnode2->right = root->right;
		else
			tnode2->right = root->Mod.next;

		tnode2->left = temp->R->root;
		if(temp->R->root != NULL) temp->R->root->back = back;

		free(temp->R);
		free(temp);

		if(root->back != NULL && root->back->val > root->val)
			update(root->back,tnode2,tree,LEFT);
		else
			update(root->back,tnode2,tree,RIGHT);
	}
}

void inorder(Tnode* root,int version){
	if(root == NULL)
		return;

	if(root->modTag == LEFT && root->Mod.version <= version)
		inorder(root->Mod.next,version);
	else
		inorder(root->left,version);

	printf("%d ", root->val);

	if(root->modTag == RIGHT && root->Mod.version <= version)
		inorder(root->Mod.next,version);
	else
		inorder(root->right,version);
}

void printInOrder(Tree* tree,int version){
	Root* R;
	R = tree->R;
	while(R->vlow > version && R!=NULL){
		R = R->next;
	}

	if(R == NULL){
		printf("invalid version\n");
	}

	inorder(R->root,version);
	printf("\n");
}

void postorder(Tnode* root,int version){
	if(root == NULL)
		return;

	if(root->modTag == LEFT && root->Mod.version <= version){
		postorder(root->Mod.next,version);
//		printf("mod left ");
	}
	else{
		postorder(root->left,version);
//		printf("static left\n");
	}

	if(root->modTag == RIGHT && root->Mod.version <= version){
		postorder(root->Mod.next,version);
//		printf("mod right\n");
	}
	else{
		postorder(root->right,version);
//		printf("static right\n");
	}

	printf("%d ", root->val);
}

void printPostOrder(Tree* tree,int version){
	Root* R;
	R = tree->R;
	while(R->vlow > version && R!=NULL){
		R = R->next;
	}

	if(R == NULL){
		printf("invalid version\n");
	}

	postorder(R->root,version);
	printf("\n");
}
