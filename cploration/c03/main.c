/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Cameron Peters
 * [TERM] FALL 2022
 * 
 ****************************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define MAX_LINE_LENGTH 200
 
int main(int argc, const char *argv[])
{	
	char out_file[50] = "";
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	
	// if user's command-line arguments does not equal 2, show error and exit
	if(argc != 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// open the input file
	FILE* fin = fopen(argv[1], "r");
	
	// if input file cannot be opened, show an error and exit
	if(fin == NULL){
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	
	// copy the input file name into output file name and concatinate .echo at the end
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo");
	
	// open the output file
	FILE *fout = fopen(out_file, "w+");
	
	// if output file cannot be opened, show an error and exit
	if(fout == NULL){
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	
	// reading each line one by one
	while(fgets(line, sizeof(line), fin)){
		
		// incrementing line count
		line_num++;
		
		//printing line count and line contents
		printf("[%04d] %s", line_num, line);
		
		// writing the line in file
		fprintf(fout, line);
	}
	
	// closing both input and output file pointers
	fclose(fin);
	fclose(fout);
	
	return 1;
}


