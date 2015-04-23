#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <minilib/stdlib.h>
#include <minilib/stdio.h>

__asm__(".code16gcc\n");

PUBLIC int do_waitpid(int pid)
{
    task_t *task = get_task_by_pid(pid);

    if (task != NULL) {
        return task_join(task);
    }

    return -1;
}
