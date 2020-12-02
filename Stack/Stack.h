#ifndef __Stack__
#define __Stack__
#include<iostream>
#include<exception>

using namespace std;

template<typename T>
struct stackNode {
	T data;
	stackNode* next;
	stackNode() : next(nullptr) {}
};

template<typename T>
class SeqStack
{
public:
	SeqStack();

	SeqStack(size_t capacity);

	SeqStack(const SeqStack& stk);

	void push(const T& ele);

	void pop();

	T& top();

	size_t size() const
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
	size_t _size;
	size_t tp;
	size_t capacity;

	void expand();

	void destroy()
	{
		if (stack != nullptr)
		{
			delete[] stack;
			stack = nullptr;
			_size = 0;
			tp = 0;
		}
	}
};

template<typename T>
SeqStack<T>::SeqStack() : _size(0), tp(0), capacity(100)
{
	stack = new T[capacity];
	if (stack == nullptr)
		throw exception("fail to allocate memory.");
}

template<typename T>
SeqStack<T>::SeqStack(size_t capacity) : _size(0), tp(0), capacity(capacity)
{
	stack = new T[capacity];

	if (stack == nullptr)
		throw exception("fail to allocate memory.");
}

template<typename T>
SeqStack<T>::SeqStack(const SeqStack<T>& stk) :_size(stk._size), tp(stk.tp), capacity(stk.capacity)
{
	stack = new T[capacity];
	if (stack == nullptr)
		throw exception("fail to allocate memory.");

	copy(begin(rhs.stack), end(rhs.stack), this->stack);
}

template<typename T>
void SeqStack<T>::push(const T& ele)
{
	if (_size == capacity) //expand capacity
		expand();
	stack[tp++] = ele;
	_size++;
}

template<typename T>
void SeqStack<T>::pop()
{
	if (empty())
		throw exception("Stack underflow!");
	_size--;
	tp--;
}

template<typename T>
T& SeqStack<T>::top()
{
	if (empty())
		throw exception("the stack is empty!");

	return stack[tp - 1];
}

template<typename T>
SeqStack<T>& SeqStack<T>::operator = (const SeqStack<T>& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	destroy();
	this->tp = rhs.tp;
	this->_size = rhs._size;
	this->capacity = rhs.capacity;
	this->stack = new T[capacity];
	if (this->stack == nullptr)
		throw exception("fail to allocate memory.");
	copy(begin(rhs.stack), end(rhs.stack), this->stack);
	return *this;
}

template<typename T>
void SeqStack<T>::expand()
{
	capacity *= 2;

	T* tmp = new T[capacity];
	for (size_t i = 0; i < _size; i++)
		tmp[i] = stack[i];

	delete[] stack;
	stack = tmp;
}

template<typename T>
class LinkedStack
{
public:
	LinkedStack() : tp(nullptr), _size(0) {}

	~LinkedStack()
	{
		destroy();
	}

	size_t _size() const
	{
		return _size;
	}

	void push(T& ele);

	void pop();

	T& top();

private:
	stackNode<T>* tp;
	size_t _size;

	void destroy();
};

#endif

template<typename T>
void LinkedStack<T>::push(T& ele)
{
	stackNode<T>* newNode = new stackNode<T>();
	newNode->data = ele;
	newNode->next = tp;
	tp = newNode;
	_size++;
}

template<typename T>
void LinkedStack<T>::pop()
{
	if (tp == nullptr)
		throw string("stack underflow");
	T ret = tp->data;
	stackNode<T>* tmp = tp;
	tp = tp->next;
	delete tmp;
	_size--;
	return ret;
}

template<typename T>
T& LinkedStack<T>::top()
{
	if (tp == nullptr)
		throw string("the stack is empty");

	return tp->data;
}

template<typename T>
void LinkedStack<T>::destroy()
{
	if (tp != nullptr)
	{
		while (tp != nullptr)
		{
			stackNode<T>* tmp = tp;
			tp = tp->next;
			delete tmp;
		}
	}
}
