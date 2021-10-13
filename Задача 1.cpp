// Задача 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Задача 1.
a) Напишете функция, която по подадени две цели числа проверява дали първото е по-малко от второто по брой единични
битове на четни позиции в двоичния запис на числата (най-младшия бит е на позиция 0). Ако двете числа имат еднакъв брой
единични битове на четни позиции да се сравни броя единични битове на нечетни позиции.

b) Напишете функция, която подрежда в намаляващ ред масив от цели числа, според горната наредба.

c) Напишете програма, която:
    *въвежда цяло, положително число N и след това масив от N цели числа
    *сортира въведения масив, посредством горната функция
    *след това премахва от него всички елементи, които не са уникални според горното сравнение.
    *извежда на екрана сортирания масив, както и резултатния масив, след премахване на еднаквите числа.*/

#include <iostream>
using namespace std;

void releaseNumbers(int* arr, unsigned int &size)
{
    unsigned short fNumBitCounter;
    unsigned short sNumBitCounter;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            fNumBitCounter = 0;
            sNumBitCounter = 0;
            for (size_t k = 0; k < 32; k += 2)
            {
                if (arr[i] & (1 << k))
                    ++fNumBitCounter;
                if (arr[j] & (1 << k))
                    ++sNumBitCounter;
            }
            if (fNumBitCounter == sNumBitCounter)
            {
                for (size_t k = 1; k < 32; k += 2)
                {
                    if (arr[i] & (1 << k))
                        ++fNumBitCounter;
                    if (arr[j] & (1 << k))
                        ++sNumBitCounter;
                }
                if (fNumBitCounter == sNumBitCounter)
                {
                    for (size_t h = i; h < size; ++h)
                    {
                        if ((h + 2) < size)
                            arr[h] = arr[h + 2];
                    }
                    size -= 2;
                }
            }
        }
    }
}
void sortByBit(int* arr, unsigned int size)
{
    int buffer;
    unsigned short fNumBitCounter;
    unsigned short sNumBitCounter;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            fNumBitCounter = 0;
            sNumBitCounter = 0;
            for (size_t k = 0; k < 32; k += 2)
            {
                if (arr[i] & (1 << k))
                    ++fNumBitCounter;
                if (arr[j] & (1 << k))
                    ++sNumBitCounter;
            }
            if (fNumBitCounter == sNumBitCounter)
            {
                for (size_t k = 1; k < 32; k += 2)
                {
                    if (arr[i] & (1 << k))
                        ++fNumBitCounter;
                    if (arr[j] & (1 << k))
                        ++sNumBitCounter;
                }
                if(fNumBitCounter < sNumBitCounter)
                {
                    buffer = arr[i];
                    arr[i] = arr[j];
                    arr[j] = buffer;
                }
            }
            else
            {
                if (fNumBitCounter < sNumBitCounter)
                {
                    buffer = arr[i];
                    arr[i] = arr[j];
                    arr[j] = buffer;
                }
            }
        }
    }
}
void print(int* arr, unsigned int size)
{
    for (size_t i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void fill(int* arr, unsigned int size)
{
    int element;
    for (size_t i = 0; i < size; ++i)
    {
        cin >> element;
        arr[i] = element;
    }
}
int* create(unsigned int size)
{
    int* arr = new(nothrow)int[size];
    if (!arr)
        return 0;

    return arr;
}
void release(int* arr)
{
    delete[] arr;
}


int main()
{
    unsigned size;
    cin >> size;
    int* arr = create(size);
    fill(arr, size);
    sortByBit(arr, size);
    print(arr, size);
    releaseNumbers(arr, size);
    print(arr, size);

    release(arr);

    return 0;
}