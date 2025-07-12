:: Compile the kernel
i686-elf-gcc -m32 -ffreestanding -O2 -Wall -Wextra -c kernel/kernel.c -o kernel.o

:: Link the kernel
i686-elf-ld -T linker.ld -o kernel.elf kernel.o --oformat elf32-i386

:: Copy kernel to ISO boot folder
copy kernel.elf iso\boot\

:: Generate ISO using WSL and GRUB
wsl -d Ubuntu grub-mkrescue -o OS.iso iso

:: Launch the OS in QEMU
qemu-system-i386 -cdrom OS.iso
