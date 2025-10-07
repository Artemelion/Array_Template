#include <iostream>
#include "Array.h"
using namespace std;

void Section(const char* title)
{
    cout << "\n" << title << "\n";
}

int main()
{
    Section("ctor default + IsEmpty");
    Array<int> a;
    if (a.IsEmpty())
    {
        cout << "a is empty\n";
    }
    cout << "capacity = " << a.GetSize() << ", upper = " << a.GetUpperBound() << endl;

    Section("SetSize + Add");
    a.SetSize(3, 2);
    cout << "capacity = " << a.GetSize() << endl;
    a.Add(10);
    a.Add(20);
    a.Add(30);
    a.Print();
    a.Add(40); // три места было, добавление 4-го проверит рост
    cout << "after Add, capacity = " << a.GetSize()
        << ", upper = " << a.GetUpperBound() << endl;
    a.Print();

    Section("operator[] / GetAt / SetAt");
    cout << "a[1] = " << a[1] << endl;
    cout << "GetAt(2) = " << a.GetAt(2) << endl;
    a.SetAt(1, 777);
    a.Print();

    Section("InsertAt / RemoveAt");
    a.InsertAt(0, 5);
    a.InsertAt(3, 55);
    a.Print();
    a.RemoveAt(2);
    a.Print();

    Section("FreeExtra");
    a.SetSize(a.GetSize() + 5, 2);
    cout << "capacity increased to " << a.GetSize() << endl;
    a.FreeExtra();
    cout << "capacity after FreeExtra = " << a.GetSize() << endl;

    Section("Append + copy/assign");
    int src[] = { 1, 2, 3, 4 };
    Array<int> b(src, 4);
    Array<int> c;
    c.Append(b);
    c.Print();

    Array<int> d = b;  // copy ctor
    d.Print();

    Array<int> e(1);
    e = b;             // operator=
    e.Print();

    Section("GetData");
    int* p = c.GetData();
    if (p != nullptr)
    {
        cout << "first of c = " << p[0] << endl;
    }

    Section("RemoveAll");
    c.RemoveAll();
    cout << "c capacity = " << c.GetSize() << ", upper = " << c.GetUpperBound() << endl;
    if (c.IsEmpty())
    {
        cout << "c is empty\n";
    }

    Section("Array<double>");
    Array<double> ad;
    ad.SetSize(2, 1);
    ad.Add(3.14);
    ad.Add(2.71);
    ad.InsertAt(1, 1.11);
    ad.Print();
    ad.FreeExtra();

    cout << "\nDone\n";
    return 0;
}
