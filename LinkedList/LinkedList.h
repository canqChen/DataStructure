#pragma once

#include<iostream>

typedef int ELETYPE;

using namespace std;

typedef struct Lnode {
	ELETYPE data;
	struct Lnode * next;
}Lnode, *pLnode;


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
		if (pos<1||pos>length)
		{
			throw "wrong position";
		}
		if (is_empty())
		{
			throw "the linked list is empty";
		}
		pLnode cur_node = head->next;
		ELETYPE data;
		do 
		{
			data = cur_node->data;
			cur_node = cur_node->next;
			pos--;
		} while (pos>0);
		return data;
	}

	bool is_empty()
	{
		return (head->next == nullptr ? true : false);
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
		while (first_node!=nullptr)
		{
			temp = first_node;
			first_node = first_node->next;
			delete temp;
		}
		head->next = nullptr;
		length = 0;
	}

private:
	pLnode list;
	pLnode head;
	int length;
};