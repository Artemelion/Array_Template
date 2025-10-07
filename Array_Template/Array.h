#pragma once
#include <iostream>
using namespace std;

template <class T>
class Array
{
    T* data;
    int capacity;
    int count;
    int growthStep;
public:
    Array();
    Array(int initialCapacity);
    Array(const T* source, int sourceCount);
    void Print();
    int GetSize() const;
    void SetSize(int newCapacity, int grow = 1);
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

    void InsertAt(int position, const T& value);
    void RemoveAt(int position);

    void Append(const Array& other);

    T* GetData();
    const T* GetData() const;
};

template <class T>
Array<T>::Array() : data(nullptr), capacity(0), count(0), growthStep(1) {}

template <class T>
Array<T>::Array(int initialCapacity)
{
    if (initialCapacity < 0)
    {
        initialCapacity = 0;
    }

    capacity = initialCapacity;
    count = 0;
    growthStep = 1;

    if (capacity > 0)
    {
        data = new T[capacity]{};
    }
    else
    {
        data = nullptr;
        capacity = 0;
    }
}

template <class T>
Array<T>::Array(const T* source, int sourceCount)
{
    growthStep = 1;

    if (sourceCount < 0)
    {
        sourceCount = 0;
    }

    capacity = sourceCount;

    if (capacity > 0)
    {
        data = new T[capacity]{};
    }
    else
    {
        data = nullptr;
        capacity = 0;
    }

    count = capacity;

    if (source != nullptr)
    {
        for (int i = 0; i < count; i = i + 1)
        {
            data[i] = source[i];
        }
    }
}

template <class T>
Array<T>::Array(const Array& other)
{
    capacity = other.capacity;
    count = other.count;
    growthStep = other.growthStep;

    if (capacity > 0)
    {
        data = new T[capacity]{};
    }
    else
    {
        data = nullptr;
    }

    for (int i = 0; i < count; i = i + 1)
    {
        data[i] = other.data[i];
    }

    cout << "Copy constructor!" << endl;
}

template <class T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this != &other)
    {
        T* tmp = nullptr;

        if (other.capacity > 0)
        {
            tmp = new T[other.capacity]{};
        }

        for (int i = 0; i < other.count; i = i + 1)
        {
            tmp[i] = other.data[i];
        }

        if (data != nullptr)
        {
            delete[] data;
        }

        data = tmp;
        capacity = other.capacity;
        count = other.count;
        growthStep = other.growthStep;
    }

    cout << "Copy= operator!" << endl;
    return *this;
}

template <class T>
void Array<T>::Print()
{
    for (int i = 0; i < count; i = i + 1)
    {
        cout << data[i] << "\t";
    }
    cout << endl;
}

template <class T>
int Array<T>::GetSize() const
{
    return capacity;
}

template <class T>
void Array<T>::SetSize(int newCapacity, int grow)
{
    if (newCapacity < 0)
    {
        newCapacity = 0;
    }
    if (grow <= 0)
    {
        grow = 1;
    }

    if (newCapacity != capacity)
    {
        T* newData = nullptr;

        if (newCapacity > 0)
        {
            newData = new T[newCapacity]{};
        }

        int toCopy;

        if (count < newCapacity)
        {
            toCopy = count;
        }
        else
        {
            toCopy = newCapacity;
        }

        for (int i = 0; i < toCopy; i = i + 1)
        {
            newData[i] = data[i];
        }

        if (data != nullptr)
        {
            delete[] data;
        }

        data = newData;
        capacity = newCapacity;
        count = toCopy;
    }

    growthStep = grow;
}

template <class T>
Array<T>::~Array()
{
    if (data != nullptr)
    {
        delete[] data;
    }

    data = nullptr;
    capacity = 0;
    count = 0;
    growthStep = 1;
}

template <class T>
bool Array<T>::IsEmpty() const
{
    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
int Array<T>::GetUpperBound() const
{
    if (count == 0)
    {
        return -1;
    }
    else
    {
        return count - 1;
    }
}

template <class T>
T& Array<T>::GetAt(int index)
{
    if (index >= 0 && index < count)
    {
        return data[index];
    }

    cout << "Index out of range" << endl;
    static T defaultValue = T();
    return defaultValue;
}

template <class T>
const T& Array<T>::GetAt(int index) const
{
    if (index >= 0 && index < count)
    {
        return data[index];
    }

    cout << "Index out of range" << endl;
    static T defaultValue = T();
    return defaultValue;
}

template <class T>
void Array<T>::SetAt(int index, const T& value)
{
    if (index >= 0 && index < count)
    {
        data[index] = value;
    }
}

template <class T>
T& Array<T>::operator[](int index)
{
    return GetAt(index);
}

template <class T>
const T& Array<T>::operator[](int index) const
{
    return GetAt(index);
}

template <class T>
void Array<T>::FreeExtra()
{
    if (capacity > count)
    {
        T* newData = nullptr;

        if (count > 0)
        {
            newData = new T[count]{};
        }

        for (int i = 0; i < count; i = i + 1)
        {
            newData[i] = data[i];
        }

        if (data != nullptr)
        {
            delete[] data;
        }

        data = newData;
        capacity = count;
    }
}

template <class T>
void Array<T>::RemoveAll()
{
    if (data != nullptr)
    {
        delete[] data;
    }

    data = nullptr;
    capacity = 0;
    count = 0;
}

template <class T>
int Array<T>::Add(const T& value)
{
    if (count == capacity)
    {
        int newCapacity = capacity + growthStep;
        if (newCapacity <= capacity)
        {
            newCapacity = capacity + 1;
        }
        SetSize(newCapacity, growthStep);
    }

    data[count] = value;
    count = count + 1;
    return count - 1;
}

template <class T>
void Array<T>::InsertAt(int position, const T& value)
{
    if (position < 0)
    {
        return;
    }
    if (position > count)
    {
        return;
    }

    if (count == capacity)
    {
        int newCapacity = capacity + growthStep;
        if (newCapacity <= capacity)
        {
            newCapacity = capacity + 1;
        }
        SetSize(newCapacity, growthStep);
    }

    for (int i = count; i > position; i = i - 1)
    {
        data[i] = data[i - 1];
    }

    data[position] = value;
    count = count + 1;
}

template <class T>
void Array<T>::RemoveAt(int position)
{
    if (position < 0)
    {
        return;
    }
    if (position >= count)
    {
        return;
    }

    for (int i = position; i < count - 1; i = i + 1)
    {
        data[i] = data[i + 1];
    }

    count = count - 1;
}

template <class T>
void Array<T>::Append(const Array& other)
{
    if (other.count == 0)
    {
        return;
    }

    if (this == &other)
    {
        int itemsToCopy = count;

        if (itemsToCopy == 0)
        {
            return;
        }

        T* tmp = new T[itemsToCopy]{};

        for (int i = 0; i < itemsToCopy; i = i + 1)
        {
            tmp[i] = data[i];
        }

        int required = count + itemsToCopy;

        if (required > capacity)
        {
            SetSize(required, growthStep);
        }

        for (int i = 0; i < itemsToCopy; i = i + 1)
        {
            data[count + i] = tmp[i];
        }

        count = count + itemsToCopy;
        delete[] tmp;
        return;
    }

    int required = count + other.count;

    if (required > capacity)
    {
        SetSize(required, growthStep);
    }

    for (int i = 0; i < other.count; i = i + 1)
    {
        data[count + i] = other.data[i];
    }

    count = count + other.count;
}

template <class T>
T* Array<T>::GetData()
{
    return data;
}

template <class T>
const T* Array<T>::GetData() const
{
    return data;
}
