#include <iostream>
#include <atomic>
#include "SharedPtr.hpp"

using namespace std;

int main() {
	Shared_Ptr<int> ptr(0);
	Shared_Ptr<int> ptr1(ptr);

	cout << "ptr count=" << ptr.use_count() << endl;
	cout << "ptr1 count=" << ptr1.use_count() << endl;

	Shared_Ptr<int> ptr2(ptr1);

	cout << "ptr count=" << ptr.use_count() << endl;
	cout << "ptr2 count=" << ptr2.use_count() << endl;



	ptr.reset();
	ptr2.reset();

	cout << "ptr count=" << ptr.use_count() << endl;
	cout << "ptr1 count=" << ptr1.use_count() << endl;
	cout << "ptr2 count=" << ptr2.use_count() << endl;

	Shared_Ptr<int> ptr3(15);

	ptr3.swap(ptr1);

	cout << ptr.use_count() << endl;
	cout << ptr1.use_count() << endl;

	return 0;
}
