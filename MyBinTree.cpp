#include "MyBinTree.h"

void MyBinTree::insert(int value)
{
	if (m_root == nullptr)
		m_root = new Node(value);
	else
	{
		Node* current = m_root;
		while (true)
		{
			if (value >= current->data)
			{
				if(current->pright == nullptr)
				{
					current->pright = new Node(value, current);
					break;
				}
				current = current->pright;
			}
			else
			{
				if (current->pleft == nullptr)
				{
					current->pleft = new Node(value, current);
					break;
				}
				current = current->pleft;
			}
		}
	}
	m_size++;
	if (m_size % 10 == 0)
		balance();
}

/* returns nullptr if value not found */
MyBinTree::Node* MyBinTree::find(int value)
{
	if (m_size == 0)
		return nullptr;
	Node* current = m_root;
	while (current != nullptr)
	{
		if (value == current->data)
			return current;
		if (value > current->data)
		{
			current = current->pright;
		}
		else
		{
			current = current->pleft;
		}
	}
	return nullptr;
}

/* 
Makes the tree orderly
If root = nullptr then root would be this->m_root
*/
void MyBinTree::balance(Node* root, std::queue<Node*>* QofNodes)
{
	int flag = 0;
	if (root == nullptr)
	{
		root = this->m_root;
		flag++;
	}
	std::vector<Node*> nodes;
	nodes.reserve(this->m_size);

	std::queue<Node*> queue;
	Node* current = nullptr;

	if (QofNodes == nullptr)
	{
		queue.push(root);
		while (!queue.empty())
		{
			current = queue.front();
			nodes.push_back(queue.front());
			queue.pop();

			if (current->pright != nullptr)
				queue.push(current->pright);
			if (current->pleft != nullptr)
				queue.push(current->pleft);

		}
		std::sort(nodes.begin(), nodes.end(),
			[](const Node* x, const Node* y)
			{
				return x->data < y->data;
			});
		queue = createQueueOfMid(nodes.begin(), nodes.begin() + nodes.size() - 1);
	}
	else
		queue = move(*QofNodes);

	if(flag)
	{
		m_root = queue.front();
		root = m_root;
		root->parent = nullptr;
	}
	else
	{
		queue.front()->parent = root;
		if (root->pright == nullptr)
			root->pright = queue.front();
		else
			root->pleft = queue.front();
		root = queue.front();
	}

	queue.pop();
	root->pright = nullptr;
	root->pleft = nullptr;
	Node* currentQ = nullptr;
	Node* prev = root;
	while (!queue.empty())
	{
		currentQ = queue.front();
		queue.pop();
		if (currentQ == nullptr)
			continue;
		currentQ->pright = nullptr;
		currentQ->pleft = nullptr;
		current = root;
		while (true)
			if (currentQ->data >= current->data)
			{
				if (current->pright == nullptr)
				{
					current->pright = currentQ;
					currentQ->parent = current;
					break;
				}
				current = current->pright;
			}
			else
			{
				if (current->pleft == nullptr)
				{
					current->pleft = currentQ;
					currentQ->parent = current;
					break;
				}
				current = current->pleft;
			}
	}
}

/* Create a new ordered tree from the other two */
MyBinTree& operator+(const MyBinTree& first, const MyBinTree& second)
{
	if (first.m_root == nullptr)
		return *(new MyBinTree(second));
	if (second.m_root == nullptr)
		return *(new MyBinTree(first));

	MyBinTree *newTree = new MyBinTree(first);
	newTree->m_size += second.m_size;

	std::queue<MyBinTree::Node*> queue;
	queue.push(second.m_root);

	MyBinTree::Node* current = nullptr;
	while (!queue.empty())
	{
		current = queue.front();
		queue.pop();

		if (current->pleft)
			queue.push(current->pleft);

		if (current->pright)
			queue.push(current->pright);

		newTree->insert(current->data);
	}
	newTree->balance();
	return *newTree;
}

/* Copy constructor */
MyBinTree::MyBinTree(const MyBinTree& other)
{
	if(other.m_root != nullptr || &other != this)
	{
		std::queue<Node*> queue;
		queue.push(other.m_root);

		Node* current = nullptr;
		while (!queue.empty())
		{
			current = queue.front();
			queue.pop();

			if (current->pleft) 
				queue.push(current->pleft);

			if (current->pright)
				queue.push(current->pright);

			this->insert(current->data);
		}
	}
}

MyBinTree& MyBinTree::operator=(const MyBinTree& other)
{
	if (this == &other)
		return *this;

	this->clear();
	this->m_root = other.m_root;
	this->m_size = other.m_size;

	return *this;
}
/* Recursive function that create queue of elements to create ordered tree */
std::queue<MyBinTree::Node*>& createQueueOfMid(const MyBinTree::VecIt& begin, const MyBinTree::VecIt& end)
{
	std::queue<MyBinTree::Node*>* q = new std::queue<MyBinTree::Node*>;
	if (begin == end)
	{
		q->push(*begin);
		return *q;
	}
	int midOfVector = abs(distance(begin, end) / 2);
	MyBinTree::VecIt midIt = begin + midOfVector;
	q->push(*midIt);

	auto pushQinQueue = [q](std::queue<MyBinTree::Node*>& qFrom) {
		while (!qFrom.empty()) {
			q->push(qFrom.front());
			qFrom.pop();
		}};

	if (begin+1 != end)
	{
		pushQinQueue(createQueueOfMid(begin, prev(midIt)));
		pushQinQueue(createQueueOfMid(next(midIt), end));
	}
	else
		q->push(*end);

	return *q;
}

void MyBinTree::erase(int value)
{
	Node* nodeToDelete = find(value);
	if (nodeToDelete == nullptr)
		return;
	std::queue<Node*> queue;
	std::vector<Node*> nodes;
	queue.push(nodeToDelete);
	Node* current = nullptr;
	while (!queue.empty())
	{
		current = queue.front();
		nodes.push_back(queue.front());
		queue.pop();

		if (current->pright != nullptr)
			queue.push(current->pright);
		if (current->pleft != nullptr)
			queue.push(current->pleft);
	}
	nodes.erase(nodes.begin());
	Node* parentOfDeleted = nodeToDelete->parent;
	//deleting node
	if(parentOfDeleted->pright == nodeToDelete)
		parentOfDeleted->pright = nullptr;
	else
		parentOfDeleted->pleft = nullptr;
	delete nodeToDelete;

	std::sort(nodes.begin(), nodes.end(),
		[](const Node* x, const Node* y)
		{
			return x->data < y->data;
		});
	queue = createQueueOfMid(nodes.begin(), nodes.begin() + nodes.size() - 1);
	balance(parentOfDeleted, &queue);
	--m_size;
}

void MyBinTree::clear()
{
	if (m_root == nullptr)
		return;
	std::queue<Node*> queue;
	queue.push(m_root);
	Node* current = nullptr;
	while (!queue.empty())
	{
		current = queue.front();
		queue.pop();

		if (current->pright != nullptr)
			queue.push(current->pright);
		
		if (current->pleft != nullptr)
			queue.push(current->pleft);

		delete current;
	}
	m_size = 0;
	m_root = nullptr;
}