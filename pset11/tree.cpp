//Include the following line at the top of your every source file with your name signed.
//On my honour, I pledge that I have neither received nor provided improper assistance in the
//completion of this assignment.
//Signed: MinJi Kim Student Number: 21600069
/**
* File: tree.cpp, tree.h
* implements a binary tree and/or binary search tree(BST).* and
* AVL(Adelson-Velskii and Landis) tree.
*
* A binary search tree BST is a type of binary tree where the nodes
* are arranged in order: for each node, all elements in its left
* subtree are less to to node and all the elements in its right
* subtree are greater than the node. Many operations are the same
* either in a binary tree or in a binary search tree.
*
* - Some functions work for a binary tree and/or for a BST.
* - The code works on the node structure 'tree' that makes up the tree.
* - The algorithm, typically recursive, that iterates over the tree
* - Using a pointer to a pointer as an argument have been avoided.
*   Instead the function is to return a new root node after an
*   insertion or deletion, then it returns the root node as a
*   returned value.
*
* 04/20/2014	Creation	Youngsup Kim, idebtor@gmail.com
* 04/15/2016	treeprint() added for clearer visualization of tree
* 05/01/2016	Added AVL tree
* 10/20/2016    Switching from/to BST and AVL tree
* 04/02/2019	C++ version, utilized stl::vector and stl::queue partially
*
* Usage:
*	tree root = nullptr;
*   root = insert(root, 5); // the first node is created
*                           // it becomes the root
*   root = insert(root, 7); // a new node is added
*   root = trim(root, 5); // if first node is removed,
*                           // the new root is returned
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include "tree.h"
using namespace std;

void treeprint(tree t);        // print the tree on console graphically

// returns the degree of a node, not a tree
int degree(tree t) {
	int d = 0;
	if (t->left != nullptr) d++;
	if (t->right != nullptr) d++;
	return d;
}

// Compute the max depth of a tree. It is the number of nodes along
// the longest path from the root node down to the farthest leaf node.
// height: 0 (undefined) for empty tree, 1 for root only tree
int height(tree node) {
	if (empty(node)) return 0;
	// compute the depth of each subree and return the larger one.

	if ((node->left == nullptr) && (node->right == nullptr)) return 1;
	int lh = 0;
    lh = 1 + height(node->left);
    int rh = 0;
    rh = 1 + height(node->right);
    if(rh>lh) return rh;
    return lh;
}

// Computes the size of the binary tree dyamically by
// traversing the nodes recursively.
int size(tree node) {
	if (empty(node)) return 0;
	return 1+size(node->left)+size(node->right);
}

bool empty(tree t) {
	return t == nullptr;
}

int value(tree t) {
	if (!empty(t)) return t->key;
	return 0;
}

// frees all nodes while traversing the tree like postorder
tree clear(tree t) {
	if (empty(t)) return nullptr;

	if(t){
        clear(t->left);
        clear(t->right);
    DPRINT(cout << "<postorder key=" << t->key << endl;);
        delete t;
    }
    
	return nullptr;
}

// does there exist a node with given key?
// search a key in binary search tree(BST) recursively.
bool contains(tree node, int key) {
	if (empty(node)) return false;
    if (key  == node->key) return true;
    if (key < node->key)
        return contains(node->left, key);
    return contains(node->right, key);
}

// does there exist a node with given key?
// search a key in binary tree(BT) recursively.
bool containsBT(tree node, int key) {
	if (empty(node)) return false;
	if (key == node->key) return true;
	return containsBT(node->left, key) || containsBT(node->right, key);
}

// does there exist a key-value pair with given key?
// search a key in binary search tree(BST) iteratively
bool containsIteration(tree node, int key) {
	if (empty(node)) return false;
	while (node) {
		if (key == node->key) return true;
		node = key < node->key ? node->left : node->right;
	}
	return false;
}

// returns a node with a key given if found in BST, otherwise nullptr.
tree find(tree node, int key) {
	if (empty(node)) return nullptr;

	if (key == node->key) return node;
	if (key < node->key)
		return find(node->left, key);
	return find(node->right, key);
}

// returns a node with a key given if found in BT, otherwise nullptr.
tree findBT(tree t, int key) {
	if (empty(t)) return nullptr;

	if (key == t->key) {
		cout << "findBT key: " << t->key << endl;
		return t;
	}

	tree node = findBT(t->left, key);
	if (node != nullptr) return node;

	return findBT(t->right, key);
}

// Inserts a new node with the key in given binary tree and
// returns the new node such that client use it properly.
tree grow(tree node, int key) {
	DPRINT(cout << ">grow key=" << key << endl;);
	if (node == nullptr) return new TreeNode(key);

	if (key < node->key)	// recur down the tree
		node->left = grow(node->left, key);
	else if (key > node->key)
		node->right = grow(node->right, key);

	// do nothing, the duplicate key is not allowed
	DPRINT(cout << "<grow returns key=" << node->key << endl;);
	return node;    // eventually returns the original root node
}

///////////////////////////////////////////////////////////////////
// trim
///////////////////////////////////////////////////////////////////
// removes the node with the key in a tree and returns the new root
tree trim(tree node, int key) {
	if (empty(node)) return node;	 // base case
	DPRINT(cout << ">trim: now we are at: " << node->key << endl;);

	if (key < node->key) // if node to trim is in left subtree.
		node->left = trim(node->left, key);
	else if (key > node->key) // node to trim is in right subtree.
		node->right = trim(node->right, key);
	else {
		if (node->left && node->right) {
			// get the successor: smallest in right subtree
			// copy the successor's content to this node
			// trim the successor recursively starting at root->right
			// root itself dose not change, but root->right may
            tree temp = succ(node);
            node->key = temp->key;
            node->right = trim(node->right,temp->key);
		}
		else if (node->left) {
			// delete root, pass back root->left
            tree temp = node->left;
            delete node;
            return temp;
            
		}
		else if (node->right) {
			// delete root, pass back root->right
			tree temp = node->right;
            delete node;
            return temp;
		}
		else {
			delete node;
			return nullptr;
		}
	}

	DPRINT(if (node != nullptr) cout << "<trim returns: key=" << node->key << endl;);
	DPRINT(if (node == nullptr) cout << "<trim returns: nullptr)\n";);
	return node;
}

// removes the node with the key in a tree and returns the new root
tree trimplus(tree node, int key) {
	if (empty(node)) return node;	 // base case
	DPRINT(cout << ">trimplus: now we are at: " << node->key << endl;);

	if (key < node->key) // if node to trim is in left subtree.
        node->left = trimplus(node->left, key);
    else if (key > node->key) // node to trim is in right subtree.
        node->right = trimplus(node->right, key);
    else {
        if (node->left && node->right) {
            // get the successor: smallest in right subtree
            // copy the successor's content to this node
            // trim the successor recursively starting at root->right
            // root itself dose not change, but root->right may
            if(height(node->left) <= height(node->right)){
                DPRINT(cout << "here" << node->key << endl;);
                tree temp = succ(node);
                node->key = temp->key;
                node->right = trimplus(node->right,temp->key);
            }
            else{
                tree temp = pred(node);
                node->key = temp->key;
                node->left = trimplus(node->left,temp->key);
            }
            
        }
        else if (node->left) {
            // delete root, pass back root->left
            tree temp = node->left;
            delete node;
            return temp;
            
        }
        else if (node->right) {
            // delete root, pass back root->right
            tree temp = node->right;
            delete node;
            return temp;
        }
        else {
            delete node;
            return nullptr;
        }
    }

	DPRINT(if (node != nullptr) cout << "<trimplus returns: key=" << node->key << endl;);
	DPRINT(if (node == nullptr) cout << "<trimplus returns: nullptr)\n";);
	return node;
}

// returns a successor of the tree
tree succ(tree node) {
	if (node != nullptr && node->right != nullptr)
		return minimum(node->right);
	return nullptr;
}

// returns a predeccessor of the tree
tree pred(tree node) {
	if (node != nullptr && node->left != nullptr)
		return maximum(node->left);
	return nullptr;
}

// Given a binary search tree, return the min or max key in the tree.
// Don't need to traverse the entire tree.
tree maximum(tree node) {			// returns max node
    while(node->right != nullptr){
        node = node->right;
    }
	return node;
}

tree minimum(tree node) {			// returns min node
	 while(node->left != nullptr){
           node = node->left;
       }
	return node;
}




// Given a binary tree, its node values in postorder are passed
// back through the argument v which is passed by reference.
void postorder(tree node, vector<int>& v) {
    if(node){
        DPRINT(cout << ">postorder size=" << v.size() << endl;);
        postorder(node->left,v);
        postorder(node->right,v);
        v.push_back(node->key);
        DPRINT(cout << "<postorder key=" << node->key << endl;);
    }
}

// Given a binary tree, its node values in preorder are passed
// back through the argument v which is passed by reference.
void preorder(tree node, vector<int>& v) {
    if(node){
        DPRINT(cout << ">preorder size=" << v.size() << endl;);
        v.push_back(node->key);
        preorder(node->left, v);
        preorder(node->right, v);
        DPRINT(cout << "<preorder key=" << node->key << endl;);
    }
}

// Given a binary tree, its nodes in level-order is passed
// back through the argument v which is passed by reference.
// Use std::queue to store the nodes during traverse the tree.
void levelorder(tree node, vector<int>& v) {
	DPRINT(cout << ">levelorder";);
    queue<tree> q;
	if (node == nullptr) return;
    
    q.push(node);
    //v.push_back(q.front()->key);
    
    while(true){
        DPRINT(cout << "here";);
       
        if(q.empty()) break;
        else{
            if(q.front()->left && q.front()->right){
                q.push(q.front()->left);
                q.push(q.front()->right);
                v.push_back(q.front()->key);
                q.pop();
            }
            else if(q.front()->left){
                q.push(q.front()->left);
                v.push_back(q.front()->key);
                q.pop();
            }
            else if(q.front()->right){
                q.push(q.front()->right);
                v.push_back(q.front()->key);
                q.pop();
            }
            else {
                v.push_back(q.front()->key);
                q.pop();
            }
        }
        
    }
	DPRINT(cout << "<levelorder size=" << v.size() << endl;);
}

// does this binary tree satisfy symmetric order?
// is the tree rooted at x a BST with all keys between min and max?
// Another solution: Do an inorder traversal of the tree and store
// the node values in a container. If it is in sorted order,
// its a valid BST otherwise not.
bool _isBST(tree x, int min, int max) {
	if (empty(x)) return true;
	//DPRINT(cout << ">_isBST key=" << x->key << "\t min=" << min << " max=" << max << endl;);
    stack<tree> s;
    int container[size(x)];
    int count = 0;
    
      while (x != nullptr || s.empty() == false)
      {
          while (x !=  nullptr)
          {
              s.push(x);
              x = x->left;
          }
          x = s.top();
          s.pop();
    
         container[count] = x->key;
         count++;
          
          x = x->right;
      }
    
    for(int i = 0; i < count-1; i++){
        if(container[i]>container[i+1]){
            return false;
        }
        else continue;
    }
    //DPRINT(cout << "<_isBST key=" << x->key << "\t min=" << min << " max=" << max << endl;);
    return true;

	
	//return false;
}

// returns true if the tree is a binary search tree, otherwise false.
bool isBST(tree root) {
	if (empty(root)) return true;
	bool result = _isBST(root, minimum(root)->key, maximum(root)->key);    // an alternative
	return result;
}

///////////   testing code  ///////////////////////////////////////
// While doing Inorder traversal, we can keep track of previously
// visited node. If the value of the currently visited node is
// less than the previous value, then tree is not BST.
bool _isBSTinOrder(tree root, tree *prev) {
	// traverse the tree in inorder fashion and keep track of prev node
	if (empty(root)) return true;

	if (!_isBSTinOrder(root->left, prev)) return false;

	// Allows only distinct valued nodes
	if (*prev != nullptr && root->key <= (*prev)->key) return false;
	*prev = root;
	return _isBSTinOrder(root->right, prev);
}

bool isBSTinOrder(tree root) {
	tree prev = nullptr;
	return _isBSTinOrder(root, &prev);
}
///////////////////////////////////////////////////////////////////


///////////////// stress test - insert, trim ////////////////////
// shuffles an int array contents
void shuffle(int* arr, int N) {
	DPRINT(cout << ">shuffle N=" << N << endl;);
	if (N <= 1) return;
	DPRINT(srand(0));    // for the same sequence of rand() for debugging
	for (int i = 0; i < N; i++) {
		int x = rand() % (N - 1);
		int t = arr[i];
		arr[i] = arr[x];
		arr[x] = t;
	}
	DPRINT(cout << "<shuffled" << endl;);
}

// returns an int array that has randomly mixed numbers
// between start to start + N
void randomN(int* arr, int N, int start) {
	DPRINT(cout << ">random N=" << N << endl;);
	for (int i = 0; i < N; i++)
		arr[i] = start + i;
	shuffle(arr, N);

#ifdef DEBUG
	cout << "randomN: ";
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	printf("\n");
#endif
	DPRINT(cout << "<random" << endl;);
}

// inserts N numbers of keys in the tree(AVL or BST), based
// on the current menu status.
// If it is empty, the key values to add ranges from 0 to N-1.
// If it is not empty, it ranges from (max+1) to (max+1 + N).
tree growN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">growN N=" << N << endl;);
	int start = empty(root) ? 0 : value(maximum(root)) + 1;

	int* arr = new (nothrow) int[N];
	assert(arr != nullptr);
	randomN(arr, N, start);

	// using a function pointer
	/*tree(*func)(tree root, int key) = AVLtree ? growAVL : grow;
	for (int i = 0; i < N; i++)
		root = func(root, arr[i]);

	delete[] arr;
	DPRINT(cout << "<growN size=" << size(root) << endl;);
	return root;*/
    
    for (int i = 0; i < N; i++) root = grow(root, arr[i]);
    if (AVLtree) root = rebalanceTree(root);
    delete[] arr;
    return root;

}

