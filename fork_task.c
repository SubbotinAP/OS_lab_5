#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void print_time() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[10];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 10, "%H:%M:%S", timeinfo);
    printf("[%s] ", buffer);
}

int main() {
    pid_t pid1, pid2;
    print_time();
    printf("Родитель: PID=%d, PPID=%d\n", getpid(), getppid());

    pid1 = fork();
    if (pid1 == 0) {
        print_time();
        printf("Ребенок 1: PID=%d, PPID=%d\n", getpid(), getppid());
        printf("\n--- Таблица маршрутизации ---\n");
        system("route -n");
        printf("-----------------------------\n\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        print_time();
        printf("Ребенок 2: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    print_time();
    printf("Родитель: дети завершены. Выполняю ps -x:\n\n");
    system("ps -x");
    return 0;
}