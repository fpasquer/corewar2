.name "test"
.comment "c'est mon test"

entry:
		sti r1, %:attack1, %1
		sti r1, %:attack2, %1
		sti r1, %:attack, %1
		sti r1, %:stay_alive, %1
		sti r1, %:alive, %1
		sti r1, %:wall, %1
		fork %:init_wall
		fork %:stay_alive
		ld %654848, r5
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		st r5, 511
		ld %0, r16
		zjmp %507

attack1:
		live %90
		fork %:attack2
		live %90
		fork %:attack3
		ld %0, r16

attack3:
		live %787
		fork %:attack1
		ld %0, r16
		zjmp %:attack3

attack2:
		live %89
		fork %:attack1
		live %89
		ld %0, r16
		zjmp %:attack

init_wall:
		ld %0, r2
		ld %0, r16

wall:
		live %670
		st		r2, -81
		st		r2, -90
		st		r2, -99
		st		r2, -108
		st		r2, -117
		st		r2, -126
		st		r2, -135
		st		r2, -144
		st		r2, -153
		st		r2, -162
		st		r2, -171
		st		r2, -180
		st		r2, -189
		st		r2, -198
		st		r2, -207
		st		r2, -216
		st		r2, -225
		st		r2, -234
		st		r2, -243
		st		r2, -252
		st		r2, -261
		st		r2, -270
		st		r2, -279
		st		r2, -288
		st		r2, -297
		st		r2, -306
		st		r2, -315
		st		r2, -324
		st		r2, -333
		st		r2, -342
		st		r2, -351
		st		r2, -360
		st		r2, -369
		st		r2, -378
		st		r2, -387
		st		r2, -396
		st		r2, -405
		st		r2, -414
		st		r2, -423
		st		r2, -432
		st		r2, -441
		st		r2, -450
		st		r2, -459
		st		r2, -468
		st		r2, -477
		st		r2, -486
		st		r2, -495
		st		r2, -504
		zjmp	%:wall

stay_alive:
	live	%9423
	fork	%:stay_alive
	ld		%0, r16

alive:
	live	%56752
	zjmp	%:alive

attack:
		live %890


