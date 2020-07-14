#pragma once
#include<iostream>

#define ElemType int
#define MAXSIZE 100

using namespace std;

class Stack
{
public:
	Stack()
	{
		stack = new ElemType[MAXSIZE];

		if (stack == nullptr)
		{
			throw string("fail to allocate memory.");
		}

		length = 0;
		top = -1;
	}

	void insert(ElemType ele, int pos = -1)
	{
		if (stack == nullptr)
		{
			cout << "the stack is not initialized!";
			return;
		}
		else if (length == MAXSIZE)
		{
			cout << "fail to insert new element into the stack, the stack is full!";
			return;
		}
		//insert
		if (pos == -1)  //default, insert into the tail
		{
			stack[length++] = ele;
		}
		else if (pos<1 || pos>length + 1)  //invalid position
		{
			cout << "fail to insert new element into the position of " << pos;
			return;
		}
		else   //valid position, insert into the middle (head)
		{
			for (int i = length; i >= pos; i--)
			{
				stack[i] = stack[i - 1];
			}

			stack[pos - 1] = ele;
			length++;
		}
	}

	void remove(int pos)
	{
		if (is_empty())
		{
			cout << "the stack is empty!";
			return;
		}
		else
		{
			if (pos < 1 || pos >= length + 1)  //invalid position
			{
				cout << "invalid position of " << pos;
				return;
			}
			for (int i = pos - 1; i < length - 1; i++)
			{
				stack[i] = stack[i + 1];
			}
			length--;
		}
	}

	void remove_first(ElemType ele)
	{
		if (is_empty())
		{
			cout << "the stack is empty!";
			return;
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (stack[i] == ele)
				{
					if (i != length - 1)  // remove the element in the middle, the last one just reduce the length
					{
						for (int j = i; j < length; j++)
						{
							stack[j] = stack[j + 1];
						}
						length--;
					}
					break;
				}
			}
		}
	}

	void remove_all(ElemType ele)
	{
		if (is_empty())
		{
			cout << "the stack is empty!";
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (stack[i] == ele)
				{
					for (int j = i; j < length - 1; j++)
					{
						stack[j] = stack[j + 1];
					}
					length--;
				}
			}
		}
	}

	void print()
	{
		for (int i = 0; i < length; i++)
		{
			cout << stack[i] << "    ";
		}
	}
	
	void destroy()
	{
		if (stack != nullptr)
		{
			delete[] stack;
			stack = nullptr;
			length = 0;
		}
	}

	void clear()
	{
		if (stack != nullptr)
		{
			length = 0;
		}
	}

	~Stack() {
		if (stack != nullptr)
			delete[] stack;
	}

private:
	ElemType* stack;
	int length;
	int top;

	bool is_empty()
	{
		return length == 0 ? true : false;
	}
};
