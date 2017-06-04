ldr r1,=0x00004000
ldr r0,=0x20200004
ldr r2,[r0]
orr r3,r2,r1
str r3,[r0]
loop:
clear:
ldr r1,=0x00001000
ldr r2,=0x20200028
str r1,[r2]
mov r0,#0xFF
sub r0,r0,#1
cmp r0,#0
bne clear
set:
ldr r1,=0x00001000
ldr r2,=0x2020001C
str r1,[r2]
mov r0,#0xFF
sub r0,r0,#1
cmp r0,#0
bne set
b loop

