.name "I.C. Winner"
.comment "I.C. Winner"

start:
	st r1, 6
	live %0
	st r1, 6
	live %0
	st r1, 6
	live %0
	st r1, 6
	live %0
	st r1, 6
	live %0
	#fork %-50
	xor r2, r2, r2
	zjmp %:start


# init:

# 	ld %16777216, r2
# 	ld %33779714, r3 # st r2, 50
# 	ld %3277680, r4 # st r1, 46
# 	ld %65582, r5 # too

# start:
	
# 	st r3, 50
# 	st r4, 49
# 	st r5, 48
# 	#st r2, 50
# 	#st r1, 46


# 	#st r1, 6
# 	#live %0


