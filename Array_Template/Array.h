#pragma once
#include <iostream>
using namespace std;

template <class T>
class Array
{
    T* arr;
    int size;
    int realUsed;
    int growStep;
public:
    Array();
    Array(int size);
    Array(const T* mas, int size);
    void Print();
    int GetSize() const;
    void SetSize(int newSize, int grow = 1);
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other);

    bool IsEmpty() const;
    int GetUpperBound() const;

    T& GetAt(int index);
    const T& GetAt(int index) const;

    void SetAt(int index, const T& value);

    T& operator[](int index);
    const T& operator[](int index) const;

    void FreeExtra();

    void RemoveAll();

    int Add(const T& value);

    void InsertAt(int pos, const T& value);
    void RemoveAt(int pos);

    void Append(const Array& other);

    T* GetData();
    const T* GetData() const;


};

template <class T>
Array<T>::Array() : arr(nullptr), size(0), realUsed(0), growStep(1) {}

template <class T>
Array<T>::Array(int size)
{
    this->size = size;
    realUsed = 0;
    growStep = 1;
    if (this->size > 0)
    {
        arr = new T[this->size];
    }
    else
    {
        arr = nullptr;
        this->size = 0;
    }
}

template <class T>
Array<T>::Array(const T* mas, int size)
{
    growStep = 1;
    if (size < 0)
    {
        size = 0;
    }
    this->size = size;
    if (this->size > 0)
    {
        arr = new T[this->size];
    }
    else
    {
        arr = nullptr;
        this->size = 0;
    }
    realUsed = this->size;
    for (int i = 0; i < realUsed; i = i + 1)
    {
        arr[i] = mas[i];
    }
}

template <class T>
Array<T>::Array(const Array& other)
{
    size = other.size;
    realUsed = other.realUsed;
    growStep = other.growStep;
    if (size > 0)
    {
        arr = new T[size];
    }
    else
    {
        arr = nullptr;
    }
    for (int i = 0; i < realUsed; i = i + 1)
    {
        arr[i] = other.arr[i];
    }
    cout << "Copy constructor!" << endl;
}

template <class T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this != &other)
    {
        T* tmp = nullptr;
        if (other.size > 0)
        {
            tmp = new T[other.size];
        }
        for (int i = 0; i < other.realUsed; i = i + 1)
        {
            tmp[i] = other.arr[i];
        }
        if (arr != nullptr)
        {
            delete[] arr;
        }
        arr = tmp;
        size = other.size;
        realUsed = other.realUsed;
        growStep = other.growStep;
    }
    cout << "Copy= operator!" << endl;
    return *this;
}

template <class T>
void Array<T>::Print()
{
    for (int i = 0; i < realUsed; i = i + 1)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

template <class T>
int Array<T>::GetSize() const
{
    return size;
}

template <class T>
void Array<T>::SetSize(int newSize, int grow)
{
    if (newSize < 0)
    {
        newSize = 0;
    }
    if (grow <= 0)
    {
        grow = 1;
    }
    if (newSize != size)
    {
        T* newArr = nullptr;
        if (newSize > 0)
        {
            newArr = new T[newSize];
        }
        int toCopy;
        if (realUsed < newSize)
        {
            toCopy = realUsed;
        }
        else
        {
            toCopy = newSize;
        }
        for (int i = 0; i < toCopy; i = i + 1)
        {
            newArr[i] = arr[i];
        }
        if (arr != nullptr)
        {
            delete[] arr;
        }
        arr = newArr;
        size = newSize;
        realUsed = toCopy;
    }
    growStep = grow;
}

template <class T>
Array<T>::~Array()
{
    if (arr != nullptr)
    {
        delete[] arr;
    }
    arr = nullptr;
    size = 0;
    realUsed = 0;
    growStep = 1;
}
