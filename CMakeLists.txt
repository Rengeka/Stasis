cmake_minimum_required(VERSION 3.15)
project(StasisOS C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_COMPILER i686-elf-gcc)

set(CMAKE_C_FLAGS "-m32 -ffreestanding -Wall -Wextra -nostdlib -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib -Wl,--build-id=none -m elf_i386")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(SOURCES
    src/kernel/kernel.c

    src/kernel/cpu/x86/x86.c
    src/kernel/cpu/x86/x86_io.c

    src/kernel/stdlib/stdbool.c
    src/kernel/stdlib/stdstring.c
    src/kernel/stdlib/stdmem.c

    src/kernel/thread/process.c

    src/kernel/shell/shell.c

    src/kernel/drivers/vga.c
    src/kernel/drivers/ataio.c
)

add_executable(kernel.elf ${SOURCES})

set_target_properties(kernel.elf PROPERTIES
    LINKER_LANGUAGE C
    OUTPUT_NAME "kernel"
    SUFFIX ".elf"
)

add_custom_command(
    OUTPUT disk.img
    COMMAND qemu-img create -f raw disk.img 64M
    COMMENT "Creating virtual disk image..."
)

add_custom_target(create_disk ALL DEPENDS disk.img)

add_custom_target(run_qemu
    COMMAND qemu-system-i386 -kernel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.elf -hda disk.img -m 512M -smp 2
    DEPENDS kernel.elf create_disk
    COMMENT "Running kernel in QEMU..."
)