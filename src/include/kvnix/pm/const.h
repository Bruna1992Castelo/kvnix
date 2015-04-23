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

/**
 * @file
 *
 * Process manager constants.
 *
 * @author Victor V. Serta
 */ 

#ifndef _PM_CONST_H
#define _PM_CONST_H

/**
 * Process manager name.
 */
#define PM_NAME "Process Manager"

/** 
 * Processes memory area size. 
 */ 
#define PROC_MEMORY_AREA_SIZE 60000

/** 
 * Process memory area begin position. 
 */  
#define PROC_MEMORY_AREA_BEGIN 0x10001

/** 
 * Process code size. 
 */ 
#define PROC_CODE_SIZE 10240

/** 
 * Process code begin position. 
 */  
#define PROC_CODE_BEGIN 0x10   

/** 
 * Process stack size. 
 */   
#define PROC_STACK_SIZE 2048

/**
 * Process code begin position. 
 */ 
#define PROC_STACK_BEGIN 0xFFFF - PROC_STACK_SIZE  

/** 
 * Process heap begin position. 
 */   
#define PROC_HEAP_BEGIN (PROC_CODE_BEGIN + PROC_CODE_SIZE + 1)

/**
 * Process heap size. 
 */ 
#define PROC_HEAP_SIZE (PROC_STACK_BEGIN - PROC_HEAP_BEGIN - 1)

/**
 * Ticks to call scheduler.
 */
#define SCHED_CLOCK_TICKS 10

#endif
