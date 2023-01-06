nasm -f elf32 boot.asm -o boot.o
nasm -fbin fda.asm -o fda.bin
i686-elf-gcc -I./misc -fno-stack-protector -m32 -c kernel.c -o kernel.o

i686-elf-ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o

qemu-system-i386 -hda fda.bin -m 5M -kernel kernel