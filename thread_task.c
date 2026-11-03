#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void print_time()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[10];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 10, "%H:%M:%S", timeinfo);
    printf("[%s] ", buffer);
}

void *thread_func(void *arg)
{
    int num = *(int *)arg;
    print_time();
    printf("Поток %d: TID=%lu, PID=%d, PPID=%d\n", num, pthread_self(), getpid(), getppid());
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int n1 = 1, n2 = 2;

    print_time();
    printf("Главный поток: TID=%lu, PID=%d, PPID=%d\n", pthread_self(), getpid(), getppid());

    pthread_create(&t1, NULL, thread_func, &n1);
    pthread_create(&t2, NULL, thread_func, &n2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}