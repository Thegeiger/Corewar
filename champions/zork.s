.name "zork"
.comment "just a basic living prog"
l2:
	st r1,2
live:	live %1
	zjmp %:live
