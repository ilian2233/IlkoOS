#include <ucontext.h>
#include <string>

namespace IlkoOS
{
    namespace
    {
        struct Process
        {
            ucontext_t *data;
            struct Process *next;
            struct Process *prev;

            void push(struct Process **head_ref, ucontext_t *data)
            {
                struct Process *new_node = (struct Process *)malloc(sizeof(struct Process));

                new_node->data = data;

                new_node->next = (*head_ref);
                new_node->prev = NULL;

                if ((*head_ref) != NULL)
                    (*head_ref)->prev = new_node;

                (*head_ref) = new_node;
            }
        };

        static Process processes;
    }

    void *
    initlibrary(){
        // int start = clock();
        // double diff;
        // do
        // {
        //     // do stuff
        //     diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

        // } while (diff < 60.0);
    };

    int create_task(void *(*start_routine))
    {
        const ucontext_t context;
        context.
        const Process proc = new Process()
            makecontext('a', &start_routine, 0);
        if (processes.data == NULL)
        {
            processes.data = start_routine;
        }
    };
}