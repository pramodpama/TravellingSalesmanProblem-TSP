#include "genetic.h"
#include "bst.h"

float maxnode;
int size ;
Tour* firstrace;
int count = 1;

void killtour (Tour* t){
	delete(t->order);
	delete(t);
}


void updatemax (tree* t){
	if (t->right) updatemax(t->right);
	else maxnode = t->key;
}

tree* insert(tree* bst, Tour* t, float k){
	if(size == POP_SIZE && k >= maxnode)	{
		killtour(t);
		return bst;
	}

	if (size == POP_SIZE && k < maxnode) {
		bst = deletemaxnode(bst);
		updatemax(bst);
	}

	if (bst == 0) {
		if(k > maxnode) maxnode = k;
		size++;
		return new tree(k, t);
	}

	if (k == bst->key) {
		killtour(t);
		return bst;
	}

	if (k < bst->key) bst->left = insert (bst->left, t, k);
	else bst->right = insert (bst->right, t, k);
}



tree* deletemaxnode(tree* bst){
	if (bst->right) {
		bst->right = deletemaxnode (bst->right);
	}
	else {
		size--;
		tree* temp = bst->left;
		delete(bst->nodeTour->order);
		delete(bst->nodeTour);
		delete(bst);
		return temp;
	}
}

void stash (tree* t){
	if (t){
		stash(t->left);
		delete(t->left);

		stash(t->right);
		delete(t->right);

		firstrace[count++] = *(t->nodeTour);
		delete(t->nodeTour);
	}
}


float best (tree* t){
	if (t->left) return best(t->left);
	return t->key;
}