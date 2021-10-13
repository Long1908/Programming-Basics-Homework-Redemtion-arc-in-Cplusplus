// Задача 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Задача 2.

В дните на засилена електронна комуникация е все по-важно да се използват надеждни средства за криптиране. Веско Синия, 
виден специалист по криптография, измислил следната процедура за криптиране – всяка буква (малка или главна латинска буква) се заменя 
с последователност от няколко (една или повече, но не повече от 10) букви според подадена таблица. Всички останали символи, както и буквите, 
които не са в таблицата не се променят. При кодиране не се прави разлика между големи и малки букви.

Вашата задача е да му помогнете, като напишете функция, която по подаден символен низ и таблица със съответствия между букви и символни низове 
за кодиране според горния алгоритъм, създава динамично символен низ с криптираното съдържание. Помислете какъв е най-добрият начин да подадете 
данните и да получите резултата от тази функция.

Напишете също функция, която по подаден, криптиран според горния алгоритъм, символен низ и таблица на съответствията декриптира и връща в 
динамично заделен с точната големина низ оригиналното съобщение. Ако текстът не може коректно да се декриптира да се върне празен резултат.

Напишете програма, която въвежда число K следвано от последователност от К двойки символ (малка или главна латинска буква) и последователност от 
символи с които този символ се криптира, двете разделени с интервал - по една такава двойка на ред.
Да се провери коректността на входа според условието.

След това трябва да се въвежда число N, следвано от N символни низа по един на ред (всеки не по-дълъг от 1000 символа). 
За всеки да се изведе на екрана криптирания му вид.

Накрая се въвежда число M, следвано от M криптирани символни низа по един на ред (всеки не по-дълъг от 1000 символа). 
За всеки да се изведе на екрана декриптирания му вид или текст “Bad string”, ако не може да се декриптира.*/

#include <iostream>
using namespace std;
const unsigned short sentenceMaxLenght = 1000;

char* createArr(unsigned int size)
{
    char* arr = new(nothrow)char[size];
    if (!arr)
        return 0;

    return arr;
}
char** createMat(unsigned int size)
{
    char** mat = new(nothrow)char* [size];
    if (!mat)
        return 0;
    for (size_t i = 0; i < size; ++i)
    {
        mat[i] = new(nothrow)char[sentenceMaxLenght];
        if (!mat[i])
            return 0;
    }
    return mat;
}
void releaseArr(char* arr)
{
    delete[] arr;
}
void releaseMat(char** mat, unsigned int size)
{
    for (size_t i = 0; i < size; ++i)
    {
        delete[] mat[i];
    }
    delete[] mat;
}
void decrypt(char* arr, char** encr, char** txt, unsigned int encrSize, unsigned int numSen)
{
    unsigned short senLen;
    unsigned short encLen;
    unsigned short diff = 'a' - 'A';
    unsigned short encrLetCount = 0;
    bool isLenOfEncr = false;
    for (size_t i = 0; i < numSen; ++i)
    {
        senLen = strlen(txt[i]);
        for (size_t j = 0; j < senLen; ++j)
        {
            for (size_t k = 0; k < encrSize; ++k)
            {
                isLenOfEncr = false;
                encLen = strlen(encr[k]);
                unsigned short incTxt = 0;
                encrLetCount = 0;
                for (size_t h = 0; h < encLen; ++h)
                {
                    if (txt[i][j + incTxt] == encr[k][h])
                    {
                        ++encrLetCount;
                        ++incTxt;
                    }
                    if (encrLetCount == encLen)
                    {
                        isLenOfEncr = true;
                        cout << arr[k];
                        k = encrSize;
                        j += (encLen - 1);
                    }
                }
            }
            if (!isLenOfEncr)
            {
                cout << txt[i][j];
            }
        }
    }
}
void encrypt(char* arr, char** txt, char** encr, unsigned encrSize, unsigned numSen)
{
    unsigned short senLen;
    bool foundLetter = false;
    unsigned short diff = 'a' - 'A';
    for (size_t i = 0; i < numSen; ++i)
    {
        senLen = strlen(txt[i]);
        for (size_t j = 0; j < senLen; ++j)
        {
            foundLetter = false;
            for (size_t k = 0; k < encrSize; ++k)
            {
                if (txt[i][j] >= 'A' && txt[i][j] <= 'Z')
                    txt[i][j] += diff;
                if (txt[i][j] == arr[k])
                {
                    cout << encr[k];
                    foundLetter = true;
                }
                if (foundLetter)
                    k == encrSize;
            }
            if (!foundLetter)
                cout << txt[i][j];
        }
    }
    cout << endl;
}
void fill(char* arr, char** mat, unsigned size)
{
    bool okSym, okCrypt;
    for (size_t i = 0; i < size; ++i)
    {
        do
        {
            cin >> arr[i];
            cin.ignore();
            cin.getline(mat[i], sentenceMaxLenght, '\n');
            okSym = true;
            okCrypt = true;
            if (i > 0)
            {
                for (size_t j = 0; j < i; ++j)
                {
                    if (arr[i] == arr[j])
                        okSym = false;
                    if (mat[i] == mat[j])
                        okCrypt == false;
                }
            }
            if ((okSym < 'a' || okSym > 'z') && (okSym < 'A' && okSym > 'Z'))
                okSym = false;
        } while ((!okSym) || (!okCrypt));
    }
}
void writeSentences(char** sen, unsigned int number)
{
    unsigned short senLen;
    cin.ignore();
    for (size_t i = 0; i < number; ++i)
    {
        cin.getline(sen[i], sentenceMaxLenght, '\n');
    }
}
void sortEncrMat(char* arr, char** mat, unsigned size)
{
    unsigned fNum, sNum;
    char buffChar;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            fNum = strlen(mat[i]);
            sNum = strlen(mat[j]);
            char* buffEncr = new(nothrow)char[sentenceMaxLenght];
            if (!buffEncr)
                return;
            if (fNum > sNum)
            {
                buffEncr = mat[i];
                buffChar = arr[i];
                mat[i] = mat[j];
                arr[i] = arr[j];
                mat[j] = buffEncr;
                arr[j] = buffChar;
                buffEncr = NULL;
            }
            delete[] buffEncr;
        }
    }
}

int main()
{
    unsigned short size, senNum, cryptNum, lenOfSen, lenOfCrypt;
    do
    {
        cout << "Number of Symbols: ";
        cin >> size;
    } while (size > 10);

    char* arr = createArr(size);
    char** mat = createMat(size);

    fill(arr, mat, size);
    sortEncrMat(arr, mat, size);

    cin >> senNum;
    char** sentences = createMat(senNum);
    writeSentences(sentences, senNum);
    encrypt(arr, sentences, mat, size, senNum);

    char** encrTxt = createMat(senNum);
    cin >> cryptNum;
    writeSentences(encrTxt, senNum);
    decrypt(arr, mat, encrTxt, size, senNum);

    releaseArr(arr);
    releaseMat(mat, size);
    releaseMat(sentences, senNum);
    releaseMat(encrTxt, senNum);

    return 0;
}

