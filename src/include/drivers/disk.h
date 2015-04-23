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
 * Support functions to handle disk.
 *
 * These funtions are used mainly to load programs (data) from disk to memory.
 */

#ifndef _DISK_H
#define _DISK_H

/**
 * LBA Address Packet
 */
typedef struct 
{
	unsigned char packet_len;
	unsigned char reserved1;
	unsigned short nsects;
	unsigned int buffer;
	unsigned long long lba;
} lba_command_packet;

/**
 * Read a disk region for a given position.
 *
 * @param memory position to write.
 * @param offset indicates the beginning on disk (must be a beginning of a sector)
 * @param nrsectors number of sectors to read
 */
void read_disk_data(void * memory, unsigned long long offset, unsigned short nrsectors);

/**
 * Reads a sector from disk to memory.
 *
 * @param memory position to write.
 * @param lba linear base address.
 */
void read_disk_sector(void * memory, unsigned long long lba);

#endif

