  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,10		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
 
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



	
	
	

	
	
	
	
	
	
 	
 	
 	
 	
 	
 	
 	
 	

