/*
 * Blocking Flow Link Cut Trees.cpp
 *
 *  Created on: 3 Feb 2021
 *      Author: Grant
 */

#include <iostream>
using namespace std;

int lowest_value = 100;
int total_flow = 0;

class Node
{
public:
	int data;
	int node_name;
	Node* parent = NULL;
	Node* left = NULL;
	Node* right = NULL;
};

class BinarySearchTree
{
public:
	BinarySearchTree* path_parent_tree = NULL;
	Node* path_parent = NULL;
	Node* root;
	int height;
};

class LinkCutTree
{
public:
	BinarySearchTree* root_tree;
};

int found = 0;

Node* discover(Node* node, int value)
{
	if (node->data == value)
	{
		//found = 1;
		return node;
	}
	else
	{
		if (value < node->data)
		{
			discover(node->left, value);
		}
		else
		{
			discover(node->right, value);
		}
	}
}

void rotate(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node->parent == NULL)
	{
		return;
	}

	Node* parent = node->parent;

	if (parent->left == node)
	{
		if (parent->parent != NULL)
		{
			Node* parent_parent = parent->parent;

			if (parent_parent->left == parent)
			{
				node->parent = parent_parent;
				parent_parent->left = node;
			}
			else
			{
				node->parent = parent_parent;
				parent_parent->right = node;
			}

			parent->left = node->right;
			if (node->right != NULL)
			{
				node->right->parent = parent;
			}

			node->right = parent;
			parent->parent = node;
		}
		else
		{
			//cout << "HERE";

			node->parent = NULL;

			parent->left = node->right;
			if (node->right != NULL)
			{
				node->right->parent = parent;
			}

			node->right = parent;
			parent->parent = node;

			tree->root = node;

			//cout << root->data;
		}
	}
	else
	{
		if (parent->parent != NULL)
		{
			Node* parent_parent = parent->parent;

			if (parent_parent->left == parent)
			{
				node->parent = parent_parent;
				parent_parent->left = node;
			}
			else
			{
				node->parent = parent_parent;
				parent_parent->right = node;
			}

			parent->right = node->left;
			if (node->left != NULL)
			{
				node->left->parent = parent;
			}

			node->left = parent;
			parent->parent = node;
		}
		else
		{
			node->parent = NULL;

			parent->right = node->left;
			if (node->left != NULL)
			{
				node->left->parent = parent;
			}

			node->left = parent;
			parent->parent = node;

			tree->root = node;
		}
	}
}

void splay(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node == root)
	{
		return;
	}

	if (node->parent == root)
	{
		rotate(tree, value);
		return;
	}
	else
	{
		Node* parent = node->parent;
		Node* parent_parent = node->parent->parent;

		if (parent_parent->left == parent && parent->left == node)
		{
			//cout << "HERE";

			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else if (parent_parent->right == parent && parent->right == node)
		{
			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else
		{
			int x = node->data;

			rotate(tree, x);
			rotate(tree, x);
		}
	}

	splay(tree, value);
}

void delete_splay(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node->parent == root)
	{
		node->left = root->left;
		node->parent = NULL;

		tree->root = node;
		return;
	}
	else
	{
		Node* parent = node->parent;
		Node* parent_parent = node->parent->parent;

		if (parent_parent->left == parent && parent->left == node)
		{
			//cout << "HERE";

			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else if (parent_parent->right == parent && parent->right == node)
		{
			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else
		{
			int x = node->data;

			rotate(tree, x);
			rotate(tree, x);
		}
	}

	splay(tree, value);
}

void Insert(BinarySearchTree* tree, Node* node, int depth, int node_name)
{
	Node* root = tree->root;

	/*
	if (node == NULL)
	{
		Node* n = new Node();
		n->data = value;
		node = n;
		cout << "HERE";
		return;
	}
	*/

	if (depth <= node->data)
	{
		if (node->left == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = depth;
			n->node_name = node_name;

			node->left = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->left, depth, node_name);
		}
	}
	else
	{
		if (node->right == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = depth;
			n->node_name = node_name;

			node->right = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->right, depth, node_name);
		}
	}
	return;
}

