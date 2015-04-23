entry start

# This boot loader start executing at 0xA500
# Due this, there is more space to load kernel.
start:

	mov	ax, #0xb800
	mov	es, ax
	seg	es
	mov	[0], #0x42
	seg	es
	mov	[1], #0x2e

	mov		ax, #0
	mov		ds, ax
	mov 	ss, ax
    mov 	es, ax
    mov 	sp, #0xFFFF

	mov		ch, #0		;cylinder
	mov		dh, #0		;face
	mov		dl, #0x80	;disk

	mov		bx, #0x500	;es:0x500
	mov		cl, #3		;start disk sector: 3

load:
	mov		ah, #2		;func 2
	mov		al, #1		;amount of sectors
	int		#0x13

	add		bx, #0x200	;512 bytes
	add		cl, #1
	
	cmp		bx, #0x7D00	;Final position at memory (0x500 + (60 x 512))
	jl		load

	;start executing program loaded from disk
	mov		ax, #0x500
	jmp		ax

loop1: jmp loop1

