/*------------------------------------------------------------

•	Алгоритмы основных операций АТД  (вставки, удаления и поиска) реализуются в итерационной форме.
•	Схема операции обхода: Lt → t → Rt.
•	Дополнительная операция: определение узла в дереве с максимальной глубиной.

------------------------------------------------------------*/


#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "BTree.h"
#include <ctime>

using namespace std;

typedef int D;
typedef int K;

int main()
{
	srand(time(nullptr));
	BTree<D, K> *T = new BTree<D, K>();

	while (true)
	{
		int select = 0;
		cout << "Total nodes count: " << T->GetNodesCount() << endl << endl;
		cout << "MENU" << endl;
		cout << "1. Add" << endl;
		cout << "2. Delete" << endl;
		cout << "3. Search" << endl;
		cout << "4. Get max depth" << endl;
		cout << "5. Print" << endl;
		cout << "6. Lt_t_Rt" << endl;
		cout << "7. Self-fill" << endl;
		cout << "8. Delete tree" << endl;
		cout << "9. Is empty" << endl;
		cout << "0. Exit" << endl;

		cin >> select;

		if (select == 0) break;

		if (select == 1)
		{
			K k;
			D d;
			cout << "Input key " << typeid(k).name() << endl;
			cin >> k;
			cout << "Input data " << typeid(d).name() << endl;
			cin >> d;
			T->addChild(k, d);
		}
		if (select == 2)
		{
			K k;
			cout << "Input key " << typeid(k).name() << endl;
			cin >> k;
			cout << (T->del(k) ? "Ok" : "Key not found") << endl;
		}
		if (select == 3)
		{
			K k;
			cout << "Input key " << typeid(k).name() << endl;
			cin >> k;
			cout << T->find(k) << endl;
		}
		if (select == 4)
		{
			cout << "Max depth is " << T->getMaxDepth() << endl;
		}
		if (select == 5)
		{
			T->print();
		}
		if (select == 6)
		{
			T->Obhod();
		}
		if (select == 7)
		{
			int count;
			cout << "Input count of nodes" << endl;
			cin >> count;
			cout << "Please wait..." << endl;
			for (int i = 0; i < count; i++)
			{
				T->addChild(rand() % 20, rand());
			}
			cout << "Done!" << endl;
		}

		if (select == 8)
		{
			cout << (T->delete_All() ? "Ok" : "Tree empty") << endl;
		}
		if (select == 9)
		{
			cout << (T->isEmpty() ? "Tree is empty" : "Tree not empty") << endl;
		}
		system("PAUSE");
		system("cls");
	}

	return EXIT_SUCCESS;
}