.name "test"
.comment "qwe"

#ld %196557, r5
#ld %225282, r4
#ld 	%192151552, r5
#sti r1, %:live, %1
sub r5,r5, r6
live: live %1
live %10
zjmp: zjmp %10
#st r4, 55
#st r5, 47
#live: live %1

#fork: fork %:live
#live %1
#st r5, -8

#ld %189267968, r3
#ld %185597952, r4
#ld %187695104, r5
#ld %186974208, r6
#ld %188743680, r7
#ld %185925632, r8
#ld %188088320, r9
#ld %186056704, r10

#st r10, 300
#st r9, 40
#st r8, 50
#st r7, 60
#st r6, 70
#st r5, 80
#st r4, 90
#st r3, 100
