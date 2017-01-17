#pragma once
#include <stack>
#include <iomanip>
#include <iostream>
#include <deque>
#include <sstream>
using namespace std;
template <typename DATA, typename KEY>
class BTree
{
	struct Node
	{
		DATA data;
		KEY key;
		Node *L, *R;
		explicit Node(KEY key, DATA data, Node *left = nullptr, Node *right = nullptr) : data(data), key(key), L(left), R(right) {}
	};
	Node *root;
	Node* Create_Node(KEY key, DATA data)
	{
		return new Node(key, data, nullptr, nullptr);
	}
	void Print_Node(Node* root_node)
	{
		if (root_node != nullptr)
		{
			Print_Node(root_node->L);
			cout << root_node->key << " ";
			Print_Node(root_node->R);
		}
	}
	bool delete_tree()
	{
		if (root == nullptr) return false;
		Node* node = nullptr;
		clean_tree(root);
		root = node;
		return true;
	}
	void clean_tree(Node* node)
	{
		if (node != nullptr)
		{
			count--;
			clean_tree(node->L);
			clean_tree(node->R);
			free(node);
		}
	}
	bool DeleteNode(Node* &root_node, DATA data)
	{
		Node *P, *v;
		if (!root_node) return false;

		else
			if (data < root_node->data)
				DeleteNode(root_node->L, data);
			else
				if (data > root_node->data)
					DeleteNode(root_node->R, data);
				else
				{
					P = root_node;
					if (!root_node->R)
						root_node = root_node->L;
					else
						if (!root_node->L)
							root_node = root_node->R;
						else
						{
							v = root_node->L;
							if (v->R)
							{
								while (v->R->R) v = v->R;
								root_node->data = v->R->data;
								P = v->R;
								v->R = v->R->L;
							}
							else
							{
								root_node->data = v->data;
								P = v;
								root_node->L = root_node->L->L;
							}
						}
					delete P;
					return true;
				}
		return false;
	}
	int count;
	int NodesCount()
	{
		count = 0;
		CalculateNodes(root);
		return count;
	}
	void CalculateNodes(Node* root_node)
	{
		if (root_node != nullptr)
		{
			CalculateNodes(root_node->L);
			count++;
			CalculateNodes(root_node->R);
		}
	}
	void Lt_t_Rt(Node*& root_node)
	{
		if (root_node == nullptr)
		{
			cout << "Tree is empty" << endl;
			return;
		}
		Node* t = nullptr;
		stack<Node*> *S1 = new stack<Node*>;
		stack<Node*> *S2 = new stack<Node*>;
		stack<Node*> *S3 = new stack<Node*>;
		S1->push(root_node);
		while (!S1->empty() || !S2->empty())
		{
			if (!S1->empty())
			{
				t = S1->top();
				S1->pop();
				S2->push(t);
				if (t->R != nullptr) S1->push(t->R);
			}
			else
			{
				t = S2->top();
				S2->pop();
				S3->push(t);
				if (t->L != nullptr) S1->push(t->L);
			}
		}
		while (!S3->empty())
		{
			t = S3->top();
			S3->pop();
			cout << "Key:\t" << t->key << "\tData:\t" << t->data << endl;
		}
	}
	DATA Iterative_Search(Node*& root_node, KEY key)
	{
		while (root_node != nullptr && key != root_node->key)
		{
			if (key < root_node->key) root_node = root_node->L;
			else root_node = root_node->R;
		}
		if (root_node == nullptr)
		{
			cout << "Not found" << endl;
			return static_cast<DATA>(0);
		}
		return root_node->data;
	}
	bool Iterative_Insert(Node*& root_node, KEY key, DATA data)
	{
		if (root_node == nullptr)
		{
			root_node = Create_Node(key, data);
			return true;
		}
		Node* t = root_node;
		Node* pred = nullptr;
		while (t != nullptr)
		{
			pred = t;
			if (key == t->key) return false;
			if (key < t->key) t = t->L;
			else t = t->R;
		}
		if (key < pred->key) pred->L = Create_Node(key, data);
		else pred->R = Create_Node(key, data);
		return true;
	}

