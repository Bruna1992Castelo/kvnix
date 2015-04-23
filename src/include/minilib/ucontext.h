/* Copyright (C) 2009 Klystofer Ortega, Victor Villela Serta
   This file is part of Kvnix.

   Kvnix is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as 
   published by the Free Software Foundation, either version 3 of 
   the License, or (at your option) any later version.

   Kvnix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public 
   License along with Kvnix. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef _UCONTEXT_H
#define _UCONTEXT_H

#include <sys/types.h>
#include <minilib/signal.h>

/**
 * @file ucontext.h
 *
 * User Context.
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/basedefs/ucontext.h.html#tag_13_78">this link</a>.
 * 
 * @author Victor V. Serta
 */

typedef u16_t reg_t;

/**
 * Machine context.
 */
typedef struct mcontext_t {
    reg_t mc_cs;
    reg_t mc_ip;

    reg_t mc_ds;
    reg_t mc_es;
    reg_t mc_ss;

    reg_t mc_si;
    reg_t mc_di;

    reg_t mc_flags;

    reg_t mc_ax;        /**< Register AX */
    reg_t mc_bx;        /**< Register BX */ 
    reg_t mc_cx;        /**< Register CX */ 
    reg_t mc_dx;        /**< Register DX */ 

} mcontext_t;

/**
 * User Context.
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/basedefs/ucontext.h.html#tag_13_78">this link</a>.
 */
typedef struct ucontext_t {
    struct ucontext_t *uc_link;    /**< Pointer to the context that is resumed when this context returns.*/
     
    //TODO Implement signals
    //sigset_t us_sigmask;  The set of signals that are blocked when this context is active. */

    stack_t uc_stack;       /**< The stack used by this context. */
    mcontext_t uc_mcontext; /**< A machine-specific representation of the saved context.*/
} ucontext_t;

/**
 * Gets the current user context.
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/functions/setcontext.html"> this link</a>.
 *
 * @param ucp user context pointer
 * @return 0 on success or -1 on error
 */
extern int getcontext(ucontext_t *ucp);
 
/**
 * Modifies a user context initialized using getcontext().
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/functions/swapcontext.html"> this link</a>.
 *
 * @param ucp user context pointer
 * @param func function called to continue the program execution
 * @param argc number of parameters to func
 */ 
extern void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...);

/**
 * Sets the current user context.
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/functions/setcontext.html"> this link</a>.
 *
 * @param ucp user context pointer
 * @return -1 on error
 */
extern int setcontext(const ucontext_t *ucp);

/**
 * Modifies a user context initialized using getcontext().
 * See <a href="http://www.opengroup.org/onlinepubs/009695399/functions/swapcontext.html"> this link</a>.
 *
 * @param oucp current user context pointer
 * @param upc user context pointer to be resumed
 * @return 0 on success or -1 on error
 */
extern int swapcontext(ucontext_t * restrict oucp, const ucontext_t * restrict ucp);

#endif