void find(BinarySearchTree* tree, Node* node, int value)
{
	if (node->data == value)
	{
		found = 1;
		splay(tree, value);
		return;
	}
	else
	{
		if (value < node->data)
		{
			find(tree, node->left, value);
		}
		else
		{
			find(tree, node->right, value);
		}
	}
}

void Delete(BinarySearchTree* tree, int value)
{
	//Node* root = tree->root;

	splay(tree, value);

	Node* root = tree->root;

	Node* r_minimum = tree->root->right;

	while (r_minimum->left != NULL)
	{
		r_minimum = r_minimum->left;
	}

	//cout << r_minimum->data;

	delete_splay(tree, r_minimum->data);
}

Node* search(BinarySearchTree* tree, Node* node, int value)
{
	if (node->data == value)
	{
		//found = 1;
		//splay(tree, value);
		return node;
	}
	else
	{
		if (value < node->data)
		{
			search(tree, node->left, value);
		}
		else
		{
			search(tree, node->right, value);
		}
	}
}

void join(BinarySearchTree* tree1, BinarySearchTree* tree2)
{
	int target_height = tree2->height - 1;

	//cout << "Tree Height " << target_height << endl;

	Node* parent_node = search(tree1, tree1->root, target_height);

	tree2->path_parent_tree = tree1;
	tree2->path_parent = parent_node;

	cout << parent_node->data << endl;
}

BinarySearchTree* access_tree = NULL;

void access(BinarySearchTree* tree, int v)
{
	splay(tree, v);

	cout << "Splay" << tree->root->data << endl;

	if (tree->root->right != NULL)
	{
		BinarySearchTree* new_tree = new BinarySearchTree();
		new_tree->height = tree->root->right->data;
		new_tree->root = tree->root->right;
		new_tree->root->parent = NULL;
		new_tree->path_parent = tree->root;
		new_tree->path_parent_tree = tree;

		tree->root->right = NULL;

		access_tree = new_tree;
	}

	Node* w = tree->path_parent;
	BinarySearchTree* w_tree = tree->path_parent_tree;
	//Node* v_node = tree->root;
	BinarySearchTree* v_tree = tree;

	//int r = 0;
	while (w != NULL)
	{
		splay(w_tree, w->data);

		BinarySearchTree* new_new_tree = new BinarySearchTree();
		new_new_tree->height = w_tree->root->right->data;
		new_new_tree->root = w_tree->root->right;
		new_new_tree->root->parent = NULL;
		new_new_tree->path_parent = w_tree->root;
		new_new_tree->path_parent_tree = w_tree;

		access_tree = new_new_tree;

		//w_tree->root->right = v_node;
		w_tree->root->right = v_tree->root;
		w_tree->root->right->parent = w_tree->root;
		v_tree->path_parent = NULL;;
		v_tree->path_parent_tree = NULL;

		splay(w_tree, w_tree->root->right->data);

		w = w_tree->path_parent;
		w_tree = w_tree->path_parent_tree;
		//v_node = w_tree->root;
		v_tree = w_tree;

		//r++;
	}
}

int findroot(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	access(target_tree, v);

	Node* current_node = base_tree->root;

	while (current_node->left != NULL)
	{
		current_node = current_node->left;
	}

	splay(base_tree, current_node->data);

	return base_tree->root->data;
}

int number_of_edges = 8;

int graph_edges[8][3] = {{ 0, 1, 2 }, { 0, 2, 2 }, { 0, 6, 1 }, { 1, 3, 2 }, { 2, 4, 2 }, { 3, 5, 1 }, { 4, 5, 1 }, { 6, 3, 1 }};

int first_edge = 100;
int second_edge = 100;
int last_accessed = 2;

