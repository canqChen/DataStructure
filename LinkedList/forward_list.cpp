#include"forward_list.h"



template<typename T>
forward_list<T>::forward_list() : head(nullptr), length(0)
{
	head = new forward_list<T>();
}

template<typename T>
forward_list<T>::forward_list(const forward_list<T>& list)
{
	destroy();
	this->head = new forward_list<T>();
	this->head->next = nullptr;
	this->length = list.length;

	const forward_list<T>* l_head = list.head;
	forward_list<T>* cur_node = head;

	forward_list<T>* l_cur_node = l_head->next;
	while (l_cur_node != nullptr)
	{
		forward_list<T>* new_node = new forward_list<T>();
		new_node->data = l_cur_node->data;
		new_node->next = nullptr;

		cur_node->next = new_node;

		cur_node = cur_node->next;
		l_cur_node = l_cur_node->next;
	}
}

template<typename T>
void forward_list<T>::extend(const forward_list<T>& list)
{
	this->length += list.length;

	const forward_list<T>* l_head = list.head;
	forward_list<T>* cur_node = head;

	while (cur_node->next != nullptr)
	{
		cur_node = cur_node->next;
	}

	forward_list<T>* l_cur_node = l_head->next;
	while (l_cur_node != nullptr)
	{
		forward_list<T>* new_node = new forward_list<T>();
		new_node->data = l_cur_node->data;
		new_node->next = nullptr;

		cur_node->next = new_node;

		cur_node = cur_node->next;
		l_cur_node = l_cur_node->next;
	}
}

template<typename T>
void forward_list<T>::destroy()
{
	forward_list<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
	}
	length = 0;
}