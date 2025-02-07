ENTRY(_start)

SECTIONS
{
  . = 2M;

  .boot : {
    KEEP(*(.multiboot))
  }

  .text : {
    *(.text)
  }
}