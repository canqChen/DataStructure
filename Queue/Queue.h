#pragma once
#include<iostream>

#define ElemType int
#define MAXSIZE 100

using namespace std;

typedef struct queueNode {
	ElemType data;
	struct queueNode* next;
}qNode, * pQNode;

class SeqQueue
{
public:
	SeqQueue(int maxSize = MAXSIZE)
	{
		queue = new ElemType[maxSize];

		if (queue == nullptr)
		{
			throw string("fail to allocate memory.");
		}
		this->maxSize = maxSize;
		size = 0;
		front = rear = 0;
	}

	void enQueue(ElemType ele)
	{
		if (queue == nullptr)
			throw string("the queue is not initialized!");
		else if(size==maxSize)
			throw string("queue overflow!");
			
		queue[rear++] = ele;
		if (rear == maxSize && front != 0)
			rear = 0;
		size++;
	}

	ElemType deQueue()
	{
		if (is_empty())
		{
			throw string("Queue underflow!");
		}
		size--;
		ElemType ret = queue[front];
		front++;
		if (front == maxSize)
			front = 0;

		return ret;
	}

	ElemType getHead()
	{
		if (is_empty())
		{
			throw string("the queue is empty!");
		}
		return queue[front];
	}

	void clear()
	{
		if (queue != nullptr)
		{
			size = 0;
			front = rear = 0;
		}
	}

	~SeqQueue() 
	{
		destroy();
	}

private:
	ElemType* queue;
	int size;
	int front;
	int rear;
	int maxSize;

	void destroy()
	{
		if (queue != nullptr)
		{
			delete[] queue;
			queue = nullptr;
			size = 0;
			front = rear = 0;
		}
	}

	bool is_empty()
	{
		return size == 0 ? true : false;
	}
};


class LinkedQueue
{
public:
	LinkedQueue()
	{
		front = rear = nullptr;
		length = 0;
	}

	~LinkedQueue()
	{
		clear();
	}

	int getLength()
	{
		return length;
	}

	void enQueue(ElemType ele)
	{
		pQNode newNode = new qNode;
		newNode->data = ele;
		newNode->next = nullptr;

		if (length == 0)
		{
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = rear->next;
		}
		
		length++;
	}

	ElemType deQueue()
	{
		if (front == nullptr)
		{
			throw string("the queue is empty");
		}

		ElemType ret = front->data;
		pQNode tmp = front;
		front = front->next;
		delete tmp;
		length--;
		return ret;
	}

	ElemType getHead()
	{
		if (front==nullptr)
		{
			throw string("the queue is empty");
		}
		return front->data;
	}

	void clear()
	{
		if (front != nullptr)
		{
			while (front != nullptr)
			{
				pQNode tmp = front;
				front = front->next;
				delete tmp;
			}
		}
	}

private:
	pQNode front, rear;
	int length;
};