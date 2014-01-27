#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int counter = 0;

void *hello(void *args)
{
    printf("thread = %i ENTER\n", args);
    pthread_mutex_lock(&mutex);
    printf("thread = %i LOCKED\n", args);
    counter++;
    usleep(100);
    printf("thread = %i, counter = %i, &counter = %p\n", args, counter, &counter);
    pthread_mutex_unlock(&mutex);
    printf("thread = %i EXIT\n", args);
}

int main(int argc, char *argv[])
{

    pthread_t t1, t2;

    pthread_create(&t1, NULL, hello, (void *)1);
    pthread_create(&t2, NULL, hello, (void *)2);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;

}



