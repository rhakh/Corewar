.name "bot"
.comment "just a basic living bot"

la: live %2

zjmp %65
zjmp %:li
zjmp %:la

li:
live %1
la: live %2
la:
live %2


