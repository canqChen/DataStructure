#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include<iostream>


using namespace std;

template<typename T>
struct ListNode {
	T data;
	ListNode<T>* next;
	ListNode() : next(nullptr) {};
};

template<typename T>
class LinkedList
{
public:
	LinkedList();

	LinkedList(const LinkedList<T>& list);
	~LinkedList()
	{
		destroy();
	}

	void extend(const LinkedList<T>& list);

	size_t getLength() const
	{
		return length;
	}

	T& getElementAt(int pos)
	{
		if (pos<1 || pos>length)
		{
			throw string("wrong position");
		}

		LinkedList<T>* cur_node = head;

		do
		{
			cur_node = cur_node->next;
			pos--;
		} while (pos > 0);

		return cur_node->data;
	}

	size_t getPosition(T& ele)
	{
		LinkedList<T>* cur_node = head;
		size_t pos = 0;

		for (int size_t = 1; i <= length; i++)
		{
			cur_node = cur_node->next;
			if (cur_node->data = ele)
			{
				return i;
			}
		}

		throw string("element not found!");
	}

	LinkedList<T>* getAddress(T ele)
	{

		LinkedList<T>* cur_node = head->next;

		while (cur_node != nullptr)
		{
			if (cur_node->data = ele)
			{
				return cur_node;
			}
			cur_node = cur_node->next;
		}

		throw string("element not found!");
	}

	void insert(T ele, int pos = -1)
	{
		if (pos==-1) //default, insert to the tail
		{
			LinkedList<T>* cur_node = head;
			while (1)
			{
				if (cur_node->next==nullptr)
				{
					break;
				}
				cur_node = cur_node->next;
			}
			LinkedList<T>* newNode = new LinkedList<T>();
			newNode->data = ele;
			newNode->next = nullptr;
			cur_node->next = newNode;
			length++;
			return;
		}

		if (pos<1 || pos>length+1)
		{
			throw string("wrong position");
		}

		// insert to the middle
		LinkedList<T>* cur_node = head;
		for (int i = 1; i<=pos-1;i++)
		{
			cur_node = cur_node->next;
		}
		LinkedList<T>* newNode = new LinkedList<T>();
		newNode->data = ele;
		newNode->next = cur_node->next;
		cur_node->next = newNode;
		length++;
	}

	void removeNodeByPosition(int pos)
	{
		if (pos<1 || pos>length)
		{
			throw string("wrong position");
		}

		LinkedList<T>* cur_node = head;

		for (int i = 1; i <= pos - 1; i++)
		{
			cur_node = cur_node->next;
		}
		LinkedList<T>* temp = cur_node->next;
		cur_node->next = (cur_node->next)->next;
		delete temp;
	}

	void removeNodeByValue(T& ele, bool rmAll = false)
	{
		LinkedList<T>* cur_node = head;

		while ((cur_node->next) != nullptr)
		{
			if ((cur_node->next)->data == ele)
			{
				LinkedList<T>* temp = cur_node->next;
				cur_node->next = temp->next;
				delete temp;
				if (rmAll)
					continue;
				else
					return;
			}
			cur_node = cur_node->next;
		}
	}

	void print()
	{
		LinkedList<T>* cur_node = head->next;
		while (cur_node!=nullptr)
		{
			cout << cur_node->data<<"  ";
			cur_node = cur_node->next;
		}
	}

	bool empty() const
	{
		//return (head->next == nullptr ? true : false);
		return (length < 1 ? true : false);
	}

	void destroy();

	void clear()
	{
		LinkedList<T>* first_node = head->next;
		LinkedList<T>* temp;
		while (first_node != nullptr)
		{
			temp = first_node;
			first_node = first_node->next;
			delete temp;
		}
		head->next = nullptr;
		length = 0;
	}


private:
	ListNode<T> * head;
	size_t length;
};



#endif

template<typename T>
LinkedList<T>::LinkedList(): head(nullptr), length(0)
{
	head = new LinkedList<T>();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	destroy();
	this->head = new LinkedList<T>();
	this->head->next = nullptr;
	this->length = list.length;

	const LinkedList<T> * l_head = list.head;
	LinkedList<T>* cur_node = head;

	LinkedList<T>* l_cur_node = l_head->next;
	while (l_cur_node != nullptr)
	{
		LinkedList<T>* new_node = new LinkedList<T>();
		new_node->data = l_cur_node->data;
		new_node->next = nullptr;

		cur_node->next = new_node;

		cur_node = cur_node->next;
		l_cur_node = l_cur_node->next;
	}
}

template<typename T>
void LinkedList<T>::extend(const LinkedList<T>& list)
{
	this->length += list.length;

	const LinkedList<T>* l_head = list.head;
	LinkedList<T>* cur_node = head;

	while (cur_node->next != nullptr)
	{
		cur_node = cur_node->next;
	}

	LinkedList<T>* l_cur_node = l_head->next;
	while (l_cur_node != nullptr)
	{
		LinkedList<T>* new_node = new LinkedList<T>();
		new_node->data = l_cur_node->data;
		new_node->next = nullptr;

		cur_node->next = new_node;

		cur_node = cur_node->next;
		l_cur_node = l_cur_node->next;
	}
}

template<typename T>
void LinkedList<T>::destroy()
{
	LinkedList<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
	}
	length = 0;
}
