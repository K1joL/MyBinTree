#ifndef MYBINTREE_H
#define MYBINTREE_H



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
private:
	int m_size = 0;
	Node* m_root = nullptr;
public:
	MyBinTree()
	{}
	void insert(int value);
	int size() { return m_size; }
	void erase(int value);
	void clear();
	Node *find(int value);
	MyBinTree& operator+(const MyBinTree& other);
	MyBinTree(const MyBinTree& other);
	MyBinTree& operator=(const MyBinTree& other);
};

#endif // !MYBINTREE_H
