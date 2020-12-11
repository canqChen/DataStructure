#ifndef __Stack__
#define __Stack__
#include<iostream>
#include<exception>

using namespace std;


template<typename T>
struct stackNode {
	T data;
	stackNode<T> * next;
	stackNode() : data(T()), next(nullptr) {}
	stackNode(T& data) : data(data), next(nullptr) {}
};

template<typename T>
class SeqStack
{
public:
	typedef size_t size_type;
	typedef T value_type;
	SeqStack();

	SeqStack(size_type capacity);

	SeqStack(const SeqStack& stk);

	void push(const T& ele);

	void pop();

	T& top();

	size_type size() const
	{
		return _size;
	}

	void clear()
	{
		if (stack != nullptr)
		{
			_size = 0;
			tp = 0;
		}
	}

	bool empty() const
	{
		return _size == 0 ? true : false;
	}

	~SeqStack()
	{
		destroy();
	}

	SeqStack& operator = (const SeqStack& rhs);

private:
	T* stack;
	size_type _size;
	size_type tp;
	size_type capacity;

	void expand();

	void destroy();
};



template<typename T>
class LinkedStack
{
public:
	typedef size_t size_type;
	typedef T value_type;
	LinkedStack() : tp(nullptr), _size(0) {}

	~LinkedStack()
	{
		destroy();
	}

	size_type size() const
	{
		return _size;
	}

	void push(T& ele);

	void pop();

	T& top();

private:
	stackNode<T>* tp;
	size_type _size;

	void destroy();
};



#endif