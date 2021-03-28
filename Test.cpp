#include <stdio.h>
#include <ucontext.h>
#include "IlkoOS.h"

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

using namespace IlkoOS;

int main()
{
    //Add functons;
    IlkoOS::create_task(f1);
    IlkoOS::create_task(f2);
    IlkoOS::create_task(f3);
    IlkoOS::create_task(f4);

    //Create main context;
    getcontext(&a);

    //Start main loop;
    IlkoOS::initlibrary();
}