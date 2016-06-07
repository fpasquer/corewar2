.name "test_1"
.comment "I'm alown"

	fork %:dest
	ld %56, r5
	st r5, 67

dest:
	live %-1

