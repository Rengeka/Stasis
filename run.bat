@echo off

REM create build directory if not exists
if not exist build (
    mkdir build
)

REM cleaning old object files in build
echo Cleaning old object files in build...
del /Q build\*.o 2>nul
del /Q build\kernel.elf 2>nul

REM compiling kernel
echo Compiling kernel...
i686-elf-gcc -m32 -ffreestanding -c kernel/kernel.c -o build\kernel.o
i686-elf-gcc -m32 -ffreestanding -c drivers/vga.c -o build\vga.o
i686-elf-gcc -m32 -ffreestanding -c drivers/std_IO.c -o build\std_IO.o
i686-elf-gcc -m32 -ffreestanding -c shell/shell.c -o build\shell.o
i686-elf-gcc -m32 -ffreestanding -c drivers/ATA_IO.c -o build\ATA_IO.o

i686-elf-gcc -m32 -ffreestanding -c lib/stdbool.c -o build\stdbool.o
i686-elf-gcc -m32 -ffreestanding -c lib/stdstring.c -o build\stdstring.o

REM kernel linking
echo Linking kernel...
i686-elf-ld -T linker.ld -o build\kernel.elf build\ATA_IO.o build\kernel.o build\vga.o build\std_IO.o build\shell.o build\stdbool.o build\stdstring.o --oformat elf32-i386

REM searching for grub.cfg
if exist iso\boot\grub\grub.cfg (
    echo grub.cfg found
) else (
    echo grub.cfg not found, copying...
)

REM creating iso
echo Creating ISO...
wsl -d Ubuntu grub-mkrescue -o OS.iso iso

REM running QEMU
echo Running in QEMU...
qemu-img create -f raw disk.img 64M
qemu-system-i386 -kernel build\kernel.elf -hda disk.img -m 512M

REM qemu-system-i386 -kernel build\kernel.elf

REM Alternative run via ISO:
REM qemu-system-i386 -cdrom OS.iso
