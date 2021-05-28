#include <bits/stdc++.h>
#include "node.hpp"

using namespace std;

template <typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {

public:
	/* define your data structure to represent a binary search tree (bst) */
	vector<Node<T>*> tree;
	Node<T>* root;

	/* test1 */
	BST(); // the contructor function.
	~BST(); // the destructor function.
	size_t num_vertices(); // returns the total number of vertices in the bst.
	size_t num_edges(); // returns the total number of edges in the bst.
	T sum_weight(); // return the total weight of all the vertices in the bst.

	/* test2 */
	void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
	bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.

	/* test3 */
	vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
	vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
				     //     Leaves are the vertices that do not have any children in the bst.

	/* test4 */
	bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.

	/* test5 */
	vector<pair<string, string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.

	/* test6 */
	vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
	size_t degree(const string&); // returns the degree of a vertex.

	/* test7 */
	vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.

/* test8 */
	vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.

	/* test9 */
	vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.

	/* test10 */
	vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.

	/* test11 */
	vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
							    //     A path should include the source and destination vertices at the begining and the end, respectively.

	/* test12 */
	vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
				       //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

	/* test13 */
	size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

	/* test14 */
	void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.

private:
	Node<T>* insert_vertex(Node<T>*, const string&, const T&, Node<T>*);	//	Inserts a vertex from Node<T>* root, with a string and T weight and parent it to Node<T>*.
	T find_vertex_weight(const string& u);									//	Finds the corresponding T weight of Node<T>* u.
	Node<T>* search_vertex(Node<T>*, const string&, const T&);				//	Finds the corresponding Node<T>* of u, according to it's weight.

	void preorder_traversal_recursive(Node<T>*, vector<string>&);			//	Recursive method for Test 7.
	void inorder_traversal_recursive(Node<T>*, vector<string>&);			//	Recursive method for Test 8.
	void postorder_traversal_recursive(Node<T>*, vector<string>&);			//	Recursive method for Test 9.
	void delete_vertex(Node<T>*);											//	Delete's Node<T>*.
	Node<T>* find_min(Node<T>*);											//	Finds the left-most child from Node<T>*.
};

template <typename T>
Node<T>* BST<T>::insert_vertex(Node<T>* root, const string& u, const T& w, Node<T>* parent) {
	if (!root) {												//	If the recursive call has found an empty Node<T>*
		root = new Node<T>(u, w, parent);						//	Then we add a new Node<T>* to the vacant spot.
		this->tree.push_back(root);								//	
	} else if (root->weight > w) {								//	If the weight of the Node<T>* we want to add is smaller than the current root
		root->left = insert_vertex(root->left, u, w, root);		//	then we want to keep searching for a vacancy in the root's left children.
	} else if (root->weight <= w) {								//	Otherwise, if the weight of the Node<T>* we want to add is larger than the current root
		root->right = insert_vertex(root->right, u, w, root);	//	Then we want to keep searching for a vacancy in the root's right children.
	}

	return root;												//	After inserting a new Node<T>, it will set the new node's parent's left or right to the newly added node.
}

template <typename T>
T BST<T>::find_vertex_weight(const string& u) {
	for (auto& n : this->tree)			//	Linearly goes through every Node<T>*.
		if (n->node == u)				//	If the desired Node<T>* is found,
			return n->weight;			//	then we return it's weight.
	return -1;
}

template <typename T>
Node<T>* BST<T>::search_vertex(Node<T>* root, const string& u, const T& weight) {
	if (!root) { return nullptr; }

	if (root->weight == weight) {				//	If Node<T>* of u is found.
		return root;
	} else if (root->weight > weight) {
		return search_vertex(root->left, u, weight);	//	Search the left child if the root weight is larger than Node<T>* u's weight.
	} else {
		return search_vertex(root->right, u, weight);	//	Search the right child if the root weight is smaller than Node<T>* u's weight.
	}
}

