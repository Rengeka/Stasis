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
i686-elf-gcc -m32 -ffreestanding -c src/kernel/kernel.c -o build\kernel.o

REM cpu
i686-elf-gcc -m32 -ffreestanding -c src/kernel/cpu/x86/x86.c -o build\cpu.o
i686-elf-gcc -m32 -ffreestanding -c src/kernel/cpu/x86/x86_io.c -o build\stdio.o

REM libs
i686-elf-gcc -m32 -ffreestanding -c src/kernel/stdlib/stdbool.c -o build\stdbool.o
i686-elf-gcc -m32 -ffreestanding -c src/kernel/stdlib/stdstring.c -o build\stdstring.o
i686-elf-gcc -m32 -ffreestanding -c src/kernel/stdlib/stdmem.c -o build\stdmem.o

REM threads
i686-elf-gcc -m32 -ffreestanding -c src/kernel/thread/process.c -o build\process.o

REM shell
i686-elf-gcc -m32 -ffreestanding -c src/kernel/shell/shell.c -o build\shell.o

REM drivers
i686-elf-gcc -m32 -ffreestanding -c src/kernel/drivers/vga.c -o build\vga.o
i686-elf-gcc -m32 -ffreestanding -c src/kernel/drivers/ataio.c -o build\ataio.o

REM linking kernel
echo Linking kernel...
i686-elf-ld -T linker.ld -o build\kernel.elf build\stdmem.o ^
    build\kernel.o build\stdbool.o build\stdstring.o build\stdio.o ^
    build\shell.o build\process.o build\vga.o build\cpu.o^
    --oformat elf32-i386

REM creating virtual disk (only if doesn't exist)
if not exist disk.img (
    echo Creating virtual disk...
    qemu-img create -f raw disk.img 64M
)

REM running QEMU
echo Running in QEMU...
qemu-system-i386 -kernel build\kernel.elf -hda disk.img -m 512M -smp 2