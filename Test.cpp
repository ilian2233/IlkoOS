#include <stdio.h>
#include <ucontext.h>
#include "IlkoOS.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

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

using namespace IlkoOS;

int main()
{
    //Add functons;
    IlkoOS::create_task(f1);
    IlkoOS::create_task(f2);
    IlkoOS::create_task(f3);
    IlkoOS::create_task(f4);

    IlkoOS::initlibrary();

    return 0;
}