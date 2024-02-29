  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"

	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  ####################################################################################
hexasc:

	andi	$a0,$a0,0xF	# keep 4 lsb and remove other bits
	addi	$t0,$a0,0x30	# finding the ascii code with position a0 + 0x30 and save it in t0

	ble	$a0,0x9,foo	# check if a0 <= 9 (decimal), if so, go to foo
	nop
	add	$t0,$a0,0x37	# otherwise(if a0 > 9) find the ascii code with pos. a0 + 0x37 and keep it in t0


foo:	move	$v0,$t0		# copy the value from t0 to v0
	jr	$ra		# return the address
	nop

 ######################################################################################
delay:
	#jr $ra
	#nop
	########
	PUSH	($ra)
 	li	$t0, 0			#i, lower bound
 	li	$t1,30000		#upperbound for the for-loop. 0x400000
 	move	$t2,$a0
 	
while:	slt	$t3,$0,$t2
	beq	$t3,$0,exit
	nop
	sub	$t2, $t2, 1		#ms = ms -1
	
for:	slt	$t4,$t0,$t1
	beq	$t4,$0, while
	nop
	addi	$t0, $t0, 1		#i = i + 1
	j	for
	nop	
	
exit:
	POP	($ra)
 	jr	$ra
 	nop
	
 ######################################################################################
time2string:

	PUSH($ra)
	
	
	move	$t6,$a0		# save the a0 in $t6
	li	$t5,0x00	# NULL
	
	
	#######################
	andi	$t0,$a1,0xF000	# extract 4 msb from a1 to t0
	srl	$t0,$t0,12	# shift the 4 bits to the lsb, bc hexasc reads only the 4 lsb
	
	
	move	$a0,$t0		# copy t0 to a0, i.e. passing the t0 as an argument to hexasc
	
	jal	hexasc
	nop
	
	sb	$v0,0($t6)
	########################
	andi	$t1,$a1,0xF00	# extract 4 msb from a1 to t1
	srl	$t1,$t1,8	# shift the 4 bits to the lsb, bc hexasc reads only the 4 lsb
	
	move	$a0,$t1		# copy t1 to a0, i.e. passing the t1 as an argument to hexasc
	
	jal	hexasc
	nop
	
	sb	$v0,1($t6)
	#######################
	li	$t2, 0x3A	
	sb	$t2,2($t6)	# adding semicolon in the middle.
	
	#######################
	andi	$t3,$a1,0xF0	# extract 4 msb from a1 to t3
	srl	$t3,$t3,4	# shift the 4 bits to the lsb, bc hexasc reads only the 4 lsb
	
	move	$a0,$t3		# copy t3 to a0, i.e. passing the t3 as an argument to hexasc
	
	jal	hexasc
	nop
	
	sb	$v0,3($t6)
	
	#######################
	
	andi	$t4,$a1,0xF	# extract 4 msb from a1 to t4. don't need shift bc it's already in lsb.
	
	move	$a0,$t4		# copy t4 to a0, i.e. passing the t4 as an argument to hexasc
	bne	$t4,2, L1
	nop
	
	li	$t7,0x54
	li	$t8,0x57
	li	$t9,0x4f
	
	sb	$t7,4($t6)
	sb	$t8,5($t6)
	sb	$t9,6($t6)
	sb	$t5,7($t6)
	
	j	go
	nop
	
	
	L1:
	jal	hexasc
	nop
	sb	$v0,4($t6)
	
	#######################
	
	sb	$t5,5($t6)
	#######################
	
	
	go:
	POP($ra)
	jr	$ra
	nop
	


	
	
	
	
	
	
	
