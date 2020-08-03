#pragma once
#include<iostream>
#include<cstring>

using namespace std;

#define MAXLENGTH 255

class MyString
{
public:
	MyString()
	{
		str = new char[capacity];
		*str = '\0';
	}

	MyString(const char* s)
	{
		int newCap = strlen(s);
		if (newCap >= capacity)
			capacity = newCap + 1;
		str = new char[capacity];
		strcpy(str, s);
	}

	MyString(const MyString& s)
	{
		int newCap = strlen(s.c_str());
		if (newCap >= capacity)
			capacity = newCap + 1;
		str = new char[capacity];
		strcpy(str, s.c_str());
	}

	const char at(int n)
	{
		if (n > strlen(str))
			throw string("out of range");
		return str[n - 1];
	}

	void assign(const char* s)
	{
		int newCap = strlen(s);
		if (newCap >= capacity)
			capacity = newCap + 1;
		if (str != nullptr)
			delete[] str;
		str = new char[capacity];
		strcpy(str, s);
	}

	void assign(const MyString& s)
	{
		int newCap = strlen(s.c_str());
		if (newCap >= capacity)
			capacity = newCap + 1;
		if (str != nullptr)
			delete[] str;
		str = new char[capacity];
		strcpy(str, s.c_str());
	}

	void append(const char* s)
	{
		int newLen = strlen(s);
		int curLen = strlen(str);
		if (newLen + curLen >= capacity)
			capacity = newLen + curLen + 1;
		if (str != nullptr)
			delete[] str;
		str = new char[capacity];
		strcat(str, s);
	}

	void append(const MyString& s)
	{
		int newLen = strlen(s.c_str());
		int curLen = strlen(str);
		if (newLen + curLen >= capacity)
		{
			capacity = newLen + curLen + 1;
			char* tmp = new char[capacity];
			int i = 0, j = 0;
			const char* s_str = s.c_str();
			while (str[i] != '\0')
			{
				tmp[i] = str[i];
				i++;
			}
			while (s_str[j] != 0)
			{
				tmp[i] = s_str[j];
				i++;
				j++;
			}
			tmp[i] = '\0';
			delete[]str;
			str = tmp;
		}
		else
		{
			strcat(str, s.c_str());
		}
	}

	int findBF(const char* s, int pos = 1)
	{
		int i = pos-1, j = 0;
		int sLen = strlen(s);
		int len = length();
		if (pos>=len)
		{
			throw string("overflow!");
		}
		while (i < len && j < sLen)
		{
			if (str[i] == s[j])
			{
				i++;
				j++;
			}
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
		if (j >= sLen)
			return i - sLen + 1;
		else
			return 0;
	}

	int findBF(const MyString& s, int pos=1)
	{
		return findBF(s.c_str(), pos);
	}

	int* getNext(const char* pat)
	{
		// get next[]
		int len = strlen(pat);
		int* next = new int[len];
		int i = 2, k = 0;
		next[0] = next[1] = 0;
		while (i < len)
		{
			if (k==0||pat[i]==pat[k])
			{
				i++;
				k++;
				next[i] = k;
			}
			else
			{
				k = next[k];
			}
		}

		return next;
	}

	int findKMP(const char* s, int pos = 1)
	{
		int i = pos - 1, j = 0;
		int sLen = strlen(s);
		int len = length();
		if (pos >= len)
		{
			throw string("overflow!");
		}

		int* next = getNext(s);

		while (i < len && j < sLen)
		{
			if (str[i] == s[j])
			{
				i++;
				j++;
			}
			else
			{
				j = next[j];
			}
		}

		delete[] next;
		if (j >= sLen)
			return i - sLen + 1;
		else
			return 0;
	}

	int findKMP(const MyString& s, int pos = 1)
	{
		return findKMP(s.c_str(), pos);
	}

	int length()
	{
		return strlen(str);
	}

	int maxSize() const
	{
		return capacity;
	}

	bool empty()
	{
		return *str == '\0' ? true : false;
	}

	const char* c_str() const
	{
		return str;
	}

	const char operator [] (int n)
	{
		return this->at(n);
	}

	MyString& operator = (const MyString& s)
	{
		if (this != &s)
		{
			this->assign(s);
			return *this;
		}
	}

	MyString& operator = (const char* s)
	{
		this->assign(s);
		return *this;
	}

	MyString& operator + (const char* s)
	{
		MyString newString(strcat(this->str, s));
		return newString;
	}

	MyString& operator + (const MyString& s)
	{
		MyString newString(strcat(this->str, s.c_str()));
		return newString;
	}

	MyString& operator = (const char* s)
	{
		this->assign(s);
		return *this;
	}

	MyString& operator += (const char* s)
	{
		this->append(s);
		return *this;
	}

	MyString& operator += (const MyString& s)
	{
		if (this == &s)
		{
			int len = strlen(str);
			if (len * 2 >= capacity)
				capacity = len * 2 + 1;
			char* tmp = new char[capacity];
			int i = 0;
			while (str[i] != '\0')
			{
				tmp[i] = str[i];
				tmp[i + len] = str[i];
				i++;
			}
			tmp[i + len] = '\0';
			delete[]str;
			str = tmp;
		}
		else
		{
			this->append(s);
		}
		return *this;
	}

	bool operator == (const MyString& s)
	{
		return strcmp(this->str, s.c_str()) == 0 ? true : false;
	}

	bool operator > (const MyString& s)
	{
		return strcmp(this->str, s.c_str()) > 0 ? true : false;
	}

	bool operator < (const MyString& s)
	{
		return strcmp(this->str, s.c_str()) < 0 ? true : false;
	}

	bool operator >= (const MyString& s)
	{
		return strcmp(this->str, s.c_str()) >= 0 ? true : false;
	}

	bool operator <= (const MyString& s)
	{
		return strcmp(this->str, s.c_str()) <= 0 ? true : false;
	}

	~MyString()
	{
		delete[]str;
	}

private:
	char* str = nullptr;
	int capacity = MAXLENGTH;
};
