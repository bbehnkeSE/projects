# prints sums of squares of integers from 0 to 100
# Code from Computer Organization and Design 5th edition
# Patterson and Hennessy 
# Appendix A.1

# Modified by Dianne Foreback to run on MARS simulator
#
# This code file demos a loop

	.text
	.globl main
main:
	subu $sp, $sp, 32
	sw $ra, 20($sp)
	sd $a0, 32($sp)
	sw $0, 24($sp)
	sw $0, 28($sp)
loop:
	lw $t6, 28($sp)
	mul $t7, $t6, $t6
	lw $t8, 24($sp)
	addu $t9, $t8, $t7
	sw $t9, 24($sp)  #result stored in $t9
	addu $t0, $t6, 1
	sw $t0, 28($sp)   
	ble $t0, 100, loop
	la $a0, str  #syscall requires $a0 to hold null terminated string
	
	#code to print the string using a system call
	li $v0, 4  # syscall 4 is print string
	syscall
	
	li $v0, 1 # syscall to print integer
	add $a0, $t9, $zero  # register $t9 holds the result
	syscall
	
	# exit MARS gracefully with syscall 10
	li $v0, 10
	syscall
	
	.data
	.align 0
str:
	.asciiz "The sum of squares from 0 .. 100 is "
