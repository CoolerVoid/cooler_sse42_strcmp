ARCH := $(shell getconf LONG_BIT)

CC=/usr/bin/gcc
OBJ_32 := strcmp_sse42_32.o
OBJ_64 := strcmp_sse42_64.o
OBJ := $(OBJ_$(ARCH)) 
CFLAGS=-Wall -g -Ofast -msse4.2 -Wl,-z,relro,-z,now -fstack-protector-all -D_FORTIFY_SOURCE=1

make: test.c
	/usr/bin/nasm -f elf32  strcmp_sse42_32.s -o  $(OBJ_32)
	/usr/bin/nasm -f elf64  strcmp_sse42_64.s -o  $(OBJ_64)
	$(CC) -o test test.c $(OBJ) $(CFLAGS)

clean:
	rm -f *.o test
 
