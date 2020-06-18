#pragma once

#include<iostream>

typedef int ELETYPE;



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
	}

private:
	pLnode list;
	pLnode head;
};