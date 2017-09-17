.name "bot"
.comment "just a basic living bot"

# live %1

# com: live %2
# com1:
# live %3
# live %-1
# live %-2
# live %4 l
# live %5 #af
# live $6

# live %5, %5, %5
# live %21474836479

# live %5, %5 %5
# live %5, 5, %
# live r1, %r1
# live %%
# live %:live
# live
# live %live, %5



# ld %65, r1
# ld 8, r2
# ld %:link, r1
# ld r1, %65

# live2: live %65
# live %:live1
# live1: live %65
# live %:live2



# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0


# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2
# xor r2, r2, r2

# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0
# st r1, 6
# live %0
# fork %-50
# xor r2, r2, r2
# zjmp %-58

st r1, 6
live %0

