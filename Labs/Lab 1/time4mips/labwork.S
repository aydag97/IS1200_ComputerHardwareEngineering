  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.globl delay
.globl time2string

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.text

  #
  # Please add your own code below this line
  #
hexasc:

	andi	$a0,$a0,0xF	# keep 4 lsb and remove other bits
	addi	$t0,$a0,0x30	# finding the ascii code with position a0 + 0x30 and save it in t0

	ble	$a0,0x9,foo	# check if a0 <= 9 (decimal), if so, go to foo
	nop
	add	$t0,$a0,0x37	# otherwise(if a0 > 9) find the ascii code with pos. a0 + 0x37 and keep it in t0

foo:
	move	$v0,$t0		# copy the value from t0 to v0
	jr	$ra		# return the address
	nop
	
delay:
 	addi	$t0, $0, 0	#i, lower bound
 	addi	$t1, $0, 0x4711	#upperbound for the for-loop. 10000 /30000
while:
	slt	$t3, $0, $a0
	beq	$t3,$0, end
	nop
	sub	$a0, $a0, 1	#ms = ms -1
	
for:
	slt	$t2, $t0, $t1
	beq	$t2, $0, end
	nop
	addi	$t0, $t0, 1		#i = i + 1
	j	for
	nop
	
end:
 	jr $ra
 	nop
 	
time2string:
	
	PUSH	$ra
	
	andi	$t0, $a1, 0xF000	#extract the 4 msb from a1 (minute 5) to t0
	srl	$t0, $t0, 12	#shift the 4 bits to the lsb for hexasc to read
	
	move	$t6, $a0	#store everything in t6
	move	$a0, $t0	
	
	jal	hexasc
	nop
	sb	$v0, 0($t6)
	
	andi	$t1, $a1, 0xF00		#extract the 4 msb from a1 (minute 5) to t0
	srl	$t1, $t1, 8	#shift the 4 bits to the lsb for hexasc to read
	
	move	$a0, $t1	
	jal	hexasc
	nop
	sb	$v0, 1($t6)
	
	jal	hexasc
	nop
	li	$t2, 0x3a
	sb	$t2, 2($t6)
	
	andi	$t3, $a1, 0xF0		#extract the 4 msb from a1 (minute 5) to t0
	srl	$t3, $t3, 4	#shift the 4 bits to the lsb for hexasc to read
	move	$a0, $t3	
	jal	hexasc
	nop
	sb	$v0, 3($t6)
	
	andi	$t4, $a1, 0xF		#extract the 4 msb from a1 (minute 5) to t0
	move	$a0, $t4	
	jal	hexasc
	nop
	sb	$v0, 4($t6)
	
	li	$t5, 0x00
	sb	$t5, 5($t6)
	
	POP	$ra
	
	jr	$ra
	nop



