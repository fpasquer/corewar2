.name "zork"
.comment ",I'M ALIIIIVE"

l2:		sti r1,%-3000,%1
		and %0, %1, r3

live:	live %1
		zjmp %:live
