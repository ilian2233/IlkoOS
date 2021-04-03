#include <ucontext.h>
#include <string>
#include <math.h>
// #include <thread_structures.h>

#define FIBER_STACK 1024 * 64
typedef struct tcb_t Task;

namespace IlkoOS
{
    namespace
    {
        struct Task
        {
            ucontext_t context;
            void (*func)();
            Task *next;

            Task()
            {
                this->context = ucontext_t();
                this->func = NULL;
                this->next = NULL;
            }

            Task(void (*func)(), Task *next)
            {
                ucontext_t *context = new ucontext_t();
                //Sets the context of the new task;
                getcontext(context);
                context->uc_link = &next->context;
                context->uc_stack.ss_sp = malloc(FIBER_STACK);
                context->uc_stack.ss_size = FIBER_STACK;
                context->uc_stack.ss_flags = 0;
                makecontext(context, func, 0);

                this->context = *context;
                this->func = func;
                this->next = next;
            }

        } * running_task, *task_queue;

        void push(void (*start_routine)())
        {
            if (task_queue != NULL)
            {
                // //Sets the context of the new task;
                // getcontext(&context);
                // // context.uc_link = &task_queue.context;
                // context.uc_stack.ss_sp = malloc(FIBER_STACK);
                // context.uc_stack.ss_size = FIBER_STACK;
                // context.uc_stack.ss_flags = 0;
                // makecontext(&context, start_routine, 0);

                //Creates new Task and sets to head;
                task_queue = new Task(start_routine, task_queue);
            }
            else
            {
                // //Sets the context of the new task;
                // getcontext(&context);
                // context.uc_link = NULL;
                // context.uc_stack.ss_sp = malloc(FIBER_STACK);
                // context.uc_stack.ss_size = FIBER_STACK;
                // context.uc_stack.ss_flags = 0;
                // makecontext(&context, start_routine, 0);

                //Sets new task to head;
                task_queue = new Task(start_routine, NULL);
            }
        }
    }

    void initlibrary()
    {
        //Sets end to beggining creating a loop;
        task_queue->next->next->next->next = task_queue;

        // //Execute a function and change to next context;
        // while (true)
        // {
        task_queue = task_queue->next;
        running_task = task_queue;
        setcontext(&running_task->context);
        // };
    };

    int create_task(void (*start_routine)())
    {
        push(start_routine);

        return 0;
    };
}