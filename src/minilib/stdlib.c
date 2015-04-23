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

#include <minilib/stdlib.h>

#include <kvnix/const.h>
#include <minilib/string.h>

__asm__(".code16gcc\n");

PUBLIC char * itoa(int value, char *string, int radix) 
{	
	int  i, sign, j;
	char c; 

	if ((sign = value) < 0)
		value = -value;

	i = 0;

	do {
		
		string[i++] = value % radix + '0';

	} while ((value /= radix) > 0);

	if (sign < 0)
		string[i++] = '-';

	string[i] = '\0';

	//reverse
	for (--i, j = 0; i > j; i--, j++)
	{
		c = string[j];
		string[j] = string[i];
		string[i] = c;
	}
	
	return string;
}
