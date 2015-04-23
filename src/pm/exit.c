#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>

__asm__(".code16gcc\n");

PUBLIC void do_exit(int exit_value)
{
    task_exit(exit_value);
}
