OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PHDRS
{
    boot_text PT_LOAD;
    text PT_LOAD;
    rodata PT_LOAD;
    data PT_LOAD;
    bss PT_LOAD;
}

SECTIONS
{
    . = 2M;
    kernel_physical_start_ = .;

    .boot_text : {
        KEEP(*(.multiboot))
    } :boot_text

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .text : {
        *(.text*)
    } :text

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .rodata : {
        *(.rodata*)
    } :rodata

    .init_array : {
        __init_array = .;
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP(*(.init_array .ctors))
        __init_array_end = .;
    } :rodata

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .data : {
        *(.data*)
    } :data

    .bss ALIGN(4K) (NOLOAD) : {
        *(COMMON)
        *(.bss)
        *(.stack)
        *(.page_tables)
    } :bss

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }

    kernel_physical_end_ = .;
}