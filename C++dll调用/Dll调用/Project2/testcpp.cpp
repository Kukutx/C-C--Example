#include <iostream>
#include"dllmain.h"

int main()
{
    printf("test cpp\n");
    std::cout << "Hello World!\n";
    printf("3+2 = %d\n", add(3, 2));
    printf("3-2 = %d\n", sub(3, 2));

    getchar();
}