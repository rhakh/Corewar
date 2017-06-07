.name "bot"
.comment "just a basic living bot"

ld %65, r3
ld %64, r14
ld %9, r4
ld %20, r5
ld %1, r11

copy:
lld %14, r6
lld %16777216, r2

add r11, r14, r14
sti r2, r3, r10
sub r3, r4, r3
sti r1, r3, r10
add r3, r5, r3
sub r6, r6, r6
aff r14

#comment

zjmp %:copy
