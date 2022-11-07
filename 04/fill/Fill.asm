// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(BLACK)		//Fill screen
@KBD		//Register keyboard
D=M		    //d = keyboard 
@WHITE	    //Go to white loop if d (keyboard) is = 0; 
D;JEQ		
@24575		//load the last pixel of the screen
D=M		    //set last pixel of screen to d
@WHITE	    //Go to white loop if d (last pixel of screen) < 0
D;JLT		
@i		    //Register i 
D=M		    //d = i
@16384		//load first pixel of screen
D=A+D		//d = (first pixel of screen) + I
A=D		    //set d to memory
M=-1		//Fill all pixels in 16-bit register
@i		    //Register i
M=M+1		//Ram[0] = i, increment i
@BLACK	    //Go back to beginning of the loop
0;JMP		//NULL, jump back to black loop

(WHITE)	    //Remove 
@KBD		//Register keyboard
D=M		    //d = keyboard
@BLACK	    //Go to black loop if keyboard register > 0 
D;JGT		
@i		    //Register i 
D=M		    //d = i
@16384		//Register screen first pixel 
D=A+D		//d = (first pixel) + i
A=D		    //set d to memory
M=0		    //Removes all filled pixels in 16-bit register
@i		    //Register i
M=M-1		//De increment i
@WHITE		//Goes back to beginning of white loop
0;JMP		//NULL, go back to the white loop