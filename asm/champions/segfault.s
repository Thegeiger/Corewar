.name "segfaultomatron"
.comment "salut, ca va ?"
st r1,1
live %2
ld %600,r3
st r1,r600
st r1,1
fork %600000
live %2
add r600,r600,r600
sub r600,r600,r600
and %r1,-70000,r600
st r1,1
live %2
sti r10,%-303,%0
st r1,1
ldi 40000,%34,r4	
live %2
st r1,1
live %2
st r1,1
live %2
lld %600,r1
st r1,1
live %2
st r1,1
live %2
ld %289,r4
aff r4
lfork %600000