OUTPUT_FORMAT(elf32-i386)
ENTRY(kernel_main)
SECTIONS {
    . = 1M;

    .multiboot ALIGN(4) : {
        *(.multiboot)
    }

    .text ALIGN(4K) : {
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
        *(COMMON)
    }
}