int lowest_capacity_first_edge = 100;
int lowest_capacity_second_edge = 100;
int lowest_capacity = 100;

void inordertraversal(Node* current_node)
{
	if (current_node == NULL)
	{
		return;
	}

	inordertraversal(current_node->left);

	if (last_accessed == 2)
	{
		first_edge = current_node->node_name;
		last_accessed = 1;
	}
	else
	{
		second_edge = current_node->node_name;
		last_accessed = 2;
	}

	if (first_edge != 100 && second_edge != 100)
	{
		for (int i = 0; i < number_of_edges; i++)
		{
			if (graph_edges[i][0] == first_edge && graph_edges[i][1] == second_edge)
			{
				if (graph_edges[i][2] < lowest_capacity)
				{
					lowest_capacity_first_edge = graph_edges[i][0];
					lowest_capacity_second_edge = graph_edges[i][1];
					lowest_capacity = graph_edges[i][2];
				}
			}
		}

		for (int j = 0; j < number_of_edges; j++)
		{
			if (graph_edges[j][0] == second_edge && graph_edges[j][1] == first_edge)
			{
				if (graph_edges[j][2] < lowest_capacity)
				{
					lowest_capacity_first_edge = graph_edges[j][0];
					lowest_capacity_second_edge = graph_edges[j][1];
					lowest_capacity = graph_edges[j][2];
				}
			}
		}

	}

	cout << current_node->node_name << endl;

	inordertraversal(current_node->right);
}

void mincapacity(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	if (base_tree != target_tree)
	{
		access(target_tree, v);
	}

	inordertraversal(base_tree->root);
}

void inordertraversalsubtract(Node* current_node, int subtract_capacity)
{
	if (current_node == NULL)
	{
		return;
	}

	inordertraversalsubtract(current_node->left, subtract_capacity);

	if (last_accessed == 2)
	{
		first_edge = current_node->node_name;
		last_accessed = 1;
	}
	else
	{
		second_edge = current_node->node_name;
		last_accessed = 2;
	}

	if (first_edge != 100 && second_edge != 100)
	{
		for (int i = 0; i < number_of_edges; i++)
		{
			if (graph_edges[i][0] == first_edge && graph_edges[i][1] == second_edge)
			{
				graph_edges[i][2] = graph_edges[i][2] - subtract_capacity;
			}
		}

		for (int j = 0; j < number_of_edges; j++)
		{
			if (graph_edges[j][0] == second_edge && graph_edges[j][1] == first_edge)
			{
				graph_edges[j][2] = graph_edges[j][2] - subtract_capacity;
			}
		}

	}

	//cout << current_node->node_name << endl;

	inordertraversalsubtract(current_node->right, subtract_capacity);
}


void subtract(BinarySearchTree* base_tree, int subtract_capacity)
{
	first_edge = 100;
	second_edge = 100;
	last_accessed = 2;

	inordertraversalsubtract(base_tree->root, subtract_capacity);

	total_flow = total_flow + subtract_capacity;
}

void cut(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	access(target_tree, v);

	cout << base_tree->root->data << endl;

	base_tree->root->left->parent = NULL;
	base_tree->root->left = NULL;
}

