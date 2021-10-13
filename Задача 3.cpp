// Задача 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*Дадено е цяло число N, следвано от N на брой двойки цели числа – двойките представят плочки от домино. Всяка плочка може да се върти 
(т.е. първото число да става второ и обратно).

Намерете такова последователно разположение на максимален брой от плочките в редица, така че за всяка плочка (без първата) първото число 
съвпада с второто число на предходната плочка. Изведете на екрана получената редица. Ако има повече от една редица с максимална дължина 
изведете която и да е от възможностите.*/

#include <iostream>
using namespace std;
const unsigned short tiles = 2;

unsigned short** copyMat(unsigned short** dominoe, unsigned short numOfDominoe)
{
    unsigned short** copy = new(nothrow)unsigned short*[numOfDominoe];
    if (!copy)
        return NULL;
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        copy[i] = new(nothrow)unsigned short[tiles];
        if (!copy[i])
            return NULL;
    }
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        for (size_t j = 0; j < tiles; ++j)
        {
            copy[i][j] = dominoe[i][j];
        }
    }
    return copy;
}
unsigned short** create(unsigned short numOfDominoe)
{
    unsigned short** dominoe = new(nothrow)unsigned short*[numOfDominoe];
    if (!dominoe)
        return NULL;
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        dominoe[i] = new(nothrow)unsigned short[tiles];
        if (!dominoe[i])
            return NULL;
    }
    return dominoe;
}
unsigned short** fillTiles(unsigned short** dominoe, unsigned short numOfDominoe)
{
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        for (size_t j = 0; j < tiles; ++j)
        {
            cin >> dominoe[i][j];
        }
    }
    return dominoe;
}
void release(unsigned short** dominoe, unsigned short numOfDominoe)
{
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        delete[] dominoe[i];
    }
    delete[] dominoe;
}
unsigned short countingChain(unsigned short** dominoe, unsigned short numOfDominoe, unsigned short domIndex, unsigned short &chain, unsigned short link,
    unsigned short attached, unsigned short index)
{
    unsigned short temp;
    if (index > 0)
    {
        for (size_t k = 0; k < tiles; ++k)
        {
            temp = dominoe[0][k];
            dominoe[0][k] = dominoe[index][k];
            dominoe[index][k] = temp;
        }
    }
    for (size_t i = 1; i < numOfDominoe; ++i)
    {
        for (size_t j = 0; j < tiles; ++j)
        {
            if (link == dominoe[i][j])
            {
                ++chain;
                for (size_t k = 0; k < tiles; ++k)
                {
                    temp = dominoe[domIndex][k];
                    dominoe[domIndex][k] = dominoe[i][k];
                    dominoe[i][k] = temp;
                }
                if (j == 1)
                {
                    attached = dominoe[domIndex][j];
                    link = dominoe[domIndex][j - 1];
                }
                else
                {
                    attached = dominoe[domIndex][j];
                    link = dominoe[domIndex][j + 1];
                }
                j = tiles;
                i = domIndex;
                ++domIndex;
            }
        }
    }
    return chain;
}
void printChain(unsigned short** dominoe, unsigned short numOfDominoe, unsigned short index, unsigned short start, unsigned short next, unsigned short domIndex)
{
    unsigned short temp;
    if (index > 0)
    {
        for (size_t k = 0; k < tiles; ++k)
        {
            temp = dominoe[0][k];
            dominoe[0][k] = dominoe[index][k];
            dominoe[index][k] = temp;
        }
    }
    cout << start << "-" << next << " ";
    for (size_t i = 1; i < numOfDominoe; ++i)
    {
        for (size_t j = 0; j < tiles; ++j)
        {
            if (next == dominoe[i][j])
            {
                for (size_t k = 0; k < tiles; ++k)
                {
                    temp = dominoe[domIndex][k];
                    dominoe[domIndex][k] = dominoe[i][k];
                    dominoe[i][k] = temp;
                }
                if (j == 1)
                {
                    start = dominoe[domIndex][j];
                    next = dominoe[domIndex][j - 1];
                }
                else
                {
                    start = dominoe[domIndex][j];
                    next = dominoe[domIndex][j + 1];
                }
                cout << start << "-" << next << " ";
                j = tiles;
                i = domIndex;
                ++domIndex;
            }
        }
    }
}

int main()
{

    unsigned short numOfDominoe;
    cin >> numOfDominoe;
    unsigned short** dominoe = create(numOfDominoe);
    fillTiles(dominoe, numOfDominoe);

    size_t domIndex = 1;
    unsigned short link;
    unsigned short attached = NULL;
    unsigned short numOfChains = numOfDominoe * 2;
    unsigned short* chains = new(nothrow)unsigned short[numOfChains];
    if (!chains)
        return -1;
    unsigned short* start = new(nothrow)unsigned short[numOfChains];
    if (!start)
        return -1;
    unsigned short* next = new(nothrow)unsigned short[numOfChains];
    if (!next)
        return -1;
    unsigned short temp;
    unsigned h = 0;
    for (size_t i = 0; i < numOfDominoe; ++i)
    {
        for (size_t j = 0; j < tiles; ++j)
        {
            link = dominoe[i][j];
            if (j == 1)
            {
                start[h] = dominoe[i][j - 1];
                next[h] = link;
            }
            else
            {
                start[h] = dominoe[i][j + 1];
                next[h] = link;
            }
            unsigned short chain = 1;
            unsigned short** copy = copyMat(dominoe, numOfDominoe);
            chains[h] = countingChain(copy, numOfDominoe, domIndex, chain, link, attached, i);
            release(copy, numOfDominoe);
            ++h;
        }
    }
    unsigned longestChain = 1;
    for (size_t i = 0; i < numOfChains; ++i)
    {
        if (longestChain < chains[i])
            longestChain = chains[i];
    }
    for (size_t i = 0; i < numOfChains; ++i)
    {
        if (longestChain == chains[i])
        {
            /*printChain(dominoe, numOfDominoe, i, start[i], next[i], domIndex);
            return 0;*/
            cout << "Not working. Last stages. Last function is broken. No time :(" << endl;
        }
        
    }
    
    delete[] chains;
    delete[] start;
    delete[] next;
    release(dominoe, numOfDominoe);
    return 0;
}