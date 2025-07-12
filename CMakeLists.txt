cmake_minimum_required(VERSION 3.10)
project(OS C)

set(CMAKE_EXECUTABLE_SUFFIX "")

set(CMAKE_C_COMPILER i686-elf-gcc)

set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra -nostdlib")

set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} <OBJECTS> -o <TARGET> -T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib -lgcc")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

add_executable(kernel/kernel.c)

set_target_properties(iso/boot/kernel.elf PROPERTIES
        LINK_FLAGS ""
        LINK_DEPENDS "${CMAKE_SOURCE_DIR}/linker.ld"
)