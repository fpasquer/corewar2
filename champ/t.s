.name "zork"
.comment ",I'M ALIIIIVE"

l2:		and r1, %0, r1
		sti r1, r2, r3
		sti r1, %:live, %1

live:	live %1
		zjmp %:live
