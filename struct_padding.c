#include <stdio.h>

struct A
{
    char a;
    char b;
    int i;
};

struct B
{
    char a;
    int i;
    char b;
};

struct C
{
    char a;
    int i;
};

struct D
{
    int i;
    char a;
};

int main()
{
    printf("sizeof(char) = %i\n", sizeof(char));
    printf("sizeof(int) = %i\n", sizeof(int));

    printf("sizeof(struct A) = %i\n", sizeof(struct A));
    printf("sizeof(struct B) = %i\n", sizeof(struct B));
    printf("sizeof(struct C) = %i\n", sizeof(struct C));
    printf("sizeof(struct D) = %i\n", sizeof(struct D));

    return 0;
}
