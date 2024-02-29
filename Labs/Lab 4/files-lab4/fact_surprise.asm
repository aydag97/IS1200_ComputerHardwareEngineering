.data
.text

factorial:
	add	$a0, $0, 0	#n
	addi	$v0, $0, 1	# returnvärde
	
	beq	$a0,1,stop	# 1! = 1
	add	$0, $0, $0	#NOP, stalling
	
loop:
	beq	$a0,$0, stop	
	add	$0, $0, $0	#NOP, stalling
	
	mul	$v0, $v0, $a0 	
	addi 	$a0,$a0,-1	# n--
	
	beq	$0, $0, loop
	add	$0, $0, $0	#NOP, stalling
	
stop:
	beq	$0, $0, stop #1 = 1 loop forever
	add	$0, $0, $0	#NOP, stalling