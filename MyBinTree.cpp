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

