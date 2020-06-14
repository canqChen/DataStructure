#include <iostream>
#include <vector>
#include <string>
#include"./SeqList/SeqList.h"

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