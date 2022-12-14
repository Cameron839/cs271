/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Cameron Peters
 * [TERM] FALL 2022
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"


int main(int argc, const char *argv[])
{
    //if users command-line argument does not equal 1 show error and exit
    if(argc != 2){
        //printf("Usage: %s [filename]\n", argv[0]);
        //exit(EXIT_FAILURE);
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }
    
    // open the input file
    FILE *fin = fopen(argv[1], "r");
	
    // if input file cannot be opened, show an error and exit
    if(fin == NULL){
        //perror("Unable to open file!");
        //exit(EXIT_FAILURE);
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]); 
    }
    
    parse(fin);
   // symtable_print_labels();
    fclose(fin);
}


