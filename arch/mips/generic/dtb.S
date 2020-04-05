.section .data
.align 2
.global __appended_dtb, __appended_dtb_end
__appended_dtb:
.incbin "arch/mips/generic/dts/qemu.dtb"
__appended_dtb_end:
