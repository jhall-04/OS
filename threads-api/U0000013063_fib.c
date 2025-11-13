#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common_threads.h"

void *mythread(void *arg) {
    int *args = (int *) arg;
    int *fib = malloc(sizeof(int) * (*args + 1));
    assert(fib != NULL);
    fib[0]=0;
    if ( *args > 0 )
    {
        fib[1] = 1;
        int i = 2;
        for (i = 2; i<=*args; i++)
        {
            fib[i] = fib[i-1] + fib[i-2];
        };
    }
    return (void *) fib;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: <nth Fibonacci>\n");
        return -1;
    }
    int n = atoi(argv[1]);
    int *fib = malloc(sizeof(int) * (n + 1));
    pthread_t p;
    Pthread_create(&p, NULL, mythread, &n);
    Pthread_join(p, (void **) &fib);
    printf("Fibonacci N: %d\n", fib[n-1]);
    free(fib);
    return 0;
}