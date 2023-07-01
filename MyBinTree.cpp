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
}

/*
	returns nullptr if value not found
*/
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