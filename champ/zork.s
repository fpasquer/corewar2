.name "zork"
.comment ",I'M ALIIIIVE"

l2:		sti r1,%:live,%1
		and %3, %3, r3

live:	live %1
		zjmp %:live
