#include <stdio.h>
#include <ucontext.h>
#include "IlkoOS.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

static ucontext_t a;

void f1()
{
    puts("-");
    setcontext(&a);
}

void f2()
{
    puts("+");
    setcontext(&a);
}

void f3()
{
    puts("/");
    setcontext(&a);
}

void f4()
{
    puts("*");
    setcontext(&a);
}

#define INTERVAL 1

void TimerStop(int signum)
{

    printf("Signal recieved!\nExecuting function:\n");

    //Shows next char;
    IlkoOS::initlibrary();
}

void TimerSet(int interval)
{
    printf("\n\n\n");
    printf("Creating new signal.\n\n");
    struct itimerval it_val;

    it_val.it_value.tv_sec = interval;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;

    if (signal(SIGALRM, TimerStop) == SIG_ERR)
    {
        perror("Unable to catch SIGALRM");
        exit(1);
    }
    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1)
    {
        perror("error calling setitimer()");
        exit(1);
    }
}

using namespace IlkoOS;

int main()
{
    //Add functons;
    IlkoOS::create_task(f1);
    IlkoOS::create_task(f2);
    IlkoOS::create_task(f3);
    IlkoOS::create_task(f4);

    //Main loop;
    while (1)
    {
        //Create main context;
        getcontext(&a);

        sleep(2);

        //Creates timer;
        TimerSet(INTERVAL);
    }
    return 0;
}