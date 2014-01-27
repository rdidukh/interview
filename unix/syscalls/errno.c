#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    printf("errno address = %p\n", &errno);
    sleep(60);
    return 0;
}
