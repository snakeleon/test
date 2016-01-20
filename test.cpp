#include <iostream>


typedef struct X
{
    int a;
    int b;
    int c;
    int d;
}X;


int main(void)
{
    X A = { 1, 2, 3, 4 };
    X B = { 5, 6, 7, 8 };
    X C = { 4, 5, 6, 7 };
    std::cout<<A.a <<A.b <<A.c <<A.d <<std::endl;
    std::cout<<B.a <<B.b <<B.c <<B.d <<std::endl;
    std::cout<<C.a <<C.b <<C.c <<C.d <<std::endl;
    //getch();

    return 0;
}