// removes randomly N numbers of nodes in the tree(AVL or BST).
// It gets N node keys from the tree, trim one by one randomly.
tree trimN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">trimN N=" << N << endl;);
	vector<int> vec;
	inorder(root, vec);
	shuffle(vec.data(), (int) vec.size());

	int tsize = size(root);
	assert(vec.size() == tsize);   // make sure we've got them all

	int count = N > tsize ? tsize : N;

	// use function pointers
	/*tree (*func)(tree root, int key) = AVLtree ? trimAVL : trim;
	for (int i = 0; i < count; i++)
		root = func(root, vec[i]);

	DPRINT(cout << "<trimN size=" << size(root) << endl;);
	return root;*/
    
    
    for (int i = 0; i < count; i++)
        root = trim(root, vec[i]);
    
    if (AVLtree) root = rebalanceTree(root);
    return root;
}

////////////////////////// AVL Tree ///////////////////////////////
bool balanced(tree node) {
	int factor = balanceFactor(node);
	return (factor >= -1 && factor <= 1) ? true : false;
}

// returns the balance factor or (height of left - height of right)
int balanceFactor(tree node) {
	DPRINT(cout << " bf" << endl;);
	if (empty(node)) return 0;
	int left = height(node->left);
	int right = height(node->right);
	DPRINT(cout << " bf at(" << node->key << "): " << (left - right)
		        << "\t (l=" << left << ", " << "r= " << right << ") \n";);
	return left - right;
}

