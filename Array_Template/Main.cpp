#include <iostream>
#include <time.h>
#include "Array.h"
using namespace std;

int main()
{
	srand(time(0));

	int mas[3]{1,2,3};

	Array<int> object1;
	object1.Print();

	Array<int> object2 = object1;
	object2.Print();

	Array<int> object3;
	object3 = object2;
	object3.Print();



	return 0;
}