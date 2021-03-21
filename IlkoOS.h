#include <ucontext.h>
#include <string>
#include <math.h>

#define FIBER_STACK 1024 * 64

namespace IlkoOS
{
    namespace
    {
        struct Process
        {
            ucontext_t *data;
            struct Process *next;
            struct Process *prev;

            Process(ucontext_t *data)
            {
                this->data = data;
                this->next = NULL;
                this->prev = NULL;
            };

            Process(ucontext_t *data, Process *next, Process *prev)
            {
                this->data = data;
                this->next = next;
                this->prev = prev;
            };
        };

        Process *processes = NULL;

        void push(void func())
        {
            static ucontext_t context;

            if (processes != NULL)
            {
                //Sets the data of the new process;
                getcontext(&context);
                context.uc_link = processes->data;
                context.uc_stack.ss_sp = malloc(FIBER_STACK);
                context.uc_stack.ss_size = FIBER_STACK;
                context.uc_stack.ss_flags = 0;
                // void *func1 = reinterpret_cast<void *>(func);
                makecontext(&context, func, 0);

                //Creates new Proccess;
                Process *new_node = new Process(&context, NULL, processes);

                //Creates new head;
                processes = new_node;
            }
            else
            {
                // getcontext(&asd);
                getcontext(&context);
                // context.uc_link = &asd;
                context.uc_stack.ss_sp = malloc(FIBER_STACK);
                context.uc_stack.ss_size = FIBER_STACK;
                context.uc_stack.ss_flags = 0;
                // void *func1 = reinterpret_cast<void *>(func);
                makecontext(&context, func, 0);

                processes = new Process(&context, NULL, NULL);
            }
        }
    }

    void initlibrary()
    {
        // int start = clock();
        // double diff;
        // Process proc1 = processes;
        // Process proc2 = *processes.prev;
        // setcontext(processes->prev->data);
        setcontext(processes->data);

        puts("asd");
        // setcontext(processes.prev->data);
        // swapcontext(proc1.data, proc2.data);
        // do
        // {
        //     diff = 0;
        //     do
        //     {
        //         swapcontext(proc1.data, proc2.data);
        //         diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

        //     } while (diff < 60.0);
        // } while (true);
    };

    int create_task(void func())
    {
        push(func);

        return 0;
    };
}