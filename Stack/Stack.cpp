#include"Stack.h"


template<typename T>
SeqStack<T>::SeqStack() : _size(0), tp(0), capacity(0), stack(nullptr)
{}

template<typename T>
SeqStack<T>::SeqStack(size_type capacity) : _size(0), tp(0), capacity(capacity)
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
	if (stack == nullptr)
	{
		stack = new T[1];
	}
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
T SeqStack<T>::top()
{
	if (empty())
		throw exception("stack underflow!");

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
	for (size_type i = 0; i < _size; i++)
		tmp[i] = stack[i];

	delete[] stack;
	stack = tmp;
}

template<typename T>
void SeqStack<T>::destroy()
{
	if (stack != nullptr)
	{
		delete[] stack;
		stack = nullptr;
		_size = 0;
		tp = 0;
	}
}




/**********************************************************/


template<typename T>
void LinkedStack<T>::push(const T& ele)
{
	stackNode<T>* newNode = new stackNode<T>(ele);
	newNode->next = tp;
	tp = newNode;
	_size++;
}

template<typename T>
void LinkedStack<T>::pop()
{
	if (tp == nullptr)
		throw string("stack underflow");
	stackNode<T>* tmp = tp;
	tp = tp->next;
	delete tmp;
	_size--;
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