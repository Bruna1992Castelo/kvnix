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
 * Global constants used by interruption system.
 */

#ifndef _CALLNR_H
#define _CALLNR_H

#define SYS_EXIT		    	1
#define SYS_FORK		    	2
#define	SYS_READ		    	3
#define SYS_WRITE		    	4
#define SYS_OPEN		    	5
#define SYS_CLOSE		    	6
#define SYS_WAIT_PID        		7
#define SYS_MALLOC		    	8
#define SYS_FREE		    	9
#define	SYS_REALLOC		    	10
#define SYS_LOAD_PROGRAM		11
#define SYS_SCHED_YIELD	    		12
#define SYS_CLONE   	    		120

#endif

