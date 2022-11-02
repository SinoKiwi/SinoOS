CFLAGS = -mcmodel=large -fno-builtin -m64
ASFLAGS = --64
LDFLAGS = -b elf64-x86-64 -T ../Kernel.lds -o syslink
OBJCPFLGS = -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary

all: clean compile link

head.o: khead_desc.S
	gcc -E khead_desc.S > build/head.s
	as $(ASFLAGS) -o build/head.o build/head.s

main.o: main.c
	gcc $(CFLAGS) -c main.c -o build/main.o

graphic.o: subkernel/gui/graphic.c
	gcc $(CFLAGS) -c subkernel/gui/graphic.c -o build/graphic.o

lib.o: syslib/libstd/lib.c
	gcc $(CFLAGS) -c syslib/libstd/lib.c -o build/lib.o

compile: head.o main.o graphic.o lib.o

link: 
#ATTENTION: head.o must be the first at ld
	cd build/ && ld $(LDFLAGS) head.o main.o graphic.o lib.o
	cd build/ && objcopy $(OBJCPFLGS) syslink ../kernel.bin

clean: 
	rm -rf build/*,build/*.*,kernel.bin
