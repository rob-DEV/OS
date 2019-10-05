CXX = ~/opt/cross/bin/i686-elf-g++
CXX_GLOBAL_INCLUDES = -I NONE
CXX_FLAGS = -c -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions  $(CXX_GLOBAL_INCLUDES)
ASM = ~/opt/cross/bin/i686-elf-as
ASM_FLAGS = -c
LN_FLAGS = -T linker.ld -melf_i386


C_FILE = $(wildcard ../src/kernel/*.c)
C_SRC = $(C_FILE:.c=)


CXX_FILE = $(wildcard ../src/kernel/*.cpp) \
			$(wildcard ../src/kernel/com/*.cpp) \
			$(wildcard ../src/kernel/cpu/*.cpp) \
			$(wildcard ../src/kernel/gui/*.cpp) \
			$(wildcard ../src/kernel/hw/*.cpp) \
			$(wildcard ../src/kernel/io/*.cpp) \
			$(wildcard ../src/kernel/mem/*.cpp) \
			$(wildcard ../src/kernel/shell/*.cpp) \
			$(wildcard ../src/kernel/utl/*.cpp) \
			$(wildcard ../src/libc/*.cpp) 

CXX_SRC = $(CXX_FILE:.c=)


ASM_FILE = $(wildcard ../src/boot/*.s)
ASM_SOURCE = $(ASM_FILE:.s=)


OUT = $(wildcard ./out/obj/*.o)

all: cxxcompile acompile

cxxcompile:
	for file in $(CXX_SRC) ; do \
		$(CXX) $(CXX_FLAGS) $$file -o out/obj/$$(basename $$file).o ; \
	done

acompile:
	for file in $(ASM_SOURCE) ; do \
	    $(ASM) $(ASM_FLAGS) $$file.s -o out/obj/$$(basename $$file).o  ; \
	done
link:
		ld $(LN_FLAGS) -o out/bin/os.bin $(OUT)

run:
	qemu-system-i386 -kernel  out/bin/os.bin -m 768M  -soundhw pcspk

clean:
	rm -f $(OUT)
	rm -f out/bin/os.bin

buildiso:
	mkdir -p isodir/boot/grub
	cp latest.bin isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	sudo grub-mkrescue -o bootable.iso isodir

