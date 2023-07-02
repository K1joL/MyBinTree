#ifndef MYBINTREE_H
#define MYBINTREE_H

#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>

class MyBinTree
{
	struct Node
	{
		int data = 0;
		Node* parent = nullptr;
		Node* pleft = nullptr;
		Node* pright = nullptr;
		Node(int data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
			: data(data), parent(parent), pleft(left), pright(right)
		{}
	};

	using VecIt = std::vector<Node*>::iterator;
	friend std::queue<Node*>& createQueueOfMid(const VecIt& begin, const VecIt& end);

private:
	int m_size = 0;
	Node* m_root = nullptr;
public:
	MyBinTree()
	{}
	~MyBinTree() { clear(); }
	void balance();
	void insert(int value);
	int size() const { return m_size; }
	void erase(int value);
	void clear();
	Node *find(int value);
	friend MyBinTree& operator+(const MyBinTree& first, const MyBinTree& second);
	MyBinTree(const MyBinTree& other);
	MyBinTree& operator=(const MyBinTree& other);
};

#endif // !MYBINTREE_H