// returns true if the tree is AVL tree.
// this is a helper function for isAVL().
bool _isAVL(tree root) {
	if (!balanced(root)) return false;
	if (root->left != nullptr && !_isAVL(root->left))  return false;
	if (root->right != nullptr && !_isAVL(root->right)) return false;
	return true;
}
bool isAVL(tree root) {
	if (root == nullptr) return true;
	if (!isBST(root)) return false;
	return _isAVL(root);
}

tree rotateLL(tree node) {
	DPRINT(cout << "\t[LL]case at " << node->key << endl;);
	tree child = node->left;
	node->left = child->right;
	child->right = node;
	return child;
}

tree rotateRR(tree node) {
	DPRINT(cout << "\t[RR]case at " << node->key << endl;);
	tree child = node->right;
	node->right = child->left;
	child->left = node;
	return child;
}

tree rotateLR(tree node) {
	DPRINT(cout << "\t[LR]case at " << node->key << endl;);
	tree child = node->left;
	node->left = rotateRR(child);
	return rotateLL(node);
}

tree rotateRL(tree node) {
	DPRINT(cout << "\t[RL]case at " << node->key << endl;);
	tree child = node->right;
	node->right = rotateLL(child);
	return rotateRR(node);
}

// rebalnces at the node only, not recursively, and
// returns the node that may be different from the input node
tree rebalance(tree node) {
	DPRINT(cout << ">rebalance at:" << node->key << endl;);

    int bf = balanceFactor(node);
    
    if(bf >= 2){
        if(balanceFactor(node->left) >= 1)
            node = rotateLL(node);
        else
            node = rotateLR(node);
    }
    else if(bf <= -2){
        if(balanceFactor(node->right) <= -1)
            node = rotateRR(node);
        else
            node = rotateRL(node);
    }

#ifdef DEBUG
	treeprint(node);
	cout << " Need rebalancing at " << node->key << endl;
#endif

	//cout << "your code here\n";

	DPRINT(cout << "<rebalance returning" << endl;);
	return node;
}



