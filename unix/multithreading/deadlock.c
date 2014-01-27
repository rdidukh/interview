#include <pthread.h>
#include <stdio.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void * thread1(void * args)
{
    printf("thread 1: started.\n");

    pthread_mutex_lock(&m1);
    
    printf("thread 1: mutex 1 locked.\n");

    usleep(100);

    pthread_mutex_lock(&m2);
    
    printf("thread 1: mutex 2 locked.\n");

    usleep(100);

    pthread_mutex_unlock(&m2);

    printf("thread 1: mutex 2 unlocked.\n");

    usleep(100);

    pthread_mutex_unlock(&m1);

    printf("thread 1: mutex 1 unlocked.\n");   

}

void * thread2(void * args)
{
    printf("thread 2: started.\n");

    pthread_mutex_lock(&m1);
    
    printf("thread 2: mutex 1 locked.\n");

    usleep(100);

    pthread_mutex_lock(&m2);
    
    printf("thread 2: mutex 2 locked.\n");

    usleep(100);

    
    pthread_mutex_unlock(&m2);

    printf("thread 2: mutex 2 unlocked.\n");

    usleep(100);

    pthread_mutex_unlock(&m1);

    printf("thread 2: mutex 1 unlocked.\n");
}

int main(int argc, char* argv[])
{
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}


