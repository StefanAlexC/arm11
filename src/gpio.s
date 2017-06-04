ldr r0,=0x20200004
ldr r2,[r0]
orr r3,r2,#0x100000
str r3,[r0]
mov r4,#25
loop:
ldr r1,=0x10000
ldr r2,=0x20200028
str r1,[r2]
ldr r0,=10
clear:
sub r0,r0,#1
cmp r0,#0
bne clear
ldr r1,=0x10000
ldr r2,=0x2020001C
str r1,[r2]
ldr r0,=10
set:
sub r0,r0,#1
cmp r0,#0
bne set
sub r4,r4,#1
cmp r4,#0
bne loop
