#include <ucontext.h>
#include <string>
#include <math.h>

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

        static Process processes = Process(NULL);

        void push(ucontext_t *data)
        {
            struct Process *new_node = (struct Process *)malloc(sizeof(struct Process));

            new_node->data = data;

            new_node->next = &processes;
            new_node->prev = NULL;

            if (&processes != NULL)
                processes.prev = new_node;

            processes = *new_node;
        }
    }

    void *
    initlibrary()
    {
        int start = clock();
        double diff;
        Process proc1 = processes, proc2 = *processes.prev;
        do
        {
            swapcontext(proc1.data, proc2.data);
            diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

        } while (diff < 60.0);
    };

    int create_task(void *(*start_routine))
    {
        char st1[8192];

        static ucontext_t context;
        getcontext(&context);
        context.uc_stack.ss_sp = st1;
        context.uc_stack.ss_size = sizeof st1;

        Process proc = Process(&context, &processes, NULL);

        push(&context);

        return 0;
    };
}