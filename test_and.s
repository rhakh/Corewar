.name "bot"
.comment "just a basic living bot"

la: live %2

xor r1, r2, r1
xor %65, %324, r2
xor %56, :li, r3
xor :li, %6, r4
xor :li, :la, r5
xor 8, :la, r6
xor :li, 8, r7
xor 8, 9, r8

li: live %1