/* test1 */

template <typename T>
BST<T>::BST() {
	tree = vector<Node<T>*>();	//	New vector of Node<T>.
	root = nullptr;				//	Initialise the root as a nullptr.
}

template <typename T>
BST<T>::~BST() {
	this->tree.clear();			//	Clears the memory of the vector of nodes.
}

template <typename T>
size_t BST<T>::num_vertices() {
	return this->tree.size();	//	The size of the vector of nodes is the number of vertices.
}

template <typename T>
size_t BST<T>::num_edges() {
	size_t ans = 0;

	for (auto& n : this->tree) {	//	Go through every Node<T>*.
		if (n->left)  { ans++; }	//	If it has a left, add one.
		if (n->right) { ans++; }	//	If it has a right, add one.
	}

	return ans;
}

template <typename T>
T BST<T>::sum_weight() {
	T ans = 0;

	for (auto& n : this->tree)	//	Go through every Node<T>*.
		ans += n->weight;		//	Append the T weight to the T answer.

	return ans;
}

/* test2 */

template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
	if (!root) {								//	If there is no root Node<T>*.
		root = new Node<T>(u, w, nullptr);		//	Add a new root Node<T>*.
		this->tree.push_back(root);				//	Add it to the vector<Node<T>*>.
	} else {
		insert_vertex(root, u, w, root);		//	Otherwise, simply insert a new Node<T>*.
	}
}

template <typename T>
bool BST<T>::contains(const string& u) {
	return search_vertex(root, u, find_vertex_weight(u)) != nullptr;	//	A Node<T> does not exist if search_vertex returns nullptr.
}

/* test3 */

template <typename T>
vector<string> BST<T>::get_vertices() {
	vector<string> vertices;

	for (auto& n : this->tree)			//	Every Node<T> in the vector of nodes.
		vertices.push_back(n->node);	//	

	return vertices;
}

template <typename T>
vector<string> BST<T>::get_leaves() {
	vector<string> leaves;

	for (auto& n : this->tree)				//	A Node<T>* is a leaf Node<T>*
		if (!n->left && !n->right)			//	if it has no left or right child.
			leaves.push_back(n->node);		//

	return leaves;
}

/* test4 */

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
	return search_vertex(root, u, find_vertex_weight(u))->is_adj(v);		//	If Node<T> u is adjacent to Node<T> v.
}

/* test5 */

template <typename T>
vector<pair<string, string>> BST<T>::get_edges() {
	vector<pair<string, string>> edges;

	for (auto& n : this->tree) {
		if (n->left)  { edges.push_back(make_pair(n->node, n->left->node)); }		//	If this Node<T>* has a left, add it to the edges vector.
		if (n->right) { edges.push_back(make_pair(n->node, n->right->node)); }		//	If this Node<T>& has a right, add it to the edges vector.
	}

	return edges;
}

/* test6 */

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
	vector<string> neighbours;
	Node<T>* node_u = search_vertex(root, u, find_vertex_weight(u));		//	Find the desired Node<T>*.

	if (node_u->left)   { neighbours.push_back(node_u->left->node); }		//	If node_u has a left or right child,
	if (node_u->right)  { neighbours.push_back(node_u->right->node); }		//	add it to the neighbours vector.
	if (node_u->parent) { neighbours.push_back(node_u->parent->node); }		//	If this node has a parent, add it to the neighbours vector.

	return neighbours;
}

template <typename T>
size_t BST<T>::degree(const string& u) {
	return search_vertex(root, u, find_vertex_weight(u))->degree();			//	Check the degree of Node<T> u.
}

/* test7 */

template <typename T>
void BST<T>::preorder_traversal_recursive(Node<T>* root, vector<string>& pot) {
	if (!root) { return; }

	pot.push_back(root->node);							//	Add the current node to the answer.
	preorder_traversal_recursive(root->left, pot);		//	Visit this Node<T>*'s left children.
	preorder_traversal_recursive(root->right, pot);		//	Visit this Node<T>*'s right children.
}

