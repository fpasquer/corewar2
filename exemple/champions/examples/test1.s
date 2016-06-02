.name "test1"
.comment "c'est mon test1"

entry:
		sti r1, %:put_train, %1
		ld %67, r2
		ld %4, r3

put_train:
		live %67
		add r3, r2, r2
		st r1, r2
		ld %0, r16
		zjmp %:put_train
