#include <kvnix/clock.h>
#include <kvnix/pm/sched.h>
#include <kvnix/pm/const.h>
#include <minilib/stdio.h>

__asm__(".code16gcc\n");

clock_tick_t clock_ticks;
clock_tick_t sched_start_clock_tick;
bool preemption_enabled;


extern void _init_timer();

PUBLIC void system_clock_init()
{
    _init_timer();

    clock_ticks = 0;
    preemption_enabled = false;
}

PUBLIC void handle_clock_tick() 
{
    clock_ticks++;

    clock_tick_t sched_clock_ticks = clock_ticks - sched_start_clock_tick;

    if (preemption_enabled && (sched_clock_ticks >= SCHED_CLOCK_TICKS)) {
        sched_handle_timer();
    }
}

PUBLIC long time_now()
{
    return (long) clock_ticks;
}

PUBLIC void enable_preemption(bool enabled)
{       
    if (enabled == preemption_enabled) {
        return;
    }
    
    sched_start_clock_tick = clock_ticks;
    preemption_enabled = enabled;
}

