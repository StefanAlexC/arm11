ldr r0,=0x20200004
ldr r2,[r0]
ldr r4,=0x00040000
str r4,[r0]
loop:
ldr r1,=0x00010000
ldr r2,=0x20200028
str r1,[r2]
ldr r0,=10000000
loop1:
sub r0,r0,#1
cmp r0,#0
bne loop1
ldr r1,=0x00000000
ldr r2,=0x20200028
str r1,[r2]
ldr r1,=0x00010000
ldr r2,=0x2020001C
str r1,[r2]
ldr r0,=10000000
loop2:
sub r0,r0,#1
cmp r0,#0
bne loop2
ldr r1,=0x00000000
ldr r2,=0x2020001C
str r1,[r2]
b loop