template <typename T>
vector<string> BST<T>::preorder_traversal() {
	vector<string> pre_trav;
	preorder_traversal_recursive(root, pre_trav);		//	Call pre-order traversal recursively.

	return pre_trav;
}

/* test8 */

template <typename T>
void BST<T>::inorder_traversal_recursive(Node<T>* root, vector<string>& iot) {
	if (!root) { return; }

	inorder_traversal_recursive(root->left, iot);		//	Visit this Node<T>*'s left children first.
	iot.push_back(root->node);							//	Add the current node to the answer.
	inorder_traversal_recursive(root->right, iot);		//	Visit this Node<T>*'s right children.
}

template <typename T>
vector<string> BST<T>::inorder_traversal() {
	vector<string> in_trav;
	inorder_traversal_recursive(root, in_trav);			//	Call in-order traversal recursively.

	return in_trav;
}

/* test9 */

template <typename T>
void BST<T>::postorder_traversal_recursive(Node<T>* root, vector<string>& pot) {
	if (!root) { return; }

	postorder_traversal_recursive(root->left, pot);		//	Visit this Node<T>*'s left children first.
	postorder_traversal_recursive(root->right, pot);	//	Then this Node<T>*'s right children.
	pot.push_back(root->node);							//	Then add the current node to the answer.
}

template <typename T>
vector<string> BST<T>::postorder_traversal() {
	vector<string> post_trav;
	postorder_traversal_recursive(root, post_trav);		//	Call post-order traversal recursively.

	return post_trav;
}

/* test10 */

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
	vector<string> bfs;

	queue<Node<T>*> q_bfs;
	q_bfs.push(root);												//	Start the BFS at the root Node<T>*.

	while (!q_bfs.empty()) {
		Node<T>* node_front = q_bfs.front();						//	Update the front Node<T>* in the queue.
		q_bfs.pop();												//	

		bfs.push_back(node_front->node);							//	Add the queue's front to the answer.

		if (node_front->left) { q_bfs.push(node_front->left); }		//	If the front node has a left, add it to the queue.

		if (node_front->right) { q_bfs.push(node_front->right); }	//	If the front node has a right, add it to the queue.
	}

	return bfs;
}

/* test11 */

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v) {
	vector<string> path;

	Node<T>* node_begin = search_vertex(root, u, find_vertex_weight(u));		//	Starting node.
	Node<T>* node_target = search_vertex(root, v, find_vertex_weight(v));		//	Destination node.
	path.push_back(node_begin->node);

	while (node_begin != node_target) {
		vector<string> pre_trav;									//	Call a pre-order traversal on the starting node.
		preorder_traversal_recursive(node_begin, pre_trav);			//	
		if (find(pre_trav.begin(), pre_trav.end(), node_target->node) != pre_trav.end()) {		//	If the pre-order traversal found the destination node.

			if (node_target->weight < node_begin->weight) {										//	Check if the target node is left of the starting node.
				path.push_back(node_begin->left->node);											//	Add it to the answer.
				node_begin = node_begin->left;													//	Update the new starting node and continue pathfinding.
			} else {																			//	Check if the target node is right of the starting node.
				path.push_back(node_begin->right->node);										//
				node_begin = node_begin->right;													//
			}
		} else {																				//	If the pre-order traversal cannot find the destination node.
			path.push_back(node_begin->parent->node);											//	Add the starting node's parent to the answer and update
			node_begin = node_begin->parent;													//	the starting node to it's parent and traverse again/
		}
	}

	return path;
}

/* test12 */

