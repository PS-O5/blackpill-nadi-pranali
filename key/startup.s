.syntax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler

.section .isr_vector,"a",%progbits
.word _estack
.word Reset_Handler

.text
.thumb_func
Reset_Handler:
    bl main
loop:
    b loop