	bool Iterative_Delete(Node*& root_node, KEY key)
	{
		Node* t = root_node;
		Node* pred = nullptr;
		while (t != nullptr && t->key != key)
		{
			pred = t;
			if (key < t->key) t = t->L;
			else t = t->R;
		}
		if (t == nullptr) return false;
		Node* t0;
		Node* x = nullptr;
		if (t->L != nullptr && t->R != nullptr)
		{
			t0 = t;
			pred = t;
			t = t->R;
			while (t->L != nullptr)
			{
				pred = t;
				t = t->L;
			}
			x = t->R;
		}
		else
		{
			t0 = nullptr;
			if (t->R == nullptr && t->L == nullptr) x = nullptr;
			if (t->L == nullptr) x = t->R;
			if (t->R == nullptr) x = t->L;
		}
		if (pred == nullptr) root_node = x;
		else
		{
			if (t->key < pred->key) pred->L = x;
			else pred->R = x;
		}
		if (t0 != nullptr)
		{
			t0->key = t->key;
			t0->data = t->data;
		}
		delete t;
		return true;
	}
	int _getMaxDepth(Node* root_node, int depth)
	{
		if (root_node == nullptr) return depth;
		return max(_getMaxDepth(root_node->L, depth + 1), _getMaxDepth(root_node->R, depth + 1));
	}
	// Find the maximum height of the binary tree
	int maxHeight(Node *p) {
		if (!p) return 0;
		int leftHeight = maxHeight(p->L);
		int rightHeight = maxHeight(p->R);
		return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	}
	// Convert an integer value to string
	static string intToString(int val) {
		ostringstream ss;
		ss << val;
		return ss.str();
	}
	// Print the arm branches (eg, /    \ ) on a line
	void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
		typename deque<Node*>::const_iterator iter = nodesQueue.begin();
		for (int i = 0; i < nodesInThisLevel / 2; i++) {
			out << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
			out << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
		}
		out << endl;
	}
	// Print the branches and node (eg, ___10___ )
	void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
		typename deque<Node*>::const_iterator iter = nodesQueue.begin();
		for (int i = 0; i < nodesInThisLevel; i++, iter++) {
			out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->L) ? setfill('_') : setfill(' '));
			out << setw(branchLen + 2) << ((*iter) ? intToString((*iter)->key) : "");
			out << ((*iter && (*iter)->R) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
		}
		out << endl;
	}
	// Print the leaves only (just for the bottom row)
	void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
		typename deque<Node*>::const_iterator iter = nodesQueue.begin();
		for (int i = 0; i < nodesInThisLevel; i++, ++iter) {
			out << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->key) : "");
		}
		out << endl;
	}
	// Pretty formatting of a binary tree to the output stream
	// @ param
	// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
	// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
	void printPretty(Node *root, int level, int indentSpace, ostream& out) {
		int h = maxHeight(root);
		int nodesInThisLevel = 1;
		int branchLen = 2 * (static_cast<int>(pow(2.0, h)) - 1) - (3 - level)*static_cast<int>(pow(2.0, h - 1));  // eq of the length of branch for each node of each level
		int nodeSpaceLen = 2 + (level + 1)*static_cast<int>(pow(2.0, h));  // distance between left neighbor node's right arm and right neighbor node's left arm
		int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

		deque<Node*> nodesQueue;
		nodesQueue.push_back(root);
		for (int r = 1; r < h; r++) {
			printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
			branchLen = branchLen / 2 - 1;
			nodeSpaceLen = nodeSpaceLen / 2 + 1;
			startLen = branchLen + (3 - level) + indentSpace;
			printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

			for (int i = 0; i < nodesInThisLevel; i++) {
				Node *currNode = nodesQueue.front();
				nodesQueue.pop_front();
				if (currNode) {
					nodesQueue.push_back(currNode->L);
					nodesQueue.push_back(currNode->R);
				}
				else {
					nodesQueue.push_back(NULL);
					nodesQueue.push_back(NULL);
				}
			}
			nodesInThisLevel *= 2;
		}
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
		printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
	}

public:
	explicit BTree(Node *root_node = nullptr) :root(root_node), count(0){}
	~BTree();
	void addChild(KEY key, DATA d)
	{
		cout << "Add key \"" << key << "\"\tis: " << (Iterative_Insert(root, key, d) ? "ok" : "already exist") << endl;
	}
	bool del(KEY k)
	{
		return Iterative_Delete(root, k);
	}
	void print()
	{
		printPretty(root, 1, 0, cout);
		cout << endl;
		//Print_Node(root);
	}
	DATA find(KEY k)
	{
		return Iterative_Search(root, k);
	}	
	int GetNodesCount()
	{
		return NodesCount();
	}
	void Obhod()
	{
		Lt_t_Rt(root);
	}
	bool isEmpty()
	{
		return root == nullptr;
	}
	int getMaxDepth()
	{
		return _getMaxDepth(root, 0);
	}
	bool delete_All()
	{
		return delete_tree();
	}
};

template <typename DATA, typename KEY>
BTree<DATA, KEY>::~BTree()
{
}
