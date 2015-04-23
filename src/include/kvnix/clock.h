#ifndef _CLOCK_H
#define _CLOCK_H

#include <kvnix/const.h>
#include <minilib/stdbool.h>

typedef long clock_tick_t;

/**
 * Initialize clock mechanism.
 */
PUBLIC void system_clock_init();

/**
 * Handles clock interruptions.
 */
PUBLIC void handle_clock_tick();

/**
 * Get number of ticks since OS was started.
 */
PUBLIC long time_now();

/**
 * Preemption Control
 */
PUBLIC void enable_preemption(bool enabled);

#endif
