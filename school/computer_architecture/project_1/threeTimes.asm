# Starter code for threeTimes.asm
# Put in comments your name and date please.  You will be
# revising this code.
#
# Dianne Foreback 
# 
# 
# This code displays the authors name (you must change
# outpAuth to display YourFirstName and YourLastName".
#
# The code then prompts the user for 3 integer values.
# The code outputs the summation of these 3 values multiplied by 3.
#
# In MARS, make certain in "Settings" to check
# "popup dialog for input syscalls 5,6,7,8,12"
#
            .data      # data segment
	    .align 2   # align the next string on a word boundary
outpAuth:   .asciiz  "This is Brian Behnke presenting threeTimes.\n"
outpPrompt: .asciiz  "Please enter an integer: "
	    .align 2   #align next prompt on a word boundary
outpStr:    .asciiz  "The sum of your numbers multiplied by 3 is: "
            .align 2   # align users input on a word boundary
#
# main begins
            .text      # code section begins
            .globl	main 
main:  
###############################################################
# system call to display the author of this code
	 la $a0,outpAuth	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	

#
# system call to prompt user for input
	 la $a0,outpPrompt	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
###############################################################
# write a system call to read the user's integer value
	 li $v0,5
	 syscall

	 #Store user input in register 8
	 move $t0,$v0
	 
	 la $a0,outpPrompt	
	 li $v0,4		
	 syscall
	 
	 li $v0,5
	 syscall

	 move $t1,$v0
	 
	 la $a0,outpPrompt	
	 li $v0,4		
	 syscall
	 
	 li $v0,5
	 syscall

	 move $t2,$v0
	 
	 #Adds the three user values together and stores them in register 12
	 add $t3, $t0,$t1
	 add $t4, $t3,$t2
	 
	 #Stores the value 3 in register 13 for multiplication later
	 addi $t5, $zero,3
	 
	 
# We have not studied looping, so you will need to repeat the prompt for input
# and do the calculation as you see fit

	 #Multiplies the sum of user inputs by the value in register 13 (3) and stores them in register 16
	 mul $t6, $t5,$t4

#
# system call to display "The sum of your numbers multiplied by 3 is: "
	 la $a0,outpStr 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  	
################################################################
# write a system call to display the calculation
	 li $v0,1
	 move $a0,$t6
	 syscall

#
# Exit gracefully
         li   $v0, 10       # system call for exit
         syscall            # close file
###############################################################
