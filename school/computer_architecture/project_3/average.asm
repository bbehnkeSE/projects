# Brian Behnke
# April 04, 2020
# Accepts user-generated float values and calculates the average

		.data
		.align 2
outpAuth:	.asciiz "This is Brian Behnke presenting average. \n"
amountPrompt:	.asciiz "How many numbers would you like to average? "
		.align 2
userNumPrompt:	.asciiz "Please enter a 3 digit decimal d.dd: "
		.align 2
resultMessage:	.asciiz "The average is: "
		.align 2
zeroMessage:	.asciiz "Number of iterations selected: 0. Ending program..."
		.align 2
result:		.space 32	# Reserve space for final result
		
		.text
		.globl main
main:
#######################################################
# System call to display the author of this code
	la $a0, outpAuth
	li $v0, 4
	syscall
	
# Syscall to ask user for amount of decimals to average
	la $a0, amountPrompt
	li $v0, 4
	syscall
	
# Syscall to store user input as an integer
	li $v0, 5
	syscall
	
# Store input in $t2
	move $t2, $v0
	
# Allocate memory for floats
	sll $a0, $v0, 2
	li $v0 9
	syscall

# Invoke while loop
	move $t4, $v0		# Allocates memory for user floats
	addi $t0, $zero, 0	# Index for Collector loop
	addi $t1, $zero, 0	# Index for Add loop
	jal Collector
		
Exit:
	li $v0, 10		# Exit syscall
	syscall
#######################################################

Collector:
	beq $t2, $zero, zeroEnd	
	la $a0, userNumPrompt	# Ask user for float
	li $v0, 4
	syscall
	
	li $v0, 6		# Store user float in $f0
	syscall
	
	swc1 $f0, 0($t4)	# Save user decimal in array at value of $t4's location
	addi $t0, $t0, 1 	# ++i
	addi $t4, $t4, 4	# Moves to next memory location
	beq $t0, $t2, Add	# If iterations equal user-given amount, calculate the sum of floats
	j Collector

# Loop to add floats	
Add:
	lwc1 $f2, 0($t4)	# Load float at value of $t4's location to $f2
	add.s $f4, $f4, $f2	# $f4 += $f2
	beq $t1, $t2, Average	# If iterations equal user-given amount, calculate average by dividing sum by total amount
	addi $t1, $t1, 1	# ++i
	addi $t4, $t4, -4	# Iterates through floats backwards
	j Add
	
Average:
	mtc1 $t2, $f6
	cvt.s.w $f6, $f6 	# Convert user inputted amount into a float for division
	div.s $f12, $f4, $f6	# Divide sum of floats by total amount and stores result in $f12
	
# Syscall to print resultMessage
	la $a0, resultMessage
	li $v0, 4
	syscall
	
# Syscall to print average
	swc1 $f12, result($zero)
	la $a0, result
	li $v0, 2
	syscall
	
# Exit program
	j Exit
	
zeroEnd:
	la $a0, zeroMessage
	li $v0, 4
	syscall
	j Exit
	
	
	
	