template <typename T>
vector<string> BST<T>::path_with_largest_weight() {
	vector<string> largest_weight_path;

	T weight_of_path = -1;
	for (auto& node_begin : this->tree) {														//	Loop through every node in this tree and make a path.
		for (auto& node_destination : this->tree) {												//	If the path's weight is greater than the current largest path
			if (node_begin == node_destination) { continue; }									//	then update the largest path.

			vector<string> current_path = path(node_begin->node, node_destination->node);		//	Draw a normal path between the starting node and the destination node.

			T current_weight = 0;																//	
			for (auto& path_node : current_path)												//	For each node in the path, find its weight
				current_weight += find_vertex_weight(path_node);								//	and add it to the total T weight.

			if (current_weight > weight_of_path) {												//	Update the largest weight if this path's total weight is
				weight_of_path = current_weight;												//	larger than the previous weight.
				largest_weight_path = current_path;												//	Update the largest weight path.
			}
		}
	}

	return largest_weight_path;
}

/* test13 */

template <typename T>
size_t BST<T>::height() {
	size_t tree_height = 0;

	vector<string> leaves = this->get_leaves();			//	A height is the maximum size of the path
														//	between the root node and each leaf node.
	for (auto& leaf : leaves) {							//	
		size_t size = path(leaf, root->node).size();	//	Draw a path between the leaf and the root
														//	
		if (size > tree_height)							//	If the size of the path exceeds the current
			tree_height = size;							//	maximum, update it.
	}

	return tree_height - 1;								//	Return the size of the largest path - 1.
}

/* test14 */

template <typename T>
void BST<T>::delete_vertex(Node<T>* node) {
	for (int i = 0; i < this->tree.size(); ++i) {
		if (this->tree[i] == node) {
			this->tree.erase(this->tree.begin() + i);
			return;
		}
	}

	delete node;
}

template <typename T>
Node<T>* BST<T>::find_min(Node<T>* root) {	//	Find the Node<T>* root's left-most child.
	while (root->left)
		root = root->left;

	return root;
}

template <typename T>
void BST<T>::remove_vertex(const string& u) {
	Node<T>* node_u = search_vertex(root, u, find_vertex_weight(u));	//	The Node<T>* to remove.
	size_t node_degree = node_u->degree();

	if (node_degree == 1) {
		(node_u->is_left() ? node_u->parent->left : node_u->parent->right) = nullptr;	//	If this node is left of its parent, set the parent's left to null. Vice versa.
	} else if (node_degree == 2) {
		if (root == node_u) {								//	Delete Node<T>* root.
			Node<T>* node_temp = find_min(node_u->right);	//	Find left most element on right child.

			root = node_temp;								//	The left most element is the new root.
			node_u->left->parent = root;					//	The original root's left parent is now the new root.
			root->left = node_u->left;						//	The new root's left Node<T>* is the original root's left Node<T>*.
		} else {
			(node_u->left ? node_u->left->parent : node_u->right->parent) = node_u->parent;		//	If the node_u has a left, set its parent to node_u's parent instead of node_u.

			if (node_u->is_left())																//	If node_u is on the left of it's parent.
				node_u->parent->left  = (node_u->left) ? node_u->left : node_u->right;			//	Set node_u's parent's left child to node_u's left or right.
			else																				//	If node_u is on the righ of it's parent.
				node_u->parent->right = (node_u->left) ? node_u->left : node_u->right;			//	Set node_u's parent's right child to node_u's left or right.
		}
	} else if (node_degree == 3) {
		Node<T>* min_node_right = find_min(node_u->right);

		(node_u->is_left() ? node_u->parent->left : node_u->parent->right) = min_node_right;		//	Set node_u's parent's left or right child to the minimum node on the right.

		min_node_right->left = node_u->left;			//	Swap the left most-element on the right with the node to remove			//	Set the left of the minimum node to node_u's left.
		node_u->left->parent = min_node_right;			//	then update the child elements and their parents to suit				//	Set node_u's left's parent to the new minimum node.
		min_node_right->parent = node_u->parent;		//	the removal and maintain the binary search tree.						//	Set the minimum node's parent to node_u's parent.
	}

	delete_vertex(node_u);
}