// rebalances AVL tree at the root just once;
// It finds the first unbalanced node and invokes rebalance() at that node.
// You may have to repeat this process as necessary to change a binary
// search to into a valid AVL tree
tree _rebalanceTree(tree node) {
	if (empty(node)) return nullptr;

	if (balanced(node)) {
		node->left = _rebalanceTree(node->left);
		node->right = _rebalanceTree(node->right);
		return node;
	}
	DPRINT(cout << " Found 1st unbalanced node at " << node->key << endl;);
	node = rebalance(node);
	return node;
}

// rebuilds an AVL tree with a list of keys sorted.
// v – an array of keys sorted, n – the array size
tree buildAVL (int* v, int n) {
    if (n <= 0) return nullptr;
    // create a new root and set a TreeNode and initial values, use the [mid] element of v.
    int mid = n/2;
    tree root = new TreeNode(v[mid]);
    
    // your code here – recursive buildAVL() calls for left & right
     // from 0 to mid-1 (or mid number of nodes)
    // from mid+1 to the end (how many nodes?)
    root->left = buildAVL(v,mid);
    root->right = buildAVL(&v[mid+1], n-mid-1);
    
    return root;
}

// Given a binary tree, its node values in inorder are passed
// back through the argument v which is passed by reference.
void inorder(tree node, vector<int>& v) {
    if(node){
        DPRINT(cout << ">inorder size=" << v.size() << endl;);
        inorder(node->left,v);
        v.push_back(node->key);
        inorder(node->right,v);
        DPRINT(cout << "<inorder key=" << node->key << endl;);
    }
}

