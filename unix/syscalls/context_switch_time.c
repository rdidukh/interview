#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
/*
    0 - read end
    1 - write end
*/
int pipe_fd[2];

struct timeval write_time;
struct timeval read_time;

void * second_thread(void * args)
{
    char buf;    

    int rlen = read(pipe_fd[0], &buf, 1);

    if(rlen <= 0)
    {
        perror("read");
        return;
    }
    
    if(-1 == gettimeofday(&read_time, NULL))
    {
        perror("gettimeofday");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    pthread_attr_t attr;

/*
    memset(&write_time, 0, sizeof(write_time));
    memset(&read_time, 0, sizeof(read_time));
*/

    if (-1 == pthread_create(&thread, NULL, second_thread, (void *)argv))
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }



    if(pipe(pipe_fd) != 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
        
    usleep(500000);

    write(pipe_fd[1], "h", 1);

    if(-1 == gettimeofday(&write_time, NULL))
    {
        perror("gettimeofday");
        exit(EXIT_FAILURE);
    }

    int join = pthread_join(thread, NULL);

    printf("join = %i\n", join);

    if (join != 0)
    {
        printf("join = %i\n", join);
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    time_t sec =  read_time.tv_sec - write_time.tv_sec;
    suseconds_t usec = read_time.tv_usec - write_time.tv_usec;

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    if(usec < 0)
    {
        usec += 1000000;
        sec--;
    }

    printf("Result: %i s %i usec\n", sec, usec);

    return 0;
}


