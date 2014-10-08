
//hila
extern float maxnode;
extern int size ;
extern Tour* firstrace;

class tree 
{
	public:
	tree* left;
	tree* right;

	float key;

	Tour* nodeTour;

	tree(float k,Tour* t){
		key = k;
		nodeTour = t;
		left =right = 0;

	}

};

void stash (tree* t);
tree* deletemaxnode(tree* bst);
tree* insert(tree* bst, Tour* t, float k);
float best (tree* t);
