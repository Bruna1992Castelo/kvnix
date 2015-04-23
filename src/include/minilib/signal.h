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

#ifndef _SIGNAL_H
#define _SIGNAL_H

/**
 * @file signal.h 
 *
 * Signals.
 * See <a href="http://www.opengroup.org/onlinepubs/007908775/xsh/signal.h.html">this link</a>.
 * 
 * @author Victor V. Serta
 */


/**
 * Stack informations.
 */
typedef struct stack_t {
    void *ss_sp;    /**< Stack pointer */
    void *ss_bp;    /**< Base pointer */
    int ss_size;    /**< Stack size */
    int ss_flags;   /**< Stack flags */
} stack_t;


#endif
