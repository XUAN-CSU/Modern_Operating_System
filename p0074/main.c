#include <stdio.h>

void test()
{
    int a = 10;
    int *p = &a;
    printf("%ld\n", sizeof(a));
    printf("%ld\n", sizeof(p));
}

int main()
{
    test();
    return 0;
}
