# Kvnix Makefile
#
#


# Package arguments
PKG=tar
PKG_FLAGS=-zcvf -X .*
PKG_PATH=../../pkg/    i

DIST_PATH=dist
OBJ_PATH=obj
BOOT_PATH=src/boot

# Documentation arguments
DOC_GEN=doxygen
DOC_CFG=Doxyfile
DOC_CFG_PATH=doc/
DOC_OUT_PATH=../doc/
DOC_PKG=doc.tar.gz

CFLAGS=-c -I src/include -DX86 -DDEBUG  -std=c99 -fno-stack-protector

documentation:	
	@echo "Generating documentation..."
	$(DOC_GEN) $(DOC_CFG_PATH)$(DOC_CFG)

package: documentation
	@echo "Generating documentation package..."
	$(PKG) $(PKG_FLAGS) $(PKG_PATH)$(DOC_PKG) $(DOC_OUT_PATH)

clear: clear_dist clear_doc clear_obj

clear_doc:
	@echo "Cleaning..."
	rm -R $(DOC_OUT_PATH)* $(PKG_PATH)*  

clear_obj:
	rm *.o

clear_dist:
	rm -R dist/*
    
compile:
	as src/archs/i386/setcontext.s -o setcontext.o
	as src/archs/i386/getcontext.s -o getcontext.o
	as src/archs/i386/makecontext.s -o makecontext.o
	as src/archs/i386/swapcontext.s -o swapcontext.o
	as src/kernel/entry.s -o entry.o
	gcc $(CFLAGS) 	src/kernel/start.c \
					src/kernel/panic.c \
					src/kernel/ints.c \
					src/kernel/syscalls.c \
					src/kernel/io.c \
					src/kernel/clock.c \
					src/kernel/shutdown.c \
					src/drivers/disk.c \
					src/drivers/tty/tty.c \
					src/mm/mm.c \
					src/mm/alloc.c \
					src/pm/load_program.c \
					src/pm/sched.c \
					src/pm/clone.c \
					src/pm/exit.c \
					src/pm/waitpid.c \
					src/ipc/semaphore.c \
					src/ipc/mqueue.c \
					src/minilib/stdio.c \
					src/minilib/stdlib.c \
					src/minilib/string.c \
					src/minilib/malloc.c \
					src/util/list.c \
					src/commands/shell/shell.c \
					src/commands/shell/progs.c \
					src/commands/shell/clear.c \
					src/commands/util/memdump.c \
					src/test/test_ucontext.c \
					src/test/test_sem.c \
					src/test/test_queue.c
	ld -static -Ttext 0x500 --oformat binary \
						start.o \
						panic.o \
						entry.o \
						ints.o \
						syscalls.o \
						io.o \
						clock.o \
						shutdown.o \
						tty.o \
						disk.o \
						mm.o \
						alloc.o \
						load_program.o \
						sched.o \
					    clone.o \
                        exit.o \
                        waitpid.o \
						semaphore.o \
						mqueue.o \
						stdio.o \
						stdlib.o \
						string.o \
						malloc.o \
						setcontext.o \
						getcontext.o \
						makecontext.o \
						swapcontext.o \
						shell.o \
						progs.o \
						clear.o \
						test_ucontext.o \
						test_sem.o \
						test_queue.o \
						memdump.o \
						list.o \
						-o $(DIST_PATH)/kvnix.bin

test_hello:
	gcc $(CFLAGS) 	src/test/test_hello.c
	ld -static -Ttext 0x0010 --oformat binary \
						test_hello.o \
						syscalls.o \
						string.o \
						malloc.o \
						-o $(DIST_PATH)/test_hello.bin

test_output:
	gcc $(CFLAGS) 	src/test/test_output.c
	ld -static -Ttext 0x0010 --oformat binary \
						test_output.o \
						syscalls.o \
						stdio.o \
						stdlib.o \
						malloc.o \
						string.o \
						-o $(DIST_PATH)/test_output.bin

test_input:
	gcc $(CFLAGS) 	src/test/test_input.c
	ld -static -Ttext 0x0010 --oformat binary \
						test_input.o \
						syscalls.o \
						stdio.o \
						stdlib.o \
						malloc.o \
						string.o \
						-o $(DIST_PATH)/test_input.bin

test_malloc:
	gcc $(CFLAGS) 	src/test/test_malloc.c
	ld -static -Ttext 0x0010 --oformat binary \
						test_malloc.o \
						syscalls.o \
						stdio.o \
						stdlib.o \
						malloc.o \
						string.o \
						-o $(DIST_PATH)/test_malloc.bin

test_string:
	gcc $(CFLAGS) 	src/test/test_string.c
	ld -static -Ttext 0x0010 --oformat binary \
						test_string.o \
						syscalls.o \
						stdio.o \
						stdlib.o \
						malloc.o \
						string.o \
						-o $(DIST_PATH)/test_string.bin

compile_tests: test_hello test_output test_input test_malloc test_string

compile_merge:
	gcc	-I src/include $(BOOT_PATH)/merge.c src/commands/shell/progs.c -o $(DIST_PATH)/merge	

compile_boot:
	as86 src/boot/preboot.s -o $(OBJ_PATH)/preboot.o
	ld86 -d $(OBJ_PATH)/preboot.o -o $(DIST_PATH)/preboot.bin
	as86 src/boot/boot.s -o $(OBJ_PATH)/boot.o
	ld86 -d $(OBJ_PATH)/boot.o -o $(DIST_PATH)/boot.bin

merge:
	$(DIST_PATH)/merge
	chmod 775 $(DIST_PATH)/image.bin
	
image: compile compile_tests compile_merge compile_boot merge
	qemu -hda $(DIST_PATH)/image.bin -boot c -no-kqemu

iso: compile compile_tests compile_merge compile_boot merge
	mkisofs -no-emul-boot -r -b $(DIST_PATH)/image.bin -o $(DIST_PATH)/kvnix.iso .
	qemu -cdrom $(DIST_PATH)/kvnix.iso -boot d -no-kqemu

burn: compile compile_tests compile_merge compile_boot merge
	gcc	$(BOOT_PATH)/burn.c -o $(DIST_PATH)/burn

	$(DIST_PATH)/burn

	qemu -hdc /dev/sdb -boot c -no-kqemu

