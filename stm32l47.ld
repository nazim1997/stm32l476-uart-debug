MEMORY
{
  FLASH(rx):ORIGIN =0x08000000,LENGTH =1024K
  SRAM(rwx):ORIGIN =0x20000000,LENGTH =96K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS {
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector*))
  } >FLASH

  .rom :
  {
    . = ALIGN(4);
    *(.text*)          /* .text* sections (code) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
  } >FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)          /* .data* sections (initialized variables) */
    _edata = .;
  } >SRAM AT>FLASH

  _sidata = LOADADDR(.data);

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)          /* .bss* sections (uninitialized variables) */
    _ebss = .;
  } >SRAM
}
