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
 * This file constains some useful constants to mantain the source code
 * more eligible.
 */

#ifndef _CODE_CONST_H
#define _CODE_CONST_H


/* -------------------
 * Scope of functions.
 * -------------------
 */

/**
 * The "extern" declaration indicates a variable/function is global.
 */
#define EXTERN extern        

/**
 * This constant is used to indicate a public function. 
 * The value is blank because in C language the functions are public by default. 
 */
#define PUBLIC

/**
 * This constant is used to indicate a private function. 
 * In C language, the modifier "static" defines that the function is private.
 */
#define PRIVATE static


#endif
