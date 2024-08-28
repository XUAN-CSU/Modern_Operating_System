#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int main()
{
    int a = 9;
    int b = SQUARE(a);

    printf("%d\n", b);

    return 0;
}
