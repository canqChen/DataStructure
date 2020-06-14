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

private:
	pLnode list;
	pLnode head;
};