ENTRY(_start)

PHDRS
{
  boot_text PT_LOAD;
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
	. = 2M;
    kernel_physical_start_ = .;

    .boot_text ALIGN(4K) : AT(ADDR(.boot_text)) {
        KEEP(*(.multiboot))
    } :boot_text

    .text ALIGN(4K) : AT(ADDR(.text)) {
        *(.text*)
    } :text

    .rodata ALIGN(4K) : AT(ADDR(.rodata)) {
        *(.rodata*)
    } :data

    .data ALIGN(4K) : AT(ADDR(.data)) {
        *(.data*)
    } :data

    .bss ALIGN(4K) (NOLOAD) : AT(ADDR(.bss)) {
        *(COMMON)
        *(.bss)
        *(.stack)
        *(.page_tables)
    } :bss

    kernel_physical_end_ = .;
}