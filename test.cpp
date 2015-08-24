#include <stdio.h>
#include <iostream>

class a
{
    public:
        int b(int);
};

int main()
{
    printf("Helo World!\n");
    std::cout<<"Hello World!"<<std::endl;
    a b;
    b.b(0);
    a *p;
    p->b(1);
    return 0;
}
