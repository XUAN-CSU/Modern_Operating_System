#include <stdio.h>
#include <unistd.h>         // for the chdir

#include <sys/stat.h>       // for the mkdir
#include <sys/types.h>      // for the mkdir


#define PATH "./chdir_test/test"
#define NEW_DIR "newdir"
void test()
{
    if (chdir(PATH) == 0) {
        printf("change dir success\n");
        if (mkdir(NEW_DIR, 0755) == 0) {
            printf("create new dir success\n");
        } else {
            printf("create new dir failed\n");
            perror("mkdir failed\n");
        }
    } else {
        perror("chdir failed\n");
    }

}

int main()
{
    test();

    return 0;

}

        
            
