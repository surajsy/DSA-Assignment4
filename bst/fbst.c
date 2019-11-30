#include "fbst.h"

int currentVersion;

Root* createRoot(){
	Root *R;
	R = ALLOC(Root);
	R->vhi = currentVersion;
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
	return newNode;
}

void postCopy(Tnode* tRoot,Tnode *root,Tree *tree){
	tnode *tnode;

	if(root == NULL)
		return;

	tnode = createNode(root->val);
	if(tRoot == NULL)
		tree->R->root = tnode;
	else if(tRoot->val > root->val)
		tRoot->left = tnode;
	else
		tRoot->right = tnode;
	postCopy(tnode,root->left,tree);
	postCopy(tnode,root->right,tree);
}

void copyTree(Tnode *root,Tree *tree){
	Root *R;

	R = createRoot();
	R->next = tree->R;
	tree->R = R;
	postCopy(tree->R->root,root);
}

void insert(int val,Tree* tree,int version){
	Tnode *tnode, *leaf, *root;
	Root *R;
	R = tree->R;

	while(R!=NULL && R->vhi != version){
		R = R->next;
	}

	if(R==NULL){
		printf("invalid version\n");
		return
	}
	++currentVersion;
	root = R->root;
	root = copyTree(root,tree);
	tnode = NULL;
	while(root!=NULL){
		tnode = root;
		if(val > root->val)
			root = root->right;
		else if(val < root->val)
			root = root->left;
		else{
			printf("value already in the tree. cannot insert\n");
			return;
		}
	}

	leaf = createNode(val);
	if(tnode == NULL)
		tree->R->root = leaf;
	else if(leaf->val > tnode val)
		tnode->right = leaf;
	else
		tnode->left = leaf;
}

