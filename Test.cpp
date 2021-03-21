#include <stdio.h>
#include <ucontext.h>
#include "IlkoOS.h"

void f1()
{
    puts("-");
}

void f2()
{
    puts("+");
}

using namespace IlkoOS;

int main()
{
    // void *foo = reinterpret_cast<void *>(f1);
    IlkoOS::create_task(f1);
    // foo = reinterpret_cast<void *>(f2);
    IlkoOS::create_task(f2);
    IlkoOS::initlibrary();
}