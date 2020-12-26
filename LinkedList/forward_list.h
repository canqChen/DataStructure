#ifndef __FORWARD_LIST__
#define __FORWARD_LIST__

#include<iostream>


using namespace std;

template<typename T>
struct __ListNode {
	T data;
	__ListNode<T>* next;
	__ListNode() : data(T()), next(nullptr) {};
	__ListNode(const T& val, __ListNode<T>* _next) : data(val) : next(_next) {};
};

template<typename T>
struct __forward_list_iterator {
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;

	typedef __forward_list_iterator<T> self;

	typedef __ListNode<T>* pNode;

	__forward_list_iterator(const self& it) : node(it.node) {}

	pNode node;
	
	self& operator ++()
	{
		this->node = this->node->next;
		return *this;
	}

	self operator ++(int)
	{
		self tmp = *this;
		node = (*node).next;
		return tmp;
	}

	reference operator *() const
	{
		return (*node).data;
	}

	pointer operator ->() const
	{
		return &(operator*());
	}

	bool operator ==(const self& rhs) const
	{
		return this->node == rhs.node;
	}

	bool operator !=(const self& rhs) const
	{
		return !operator==(rhs);
	}
	
};


template<typename T>
class forward_list
{
public:
	typedef forward_list<T> self;
	typedef __ListNode<T>* pNode;
	typedef T value_type;
	typedef T& reference;
	typedef __forward_list_iterator<T> iterator;

	forward_list();

	forward_list(const forward_list<T>& list);
	~forward_list()
	{
		destroy();
	}

	void extend(const forward_list<T>& list);

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

		forward_list<T>* cur_node = head;

		do
		{
			cur_node = cur_node->next;
			pos--;
		} while (pos > 0);

		return cur_node->data;
	}

	size_t getPosition(T& ele)
	{
		forward_list<T>* cur_node = head;
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

	forward_list<T>* getAddress(T ele)
	{

		forward_list<T>* cur_node = head->next;

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
			forward_list<T>* cur_node = head;
			while (1)
			{
				if (cur_node->next==nullptr)
				{
					break;
				}
				cur_node = cur_node->next;
			}
			forward_list<T>* newNode = new forward_list<T>();
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
		forward_list<T>* cur_node = head;
		for (int i = 1; i<=pos-1;i++)
		{
			cur_node = cur_node->next;
		}
		forward_list<T>* newNode = new forward_list<T>();
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

		forward_list<T>* cur_node = head;

		for (int i = 1; i <= pos - 1; i++)
		{
			cur_node = cur_node->next;
		}
		forward_list<T>* temp = cur_node->next;
		cur_node->next = (cur_node->next)->next;
		delete temp;
	}

	void removeNodeByValue(T& ele, bool rmAll = false)
	{
		forward_list<T>* cur_node = head;

		while ((cur_node->next) != nullptr)
		{
			if ((cur_node->next)->data == ele)
			{
				forward_list<T>* temp = cur_node->next;
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
		forward_list<T>* cur_node = head->next;
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
		forward_list<T>* first_node = head->next;
		forward_list<T>* temp;
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
	pNode head;
	size_t length;
};




#endif