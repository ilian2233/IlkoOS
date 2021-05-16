#include <stdio.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include "IlkoOS.h"

void f1()
{
	while (true)
	{
		puts("-");
	};
}

void f2()
{
	while (true)
	{
		puts("+");
	};
}

void f3()
{
	while (true)
	{
		puts("/");
	}
}

void f4()
{
	while (true)
	{
		puts("*");
	}
}

//using namespace IlkoOS;

int main()
{
	//Add functons;
	create_task(f1);
	create_task(f2);
	create_task(f3);
	create_task(f4);

	initlibrary();

	return 0;
}