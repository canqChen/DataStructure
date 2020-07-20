#pragma once
#include<iostream>

#define ElemType int
#define MAXSIZE 100

using namespace std;

typedef struct stackNode {
	ElemType data;
	struct stackNode* next;
}StkNode, * pStkNode;

class SeqStack
{
public:
	SeqStack(int maxSize = MAXSIZE)
	{
		stack = new ElemType[maxSize];

		if (stack == nullptr)
		{
			throw string("fail to allocate memory.");
		}
		this->maxSize = maxSize;
		size = 0;
		top = 0;
	}

	void push(ElemType ele)
	{
		if (stack == nullptr)
			throw string("the stack is not initialized!");
		else if(size==maxSize)
			throw string("Stack overflow!");
			
		stack[top++] = ele;
		size++;
	}

	ElemType pop()
	{
		if (is_empty())
		{
			throw string("Stack underflow!");
		}
		size--;
		return stack[--top];
	}

	ElemType getTop()
	{
		if (is_empty())
		{
			throw string("the stack is empty!");
		}
		return stack[top-1];
	}

	void clear()
	{
		if (stack != nullptr)
		{
			size = 0;
			top = 0;
		}
	}

	~SeqStack() 
	{
		delete[] stack;
	}

private:
	ElemType* stack;
	int size;
	int top;
	int maxSize;

	bool is_empty()
	{
		return size == 0 ? true : false;
	}

	void destroy()
	{
		if (stack != nullptr)
		{
			delete[] stack;
			stack = nullptr;
			size = 0;
			top = 0;
		}
	}
};


class LinkedStack
{
public:
	LinkedStack()
	{
		top = nullptr;
		length = 0;
	}

	~LinkedStack()
	{
		clear();
	}

	int getLength()
	{
		return length;
	}

	void push(ElemType ele)
	{
		pStkNode newNode = new StkNode;
		newNode->data = ele;
		newNode->next = top;
		top = newNode;
		length++;
	}

	ElemType pop()
	{
		if (top == nullptr)
		{
			throw string("the stack is empty");
		}
		ElemType ret = top->data;
		pStkNode tmp = top;
		top = top->next;
		delete tmp;
		length--;
		return ret;
	}

	ElemType getTop()
	{
		if (top==nullptr)
		{
			throw string("the stack is empty");
		}
		return top->data;
	}

	void clear()
	{
		if (top != nullptr)
		{
			while (top != nullptr)
			{
				pStkNode tmp = top;
				top = top->next;
				delete tmp;
			}
		}
	}
private:
	pStkNode top;
	int length;

};