.name "bot"
.comment "just a basic living bot"

la: live %2

sti r1, r1, r1
sti r2, %65, r1 
sti r3, %65, %66
sti r4, %:la, r1
sti r5, %:li, r1
sti r6, :li, r1 
sti r7, :li, %65
sti r8, :la, r1 
sti r9, 8, r1
sti r10, r1, %65 
sti r11, r1, %:li
sti r12, r1, %:la
sti r13, r1, r2

li: live %1




