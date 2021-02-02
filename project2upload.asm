# Description: This program will perform a letter count
# on several strings entered by the user.

.data

strprompt: .asciiz "Enter up to 100 characters:\n"	#string to prompt the user
userstr: .space 100 					#saves room for up to 100 characters, to be read in later
str2: .asciiz "\n\nLetter Frequency Table\n"
endstr: .asciiz "No letters entered. Program terminating."
letfreqtable: .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 #sets up array for 26 letter counts

.text

.globl main

main:
li $v0, 4      			#load the instruction to print a string
la $a0, strprompt 		#load the address of the string to prompt the user
syscall 			#print the string
la $s0, userstr 		#load the address where string is to be stored
add $a0, $s0, $zero 		#prepare to read in a string to the address just loaded
addi $a1, $zero, 100 		#store the maximum length of the string to be read in
li $v0, 8 			#load the instruction to read in a string
syscall 			#read in the string

jal lettersOnly 		#calls the function to remove punctuation etc

lb $t0, 0($s0) 			#load the first character of the user's string to $t0
beq $t0, $zero, endpgm 		#user's string contains no letters; program terminates
li $v0, 4 			#load the instruction to print a string
add $a0, $s0, $zero 		#load the address of the string
syscall 			#print the string

jal lettertable 		#calls function to create and print a letter frequency table
li $v0, 11 			#load the instruction to print a character
addi $a0, $zero, 10 		#save a newline character
syscall 			#print twice
syscall

j main 				#start over and read in another string

endpgm:
li $v0, 4 			#load the instruction to print a string
la $a0, endstr 			#load the address of the string
syscall
li $v0, 10 			#load the instruction to exit the program
syscall 			#exit

lettersOnly: 			# requires that the base address of a string be stored in $a0
add $t0, $a0, $zero 		#$t0 is address of next character in the string
add $t1, $a0, $zero 		#will be used to write the new, "cleaned" string
loop:
lb $t2, 0($t0) 			#load next character of the user's string as read
addi $t3, $zero, 96 		#last ASCII value before lowercase letters
addi $t4, $zero, 123 		#first ASCII value after lowercase letters
slt $t3, $t3, $t2 		#check if current character is a lowercase letter
slt $t4, $t2, $t4
and $t3, $t3, $t4
bne $t3, $zero, copychar 	#character is a lowercase letter; write it to the new string
addi $t3, $zero, 64 		#last ASCII value before uppercase letters
addi $t4, $zero, 91 		#first ASCII value after uppercase letters
slt $t3, $t3, $t2 		#check if current character is an uppercase letter
slt $t4, $t2, $t4
and $t3, $t3, $t4
bne $t3, $zero, copychar 	#character is an uppercase letter; write it to the new string
beq $t2, $zero, copychar 	#copies the null terminating character if reached
j finish 			#character is not a letter or null-terminating character and should not be saved
copychar:
sb $t2, 0($t1) 			#stores current letter as next character of cleaned string
addi $t1, $t1, 1 		#prepares to write a character to the next 1-byte space
finish:
addi $t0, $t0, 1 		#prepares to read next character
bne $t2, $zero, loop		#starts loop over unless null-terminating character has been reached
jr $ra 				#returns to calling function

lettertable: 			#requires that the address of a string be in $a0
add $s1, $a0, $zero 		#save address of string in $s1
la $s2, letfreqtable 		#store address of letter frequency array
add $t0, $s2, 104 		#designates end of the array
add $t1, $s2, $zero 		#pointer to traverse letter table
empty:
sw $zero, 0($t1) 		#set an element in letter frequency array to 0
addi $t1, $t1, 4 		#traverse to next element
bne $t1, $t0, empty 		#repeat until end of array is reached
				#letter frequency array has been initialized to zero; now, begin counting letters
count:
lb $t2, 0($s1) 			#loads next letter in user string
beq $t2, $zero, printtable 	#if null terminating character is reached, exit loop
add $t1, $s2, $zero 		#reset $t1 to beginning of array
slti $t3, $t2, 91 		#checks if this letter is uppercase or lowercase
bne $t3, $zero, uppercase 	#skips next step if letter is uppercase
addi $t2, $t2, -32 		#converts the letter to uppercase
uppercase:
addi $t2, $t2, -65 		#subtracts the value of ASCII A; $t2 now contains index of appropriate element of frequency array
sll $t2, $t2, 2 		#multiply array index by 4,the size in bytes of one element
add $t1, $t1, $t2 		#$t1 now points to correct array element
lw $t4, 0($t1) 			#load an element from the frequency array
addi $t4, $t4, 1 		#adds 1 to the count for appropriate letter
sw $t4, 0($t1) 			#store new count for that letter
addi $s1, $s1, 1 		#increment to next letter in string
j count 			#start loop over
				#all letters in string have been counted; now, print the table
printtable:
li $v0, 4 			#load the instruction to print a string
la $a0, str2 			#load the address of the table title
syscall 			#print the string
add $t1, $s2, $zero 		#reset pointer to beginning of array
add $t4, $zero, $zero 		#sets column count to zero
addi $t3, $zero, 13 		#saves desired column count to check for newline
printcounts:
lw $a0, 0($t1) 			#load next letter count to $a0, to be printed
li $v0, 1 			#load instruction to print an int
syscall
addi $t4, $t4, 1 		#add 1 to column count
beq $t4, $t3, newline 		#prints a new line if 13 columns have been printed
addi $a0, $zero, 32 		#stores the space character
j printspace 			#skips ahead to print the character
newline:
addi $a0, $zero, 10 		#stores the newline character
printspace:
li $v0, 11 			#loads instruction to print a character
syscall 			#print the character
addi $t1, $t1, 4 		#increment to next array element
bne $t1, $t0, printcounts	#restart loop unless at end of array
jr $ra 				#print loop is finished; return to calling function

.end