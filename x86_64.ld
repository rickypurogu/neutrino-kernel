OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(_kstart)

PHDRS
{
    null    PT_NULL    FLAGS(0) ;                   /* Null segment */
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ; /* Execute + Read */
    rodata  PT_LOAD    FLAGS((1 << 2)) ;            /* Read only */
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; /* Write + Read */
    dynamic PT_DYNAMIC FLAGS((1 << 1) | (1 << 2)) ; /* Dynamic segment needed for PIE */
}

SECTIONS
{
    . = 0xffffffff80000000 + 2M;
    __start = .;

    .text : {
        *(.text*)
    } :text

    . += 0x1000;

    .stivale2hdr : {
        KEEP(*(.stivale2hdr))
    } :rodata

    .rodata : {
        *(.rodata*)
    } :rodata

    . += 0x1000;

   .data : {
        *(.data*)
   } :data

   .dynamic : {
       *(.dynamic)
   } :data :dynamic

   .bss : {
       *(COMMON)
       *(.bss*)
   } :data

   __end = .;

   /DISCARD/ :
   {
        *(.comment)
   }
}