void inorder(tree node, vector<tree>& v) {
    if(node){
        DPRINT(cout << ">inorder size=" << v.size() << endl;);
        inorder(node->left,v);
        v.push_back(node);
        inorder(node->right,v);
        DPRINT(cout << "<inorder key=" << node->key << endl;);
    }
}

tree buildAVL(tree* v, int n){
    if (n <= 0) return nullptr;


    int mid = n/2;
    tree root = v[mid];
    root->left = nullptr;
    root->right = nullptr;
    
    // your code here – recursive buildAVL() calls for left & right
     // from 0 to mid-1 (or mid number of nodes)
    // from mid+1 to the end (how many nodes?)
    root->left = buildAVL(v,mid);
    root->right = buildAVL(&v[mid+1], n-mid-1);
    return root;
}


// reconstructs a new AVL tree in O(n), Actually it is O(n) + O(n).
tree rebalanceTree(tree node) {
	DPRINT(cout << ">rebalanceTree " << endl;);
	if (node == nullptr) return nullptr;


    // you may use inorder() to get an array of keys or nodes.
    // if you use an array of nodes, you just reconstructs AVL tree using nodes.
    // if you use an array of keys, the root should be cleared (or deallocated).
    
    //while (!isAVL(node))                 // O(n) ~ O(n log n)
    //node = _rebalanceTree(node);
    
    vector<int> v;
    //vector<tree> v;
    v.clear();
    inorder(node, v);
    tree new_root = buildAVL(v.data(), (int)v.size());
    clear(node);
	DPRINT(cout << "<rebalanceTree " << endl;);
    return new_root;
}


// inserts a node in the AVL tree and rebalance it. O(log n)
tree growAVL(tree node, int key) {
	DPRINT(cout << ">growAVL key=" << key << endl;);
	if (node == nullptr) return new TreeNode(key);

    if (key < node->key){
        node->left = grow(node->left, key);
    }
        
    else if (key > node->key){
        node->right = grow(node->right, key);
    }
        
    
    // do nothing, the duplicate key is not allowed
    DPRINT(cout << "<grow returns key=" << node->key << endl;);
    return rebalance(node);

	//return nullptr;
}

// removes a node with key in the AVL tree and rebalance it.
tree trimAVL(tree node, int key) {
	DPRINT(cout << ">trimAVL key=" << key << " at " << node->key << endl;);

	// step 1 - BST trim as usual

	
    if (empty(node)) return node;     // base case
    DPRINT(cout << ">trim: now we are at: " << node->key << endl;);

    if (key < node->key) // if node to trim is in left subtree.
        node->left = trimAVL(node->left, key);
    else if (key > node->key) // node to trim is in right subtree.
        node->right = trimAVL(node->right, key);
    else {
        if (node->left && node->right) {
            // get the successor: smallest in right subtree
            // copy the successor's content to this node
            // trim the successor recursively starting at root->right
            // root itself dose not change, but root->right may
            tree temp = succ(node);
            node->key = temp->key;
            node->right = trimAVL(node->right,temp->key);
        }
        else if (node->left) {
            // delete root, pass back root->left
            tree temp = node->left;
            delete node;
            return temp;
            
        }
        else if (node->right) {
            // delete root, pass back root->right
            tree temp = node->right;
            delete node;
            return temp;
        }
        else {
            delete node;
            return nullptr;
        }
    }

	// step 2 - get rebalanced at this node
	DPRINT(if (node != nullptr)
		cout << "<trimAVL key=" << key << " is done, now rebalance at " << node->key << endl;);
	return rebalance(node);
}
