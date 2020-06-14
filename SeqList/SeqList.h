
#include<iostream>

#define ElemType int
#define MAXSIZE 100

using namespace std;

class SeqList
{
public:
	SeqList()
	{
		length = 0;
		list = nullptr;
		Init();
	}
	void Init()
	{
		if (list != nullptr)
		{
			cout << "fail to initialize the seqlist, destroy it before initialization please." << endl;
		}

		list = new ElemType[MAXSIZE];
		if (list == nullptr)
		{
			cout << "fail to initialize the seqlist." << endl;
		}
	}

	void insert(ElemType ele, int pos = -1)
	{
		if (list == nullptr)
		{
			cout << "the list is not initialized!";
			return;
		}
		else if (length == MAXSIZE)
		{
			cout << "fail to insert new element into the list, the list is full!";
			return;
		}
		//insert
		if (pos == -1)  //default, insert into the tail
		{
			list[length++] = ele;
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
				list[i] = list[i - 1];
			}

			list[pos - 1] = ele;
			length++;
		}
	}

	void remove(int pos)
	{
		if (is_empty())
		{
			cout << "the list is empty!";
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
				list[i] = list[i + 1];
			}
			length--;
		}
	}

	void remove_first(ElemType ele)
	{
		if (is_empty())
		{
			cout << "the list is empty!";
			return;
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (list[i] == ele)
				{
					if (i != length - 1)  // remove the element in the middle, the last one just reduce the length
					{
						for (int j = i; j < length; j++)
						{
							list[j] = list[j + 1];
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
			cout << "the list is empty!";
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (list[i] == ele)
				{
					for (int j = i; j < length - 1; j++)
					{
						list[j] = list[j + 1];
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
			cout << list[i] << "    ";
		}
	}

	bool is_empty()
	{
		if (list == nullptr || length == 0)
		{
			return true;
		}
		return false;
	}

	void destroy()
	{
		if (list != nullptr)
		{
			delete[] list;
			list = nullptr;
			length = 0;
		}
		else
		{
			cout << "the list is not initialized!";
		}
	}

	void clear()
	{
		if (list != nullptr)
		{
			length = 0;
		}
		else
		{
			cout << "the list is not initialized!";
		}
	}

	~SeqList() {
		if (list != nullptr)
			delete[] list;
	}

private:
	ElemType* list;
	int length;
};
