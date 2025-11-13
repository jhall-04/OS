#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common_threads.h"

typedef struct {
    int a;
    int b;
} myarg_t;

typedef struct {
    int x;
    int y;
} myret_t;

    int fibb(n){
        int f[n]; f[0]=0;
        if ( n > 0 ){
        f[1] = 1;
        for (int i = 2; i<=n; i++) {
        f[i] = f[i-1] + f[i-2];
        }
        return f[n];
        }
    }

void *mythread(void *arg) {
    int *args = (int *) arg;
    printf("args %d\n", args);
    int *fib = malloc(sizeof(int) * (*args + 1));
    assert(fib != NULL);
    fib[0]=0;
    if ( *args > 0 ){
        fib[1] = 1;
        for (int i = 2; i<=*args; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        };
    }
    return (void *) fib;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: <nth fibbonacci>\n");
        return -1;
    }
    int n = atoi(argv[1]);
    int *fib = malloc(sizeof(int) * (n + 1));
    pthread_t p;
    Pthread_create(&p, NULL, mythread, &n);
    Pthread_join(p, (void **) &fib);
    printf("Fibbonacci N: %d\n", fib[n]);
    free(fib);
    return 0;
}

