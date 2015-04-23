#ifndef _IPC_H
#define _IPC_H

/**
 * Holds syscalls information to be treat by the kernel.
 */
typedef struct message {
	int m_type;
	int m1_i1;
	int m1_i2;
	int m1_i3; 
	char *m1_p1;
	char *m1_p2;
	char *m1_p3;
 } message;

#endif

