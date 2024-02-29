.data
.text
factorial:
	addi	$a0,$0,4 	#n
	addi	$a1,$a0,-1	#i = n-1
	addi	$v0,$0,1	# returnvärde
	
	beq	$a0,$0,stop	# 0! = 1 går direkt till stop
	add	$0, $0, $0	#NOP, stalling
	beq	$a0,1,stop	# 1! = 1
	add	$0, $0, $0	#NOP, stalling
	
loop:	beq	$a1,0,stop
	add	$0, $0, $0	#NOP, stalling
	addi	$a2,$0,0	# sum = 0
	addi	$a3,$0,0	# j = 0
	
	
multiply:
	add	$a2,$a0,$a2	# sum += num
	addi	$a3,$a3,1	# j++
	beq	$a3,$a1, L1	# j == i
	add	$0, $0, $0	#NOP, stalling
	beq	$0,$0,multiply
	add	$0, $0, $0	#NOP, stalling
	
L1:	addi	$a1,$a1,-1	# i--
	add	$a0,$a2,0	# ans = sum
	add	$v0,$a2,0	# v0 = a2

	beq	$0,$0,loop
	add	$0, $0, $0	#NOP, stalling

stop:
	beq	$0, $0, stop #1 = 1 loop forever
	add	$0, $0, $0	#NOP, stalling
