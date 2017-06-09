.name "bot"
.comment "just a basic living bot"

la: live %2

ldi r1, r1, r1
ldi %65, r1, r2
ldi %65, %66, r2
ldi %:la, r1, r3
ldi %:li, r1, r3
ldi :li, r1, r4
ldi :li, %65, r4
ldi :la, r1, r5
ldi 8, r1, r6
ldi r1, %65, r7
ldi r1, %:li, r8
ldi r1, %:la, r9
ldi r1, r2, r10

li: live %1