void link(LinkCutTree* overall_tree, LinkCutTree* overall_tree1, BinarySearchTree* target_tree1, BinarySearchTree* target_tree2, int w, int v)
{
	access(target_tree2, v);
	access(target_tree1, w);

	target_tree1->path_parent_tree = target_tree2;

	Node* current_node = target_tree2->root;

	while (current_node->left != NULL)
	{
		current_node = current_node->left;
	}

	splay(target_tree1, current_node->data + 1); //Sets tree heights to ensure balance

	target_tree1->root->left->parent = NULL; //Deletes values shallower than the root
	target_tree1->root->left = NULL; //Deletes values shallower than the root

	target_tree1->path_parent = current_node;
}
// Driver code
int main()
{
	LinkCutTree* overall_tree = new LinkCutTree();

	BinarySearchTree* tree1 = new BinarySearchTree();
	tree1->height = 0;
	tree1->root = new Node();
	tree1->root->data = 2;
	tree1->root->node_name = 1;
	Insert(tree1, tree1->root, 3, 0);
	Insert(tree1, tree1->root, 1, 3);
	Insert(tree1, tree1->root, 0, 5);

	overall_tree->root_tree = tree1;

	BinarySearchTree* tree2 = new BinarySearchTree();
	tree2->height = 1;
	tree2->root = new Node();
	tree2->root->data = 2;
	tree2->root->node_name = 2;
	Insert(tree2, tree2->root, 3, 0);
	Insert(tree2, tree2->root, 1, 4);

	join(tree1, tree2);

	BinarySearchTree* tree3 = new BinarySearchTree();
	tree3->height = 2;
	tree3->root = new Node();
	tree3->root->data = 2;
	tree3->root->node_name = 6;
	Insert(tree3, tree3->root, 3, 0);

	join(tree1, tree3);


	/*
	LinkCutTree* overall_tree1 = new LinkCutTree();

	BinarySearchTree* tree3 = new BinarySearchTree();
	tree3->height = 0;
	tree3->root = new Node();
	tree3->root->data = 2;
	tree3->root->node_name = 1;
	Insert(tree3, tree3->root, 3, 0);
	Insert(tree3, tree3->root, 1, 3);
	Insert(tree3, tree3->root, 0, 5);

	overall_tree->root_tree = tree3;

	BinarySearchTree* tree4 = new BinarySearchTree();
	tree4->height = 2;
	tree4->root = new Node();
	tree4->root->data = 2;
	tree4->root->node_name = 6;
	Insert(tree4, tree4->root, 3, 0);

	join(tree3, tree4);
	*/

	//mincapacity(tree1, tree3, 3);

	//link(overall_tree, overall_tree1, tree2, tree4, 3, 3);

	//cout << "HERE" << endl;

	//cout << "Lowest First Edge " << lowest_capacity_first_edge << endl;
	//cout << "Lowest Second Edge " << lowest_capacity_second_edge << endl;
	//cout << "Lowest Capacity " << lowest_capacity << endl;
	//cout << endl;

	//subtract(tree1, lowest_capacity);

	int number_of_trees = 3;
	int count = 0;

	while(count < number_of_trees)
	{
		if (count == 0)
		{
			int root = findroot(overall_tree->root_tree, tree1, 3);

			if (root == 0)
			{
				mincapacity(overall_tree->root_tree, tree1, 3);
				subtract(overall_tree->root_tree, lowest_capacity);
			}

			//cout << "The Max Flow is " << total_flow << endl;
		}

		if (count == 1)
		{
			int root = findroot(overall_tree->root_tree, tree2, 3);

			//cout << "Root is " << root << endl;

			if (root == 0)
			{
				mincapacity(overall_tree->root_tree, tree2, 3);
				subtract(overall_tree->root_tree, lowest_capacity);
			}

			//cout << "The Max Flow is " << total_flow << endl;
		}

		if (count == 2)
		{
			int root = findroot(overall_tree->root_tree, tree3, 3);

			//cout << "Root is " << root << endl;

			if (root == 0)
			{
				mincapacity(overall_tree->root_tree, tree3, 3);

				//cout << "Lowest Capacity is " << lowest_capacity << endl;
				subtract(overall_tree->root_tree, lowest_capacity);
			}

			//cout << "The Max Flow is " << total_flow << endl;
		}

		first_edge = 100;
		second_edge = 100;
		last_accessed = 2;

		lowest_capacity_first_edge = 100;
		lowest_capacity_second_edge = 100;
		lowest_capacity = 100;

		count = count + 1;
	}

	cout << "The Max Flow is " << total_flow << endl;

    return 0;
}


