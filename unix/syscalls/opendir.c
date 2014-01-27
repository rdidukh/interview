#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    
    DIR *d = opendir(argv[1]);

    if(d == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    puts("ok\n");

    struct dirent *dir = readdir(d);

}


