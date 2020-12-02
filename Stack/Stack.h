#ifndef __Stack__
#define __Stack__
#include<iostream>
#include<exception>


using namespace std;

template<typename T>
struct stackNode {
	T data;
	stackNode * next;
	stackNode() : next(nullptr) {}
};

template<typename T>
class SeqStack
{
public:
	SeqStack() : size(0), top(0), capacity(100)
	{
		stack = new T[capacity];
		if (stack == nullptr)
			throw exception("fail to allocate memory.");
	}

	SeqStack(size_t capacity): size(0), top(0), capacity(capacity)
	{
		stack = new T[capacity];

		if (stack == nullptr)
			throw exception("fail to allocate memory.");
	}

	SeqStack(const SeqStack& stk):size(stk.size), top(stk.top), capacity(stk.capacity)
	{
		stack = new T[capacity];
		if (stack == nullptr)
			throw exception("fail to allocate memory.");

		for (size_t i = 0; i < size; i++)
			stack[i] = stk.stack[i];
	}

	void push(T ele)
	{
		if (size == capacity) //expand capacity
			expand();
			
		stack[top++] = ele;
		size++;
	}

	void pop()
	{
		if (empty())
			throw exception("Stack underflow!");

		size--;
		top--;
	}

	T top()
	{
		if (empty())
			throw exception("the stack is empty!");

		return stack[top-1];
	}

	size_t size()
	{
		return size;
	}

	void clear()
	{
		if (stack != nullptr)
		{
			size = 0;
			top = 0;
		}
	}

	bool empty()
	{
		return size == 0 ? true : false;
	}

	~SeqStack() 
	{
		destroy();
	}

private:
	T* stack;
	size_t size;
	size_t top;
	size_t capacity;

	void expand()
	{
		capacity *= 2
		T* tmp = new T[capacity];
		for (size_t i=0; i<size; i++)
			tmp[i] = stack[i];

		delete[] stack;
		stack = tmp;
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




template<typename T>
class LinkedStack
{
public:
	LinkedStack(): top(nullptr), size(0)
	{
	}

	~LinkedStack()
	{
		destroy();
	}

	size_t size()
	{
		return size;
	}

	void push(T ele)
	{
		stackNode<T> * newNode = new stackNode<T>();
		newNode->data = ele;
		newNode->next = top;
		top = newNode;
		size++;
	}

	void pop()
	{
		if (top == nullptr)
			throw string("stack underflow");
		T ret = top->data;
		stackNode<T> * tmp = top;
		top = top->next;
		delete tmp;
		size--;
		return ret;
	}

	T top()
	{
		if (top==nullptr)
			throw string("the stack is empty");

		return top->data;
	}

private:
	stackNode<T> * top;
	size_t size;

	void destroy()
	{
		if (top != nullptr)
		{
			while (top != nullptr)
			{
				stackNode<T>* tmp = top;
				top = top->next;
				delete tmp;
			}
		}
	}
};

#endif