#include <ucontext.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

#define FIBER_STACK 1024 * 64
#define INTERVAL 1
typedef struct tcb_t Task;
static ucontext_t a;

namespace IlkoOS
{
    namespace
    {
        struct Task
        {
            ucontext_t *context;
            void (*func)();
            Task *next;

            Task()
            {
                this->context = NULL;
                this->func = NULL;
                this->next = NULL;
            }

            Task(void (*func)(), Task *next)
            {
                ucontext_t *context = new ucontext_t();
                //Sets the context of the new task;
                if (getcontext(context) == -1)
                {
                    printf("Getcontext failed.\n");
                    exit(1);
                };
                context->uc_link = &a;
                context->uc_stack.ss_sp = malloc(FIBER_STACK);
                context->uc_stack.ss_size = FIBER_STACK;
                context->uc_stack.ss_flags = 0;
                makecontext(context, func, 0);

                this->context = context;
                this->func = func;
                this->next = next;
            }

        } * task_queue;

        void push(void (*func)())
        {
            task_queue = new Task(func, task_queue);
        }
    }

    void execute_task(int signum)
    {

        printf("Signal recieved!\nExecuting function:\n");

        if (swapcontext(&a, task_queue->context) == -1)
        {
            printf("Swapcontext failed.\n");
            exit(1);
        };

        if (task_queue->next == NULL || task_queue->next->context == NULL)
        {
            printf("No next function to execute.\n");
            exit(1);
        }

        task_queue = task_queue->next;
    };

    void initlibrary()
    {
        //Sets end to beggining creating a loop;
        task_queue->next->next->next->next = task_queue;

        // Task *last_task = task_queue;
        // while (last_task->next != NULL)
        // {
        //     last_task = last_task->next;
        // }
        // last_task->next = task_queue;

        printf("Creating new timer.\n\n");

        struct itimerval it_val;
        it_val.it_value.tv_sec = INTERVAL;
        it_val.it_value.tv_usec = 0;
        it_val.it_interval.tv_sec = INTERVAL;
        it_val.it_interval.tv_usec = 0;
        if (setitimer(ITIMER_REAL, &it_val, NULL) == -1)
        {
            printf("Setitimer failed.\n");
            exit(1);
        };

        struct sigaction action;
        action.sa_handler = execute_task;
        if (sigemptyset(&action.sa_mask) == -1)
        {
            printf("Sigemptyset failed.\n");
            exit(1);
        };
        action.sa_flags = 0;
        if (sigaction(SIGALRM, &action, NULL) == -1)
        {
            printf("Sigaction failed.\n");
            exit(1);
        };

        while (true)
            ;
    };

    int create_task(void (*func)())
    {
        push(func);

        return 0;
    };
}