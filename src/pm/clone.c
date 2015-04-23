#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <kvnix/mm/alloc.h>

__asm__(".code16gcc\n");

PUBLIC int do_clone(int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg)
{           
    //new thread creation
    task_t *new_task = task_create(current_proc, func, child_stack, child_stack_size, arg);

    //adding the new thread to the scheduler
    task_add(new_task);

    return new_task->tid;
}
