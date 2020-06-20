#pragma once

#include<iostream>

typedef int ELETYPE;

using namespace std;

typedef struct Lnode {
	ELETYPE data;
	struct Lnode* next;
}Lnode, * pLnode, * LList;

class LinkedList
{
public:
	LinkedList()
	{
		initialization();
	}

	~LinkedList()
	{
		if (list != nullptr)
		{
			delete list;
		}
	}

	void initialization()
	{
		head = new Lnode;
		list = head;
		head->next = nullptr;
	}

	int calLength()
	{
		int count = 0;
		pLnode temp = head->next;
		while (temp != nullptr)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}

	int getLength()
	{
		return length;
	}

	ELETYPE getElementAt(int pos)
	{
		if (pos<1 || pos>length)
		{
			throw "wrong position";
		}
		check_list();
		pLnode cur_node = head;

		do
		{
			cur_node = cur_node->next;
			pos--;
		} while (pos > 0);

		return cur_node->data;
	}

	int getPosition(ELETYPE ele)
	{
		pLnode cur_node = head;
		int pos = 0;

		for (int i = 1; i <= length; i++)
		{
			cur_node = cur_node->next;
			if (cur_node->data = ele)
			{
				return i;
			}
		}

		throw "element not found!";
	}

	pLnode getAddress(ELETYPE ele)
	{
		check_list();

		pLnode cur_node = head->next;

		while (cur_node != nullptr)
		{
			if (cur_node->data = ele)
			{
				return cur_node;
			}
			cur_node = cur_node->next;
		}

		throw "element not found!";
	}

	void insert(ELETYPE ele, int pos = -1)
	{
		if (pos==-1) //default, insert to the tail
		{
			pLnode cur_node = head;
			while (1)
			{
				if (cur_node->next==nullptr)
				{
					break;
				}
				cur_node = cur_node->next;
			}
			pLnode newNode = new Lnode;
			newNode->data = ele;
			newNode->next = nullptr;
			cur_node->next = newNode;
			return;
		}

		if (pos<1 || pos>length+1)
		{
			throw "wrong position";
		}
		// insert to the middle
		pLnode cur_node = head;
		for (int i = 1; i<=pos-1;i++)
		{
			cur_node = cur_node->next;
		}
		pLnode newNode = new Lnode;
		newNode->data = ele;
		newNode->next = cur_node->next;
		cur_node->next = newNode;
	}

	void print()
	{
		check_list();
		pLnode cur_node = head->next;
		while ()
		{
		}
	}

	bool is_empty()
	{
		//return (head->next == nullptr ? true : false);
		return (length < 1 ? true : false);
	}

	void destroy()
	{
		pLnode temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		length = 0;
	}

	void clear()
	{
		pLnode first_node = head->next;
		pLnode temp;
		while (first_node != nullptr)
		{
			temp = first_node;
			first_node = first_node->next;
			delete temp;
		}
		head->next = nullptr;
		length = 0;
	}

private:
	LList list;
	pLnode head;
	int length;

	void check_list()
	{
		if (is_empty())
		{
			throw "the linked list is empty!";
		}
	}
};