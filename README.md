### disassembler


Introduction:
In this project, we will design a disassembler using C++. Disassembler is used for converting MIPS instruction into symbolic command, like assembly code. 

Design:
Before I design the disassembler, I will check if the user gives the correct input. The input file has to be in the same folder with the source file.  

The input file is nothing but a .obj file. Each line contains a 32-bit instruction encoded as 8 hexadecimal digits without a leading “0x”. 

Before I actually read the file in, I will check if the length of each line is correct using a for loop. The correct length should be 8. Every line that is not 8 should give me the error and exit. This is my first error handling. 

If no error has encountered before, then it will go through a real for loop. In this for loop, the hex command will be passed to a function called hex_to_bin, which is simply a state machine that convert 16 hex characters into binary code. 

After I get the binary code, I will pass each binary code into a function called bin_to_symbol. In this function, I first divide 32 bit binary into several fields. For example, the opcode is 0-5 and rs is 6-10. I use several function to achieve this. Specifically, get_register function will handle the register according to the naming convention on the Green Sheet. Signed_conversion fucntion is used to deal with the 2's complement. When using the immediate, unless it states the command is unsigned, all the immediate will be treated as signed. And convert_to_hex function will convert the integer to hex, for example, 1 will be converted to 0004. 

When I encounter the branch instruction, like bne and beq. I create a list called address_list to store the address, which are the targets of these commands.

So after the steps above, I will be able to get the symbolic command. I create a map, called command_map, to store every command. I make a pair of command and its address so when I later label the command, I will have access to command's address. 

The way I label the command is that I create a function called found_the_address. It's a boolean function and will return true if the address from the address_list matches the address of current command. Therefore, my logic is if the address from the list is the address of command from the commad_map, print out the address and command, otherwise, simply print out the command. 

Another error handling is to check the string that cannot be disassembled. The way I do this is when I convert the binary code to symbolic command, I will check field if it's valid. If it's not valid, I will print the address and that string out to the command window. 


 



