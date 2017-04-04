.name "Angry bird"
.comment "flying on your shit code"
#stock zjmp dans r2
ld %0, r10
#Protect

ld %:alive, r3
#write name for next live
alive:
	st r1, 6
	live %235
	st r10, -9
	fork %:alive
