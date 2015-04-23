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
__asm__(".code16gcc\n");

#include <drivers/disk.h>
#include <sys/types.h>
#include <archs/arch.h>
#include <minilib/string.h>
#include <minilib/stdio.h>

void read_disk_data(void * memory, unsigned long long offset, unsigned short nrsectors) {
	int i;
	void * mem = memory;
	unsigned long long lba = offset;

	lba /= 512;

	for (i=0; i < nrsectors; i++) {
		read_disk_sector(mem, lba++);

		mem+=512;
	}
}

void read_disk_sector(void * memory, unsigned long long lba) {

	lba_command_packet packet;

	memset(&packet, 0, 0x10);

	packet.packet_len = 0x10;
	packet.nsects = 1;
	packet.buffer = (unsigned int)memory;
	packet.lba = lba;

	unsigned short pos = (unsigned short)&packet;

	__asm__(
			"movb	$0x42, %%ah	\n" \
			"movb	$0x80, %%dl	\n" \
			"movw	%0, %%si	\n" \
			"int $0x13			\n"
			:
			: "m" ((unsigned short)pos)
			);						
}

