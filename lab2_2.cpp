#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    TwoInts i2 = { };

    i2.a = 5;
    i2.b = 7;

    std::cout << i2.a << std::endl; //5
    std::cout << i2.b << std::endl; //7
    
    StructWithArray s = { };
    s.arr[0] = 10;
    StructWithArray s1 = { };
    s1.arr[0] = 15;
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    std::cout << s.arr[0] << std::endl; //20 fiindca e indicata valoare elementului 0

    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl; //25 fiindca a fost modificat elementul 0

    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl; // 30 fiindca a fost modificat prin pointer

    sPointer = &s1;
    sPointer->arr[0] = 35;

    std::cout << s.arr[0] << std::endl; //30 fiidca sPointer arata spre s
    std::cout << s1.arr[0] << std::endl; //35 fiidca s1 a fost alocat prin sPointer

    StructWithArray structArray[2] = { };
    structArray[0].arr[3] = 77;

    structArray[1].someNumber = &structArray[0].arr[3];

    sPointer = &s;
    int* pointer = &sPointer->arr[3];
    s.arr[3] = 72;

    std::cout << *pointer; //72 fiidca pointerul a fost idicat ca al treilea element al arrayului
    StructWithArray memory;
    memset
