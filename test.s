.name "test"
.comment "qwe"

ld  %11, r4
ld 	%173277184, r5
sti r1, %:live, %1

live: live %1
fork: fork %:live

st r4, 55
st r5, 54
st r5, -13
