#include <stdio.h>
#include <ucontext.h>
#include "IlkoOS.h"

void f1(void)
{
    puts("-");
}

void f2(void)
{
    puts("-");
}

using namespace IlkoOS;

int main()
{
    void *foo = reinterpret_cast<void *>(f1);
    IlkoOS::create_task(&foo);
    foo = reinterpret_cast<void *>(f2);
    IlkoOS::create_task(&foo);
    IlkoOS::initlibrary();
}

// static ucontext_t ctx[3];

// int main(void)
// {
//     char st1[8192];
//     char st2[8192];

//     getcontext(&ctx[1]);
//     ctx[1].uc_stack.ss_sp = st1;
//     ctx[1].uc_stack.ss_size = sizeof st1;
//     ctx[1].uc_link = &ctx[0];
//     makecontext(&ctx[1], f1, 0);

//     getcontext(&ctx[2]);
//     ctx[2].uc_stack.ss_sp = st2;
//     ctx[2].uc_stack.ss_size = sizeof st2;
//     ctx[2].uc_link = &ctx[1];
//     makecontext(&ctx[2], f2, 0);

//     swapcontext(&ctx[0], &ctx[2]);
//     return 0;
// }