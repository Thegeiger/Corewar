.name "zork"
.comment "just a basic living prog"
l2:
sti r1,%:live,%1#ceciestuncommentaire
and r1,%1,r1#ceci est un commentaire
live: live %1 #ceci est un commentaire
zjmp %:live #ceciestuncommentaire
