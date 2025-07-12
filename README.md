
i686-elf-gcc -m32 -ffreestanding -O2 -Wall -Wextra -c kernel/kernel.c -o kernel.o

i686-elf-ld -T linker.ld -o kernel.elf  kernel.o --oformat elf32-i386    

copy kernel.elf iso/boot/

wsl -d Ubuntu grub-mkrescue -o OS.iso iso

qemu-system-i386 -cdrom OS.iso