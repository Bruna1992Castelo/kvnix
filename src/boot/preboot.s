entry start

# Bootloader - Starting at 0x7C00
# The goal is to load the real bootloader at 0xA500
# So, the 0x7C00 sector is release to kernel code
start:

	mov	ax, #0xb800
	mov	es, ax
	seg	es
	mov	[0], #0x42
	seg	es
	mov	[1], #0x1f

	mov	ax, #0
	mov	ds, ax
	mov ss, ax
    mov es, ax

	mov		ch, #0		;cilindro
	mov		dh, #0		;face
	mov		dl, #0x80	;disco

	mov		bx, #0xA500	;es:0xA500
	mov		cl, #2		;inicio setor 2

	mov		ah, #2		;funcao 2
	mov		al, #1		;qtde setores
	int		#0x13

	;start executing real bootloader
	mov	ax, #0xA500
	jmp	ax

loop1: jmp loop1

.org 510
	.byte	0x55
	.byte	0xaa	

