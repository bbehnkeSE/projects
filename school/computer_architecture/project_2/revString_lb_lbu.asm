# Dianne Foreback 
# Feb 2016
# 
# Code to show 
# 1. the difference between lb and lbu
# 2. to reverse an input string
#
# Prompts the user for input of 4 characters.
# Stores the user input into memory "thestring"
# then displays the stored "thestring" , reverses it
# placing the reversed string in "thestringRev",
# and displays the reversed string
#
# This code does NOT use looping
#
#
# If using MARS, make certain in "Settings" to check
# "prompt dialog for input syscalls 5,6,7,8,12"
#
            .data      # data segment
	    .align 2   # align the next string on a word boundary
number:     .word -1   # -1 placed in memory
prompt:     .asciiz  "Please enter 4 characters (upper/lower or mixed case):\n"
	    .align 2   #align next prompt on a word boundary
display:    .asciiz  "You entered the string: "
            .align 2   # align users input on a word boundary
displayRev: .asciiz "And your string reversed is: "
	    .align 2
thestring:  .space 6   # will hold the user's input string thestring of 4 bytes 
                       # last two chars are \n\0  (a new line and null char)
                       # If user enters 5 characters then clicks "enter" or hits the
                       # enter key, the \n will not be inserted into the 6th element
                       # (the actual users character is placed in 5th element).  the 
                       # 6th element will hold the \0 character.
            .align 2   # aligns on a word boundary 
thestringRev:  .space 6   # reserve four bytes for the reversed string
            .text      # code section begins
            .globl	main
main:  

################################################################
# load byte example shows difference between lbu and lb
        la $t0, number            # put the adress of number buffer in $t0
        lbu $t1, 0($t0)           # first byte of number in the register $t0, zero extended 
        lb $t2, 0($t0)            # first byte of number placed in register $t2 is sign extended
###############################################################
# system call to prompt user
	 la $a0,prompt		# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
###############################################################
# system call to store user input into string thestring
	li $v0,8		# system call 8 for read string needs its call number 8 in $v0
        			# get return values
	la $a0,thestring	# put the address of thestring buffer in $t0
	li $a1,22 	        # maximum length of string to load, null char always at end
				# but note, the \n is also included providing total len < 22
        syscall
 
################################################################
# system call to display "You entered the string: "
	 la $a0,display 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  
################################################################
# system call to display user input that is saved in "thestring" buffer
	 la $a0,thestring	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
###############################################################
# Reverse the users input
        la $t0, thestring    #t0 gets address of thestring
        la $t2, thestringRev #$t2 gets address of theStringRev
        lbu $t1,0($t0)       #t1 gets first byte stored at thestring
        sb $t1,3($t2)        # store first byte in last byte
        lbu $t1,1($t0)       # get next byte, notice adding one to the address of theString
        sb $t1,2($t2)        # store second byte in 3rd position
        lbu $t1,2($t0)       
        sb $t1,1($t2)        # store third byte in 2nd position
        lbu $t1,3($t0)
        sb $t1,0($t2)        # store fourth byte in 1st position
################################################################
# system call to display "And your string reversed is: "
	 la $a0,displayRev 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  	
################################################################
# system call to display user input that is reverse in the buffer rev_string
	 la $a0,thestringRev	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
 ###############################################################

# Exit gracefully
         li   $v0, 10       # system call for exit
         syscall            # close file
###############################################################
