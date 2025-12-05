#include <iostream>
#include <utility>
#include "pch.h"
#include "DynamicArray.h"
#include <cstdlib>

using namespace std;

int main()
{
	Array<int> a;
	for (int i = 0; i < 10; i++) {
		a.insert(i + 1);
	}


	for (int i = 0; i < a.size(); ++i) {
		a[i] *= 2;
	}


	a.remove(3);
	cout << a.size() << endl;
	cout << a[2] << endl;
	cout << "Is it work?" << endl;


	for (auto it = a.iterator(); ; it.next()) { //из-за семантики?
		cout << it.get() << endl;
		if (!it.hasNext()) {
			break;
		}
	}


	Array<string> str;
	for (int i = 0; i < 10; i++) {
		str.insert(to_string(i) + "f");
	}


	cout << "Is it work second two?" << endl;
	for (auto it = str.iterator(); ; it.next()) { //из-за семантики
		cout << it.get() << endl;
		if (!it.hasNext()) {
			break;
		}
	}
}