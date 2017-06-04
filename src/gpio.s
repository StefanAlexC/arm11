mov r1,#0x00004000
orr r1,[#0x20200004]
str r1,[#0x20200004]
loop:
clear:
mov r1,#0x00001000
str r1,[#0x20200028]
mov r0,#0xFF
sub r0,#00000001
cmp r0,#0x0
bne clear
set:
mov r1,#0x00001000
str r1,[#0x2020001C]
mov r0,#0xFF
sub r0,#00000001
cmp r0,#0x0
bne set
b loop

