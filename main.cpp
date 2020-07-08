#include <iostream>
#include <vector>
#include <string>
#include"./SeqList/SeqList.h"
#include"./LinkedList/LinkedList.h"

using namespace std;

int SeqList_main()
{
	SeqList L = SeqList();
	int choice;
	int x, y;
	do
	{
		cout << "\n0.Quit";
		cout << "\n1.Insert";
		cout << "\n2.Remove by element";
		cout << "\n3.Remove by position";
		cout << "\n4.Clear";
		cout << "\n5.Print";

		cout << "\n\nEnter Your Choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter the element to be inserted : ";
			cin >> x;
			L.insert(x);
			break;
		case 2:
			cout << "\nEnter the element to be removed : ";
			cin >> x;
			cout << "\nEnter the mode to be removed (1 for first, 2 for all): ";
			cin >> y;
			y == 1 ? L.remove_first(x) : L.remove_all(x);
			break;
		case 3:
			cout << "\nEnter the position to be removed : ";
			cin >> x;
			L.remove(x);
			break;
		case 4:
			L.clear();
			break;
		case 5:
			L.print();
			break;
		}
	} while (choice != 0);
	return 0;
}

int LinkedList_main()
{
	LinkedList L = LinkedList();
	int choice;
	int x, y, pos;
	pLnode add;
	do
	{
		cout << "\n0.Quit";
		cout << "\n1.Insert";
		cout << "\n2.Search";
		cout << "\n3.Remove by element";
		cout << "\n4.Remove by position";
		cout << "\n5.Clear";
		cout << "\n6.Print";

		cout << "\n\nEnter Your Choice : ";
		cin >> choice;
		try
		{
			switch (choice)
			{
			case 1:
				cout << "\nEnter the element to be inserted : ";
				cin >> x;
				cout << "\nEnter the position to be inserted (\"-1\" to the tail): ";
				cin >> y;
				L.insert(x, y);
				break;
			case 2:
				cout << "\nEnter the element to be search : ";
				cin >> x;
				pos = L.getPosition(x);
				add = L.getAddress(x);
				cout << "\nThe element is at " << x << "-th position of the list.";
				cout << "\nIts address is " << add;
				break;
			case 3:
				cout << "\nEnter the element to be removed : ";
				cin >> x;
				cout << "\nEnter the mode to be removed (1 for first, 2 for all): ";
				cin >> y;
				y == 1 ? L.removeNodeByValue(x) : L.removeNodeByValue(x, true);
				break;
			case 4:
				cout << "\nEnter the position to be removed : ";
				cin >> x;
				L.removeNodeByPosition(x);
				break;
			case 5:
				L.clear();
				break;
			case 6:
				L.print();
				break;
			}
		}
		catch (string e)
		{
			cout << e << endl;
		}
		
	} while (choice != 0);
	return 0;
}