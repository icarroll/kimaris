#define _POSIX_SOURCE

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "kimaris.h"

int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

const char * func;
int line;

#define _() func=__func__; line=__LINE__;
#define ok(test) do { _(); if (!(test)) { fail(); return 1; } } while(0)
#define run(test) do { reset_state(); tests_run++; test(); } while(0)
void fail() { printf("test failure in %s() line %d\n", func, line); }

void sighandler(int signum) {
    fail();
    /* generate core dump */
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

int test_nothing() {
    return 0;
}

int all_tests() {
    _verify(test_nothing);
    return 0;
}

int main(int argc, char ** argv) {
    signal(SIGSEGV, sighandler);

    int result = all_tests();
    printf("Tests run: %d\n", tests_run);
    if (result == 0) printf("OK\n");

    return result != 0;
}
