/* Format of this linker script was slightly copied from suzumebachi
 *  http://cgit.jvnv.net/suzumebachi/tree/suzumebachi.ld?id=2fc77d2
 *  Used with explicit permission */
MEMORY {
  flash (rx)  : org = 0x08000000, len = 256k
  ram   (rwx) : org = 0x20000000, len = 64k
}

_ram_start = ORIGIN(ram);
_ram_size = LENGTH(ram);
_ram_end = _ram_start + _ram_size;

SECTIONS {
  . = 0;
  
  /* ISR vectors must come first. */
  .vectors : {
    *(.vectors)
  } > flash
  
  .text : {
    *(.text)
  } > flash

  .data : {
    *(.data)
  } > ram AT > flash

  .bss : {
    *(.bss)
    *(COMMON)
  } > ram
}
