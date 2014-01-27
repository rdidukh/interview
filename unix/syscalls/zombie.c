#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid == 0)
    {
        printf("Child process.\n");
        exit(EXIT_SUCCESS);
    }      
    else
    {
        printf("Parent process.\n");
        sleep(30);
        exit(EXIT_SUCCESS);
    }    

}


