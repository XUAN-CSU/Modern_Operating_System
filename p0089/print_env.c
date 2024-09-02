#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[], char *envp[])
{
    //if (argv < 2) {
    //    printf("Usage: %s <parameter>\n", argc[0]);
    //    return 1;
    //}
    //printf("%s\n", argc[1]);

    char *my_data = getenv("MY_DATA");
    if (my_data != NULL) {
        printf("MY_DATA = %s\n", my_data);
    } else {
        printf("MY DATA environment variable is not set.\n");
    }

    return 0;
}
