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

#define MAX_LINE_LENGTH  200


/*extract_label function*/
char *extract_label(const char *line, char* label){
    int i = 0;
    //assign a pointer the the line and increment through the line
    for(const char *s = line;  *s++;){
        //if first character in line is a (
        if((*s == '(') || (*s == ')')){
            //continue through loop
            continue;
        } else {
            label[i++] = *s;
        }
    }
    label[i] = '\0';
    return label;

}
    



/*Fucntion: is_Atype*/
bool is_Atype(const char *line){
    if(line[0] == '@'){
        return  1;
    }else{
        return  0;
    }
}

/*Function: is_label*/
bool is_label(const char *line){
    if((line[0] == '(') && (line[strlen(line)-1]) == ')'){
        return 1;
    } else {
        return 0;
    }
}

/*Function: is_Ctype*/
bool is_Ctype(const char *line){
    if((line[0] == 'M') || (line[0] == 'D') || (line[0] == '0') || (line[0] == 'A')){
        return 1;
    } else {
        return 0;
    }
}


/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

    char s_new[strlen(s) + 1];
    int i = 0;
    
    for (char *s2 = s; *s2; s2++) {
       
        if((*s2 == '/') && (*(s2+1) == '/')){
            break;
        } else if(!isspace(*s2)) {
            s_new[i++] = *s2;
        }
        
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
    char line[MAX_LINE_LENGTH]={0};
    char label[MAX_LABEL_LENGTH] = {0};
    
    unsigned int counter = 0;
   // char insert_label[20] = "";
    unsigned int line_num  = *line;
    unsigned int instr_num = counter;
    
    while(fgets(line, sizeof(line), file)){
        
        line_num++;
        
        if(instr_num  > MAX_INSTRUCTIONS){
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
            
            
        strip(line);
        
        //if first character of the line is not NULL, continue to next
        if(*line == '\0'){
            continue;
        }
    
        
        char inst_type = '\0';
        
        
        if(is_Atype(line) == 1){
            inst_type = 'A';
            //printf("%c  %s\n", inst_type, line);
            //counter++;
        }
        
        if(is_label(line) == 1){
            inst_type = 'L';
            //extract_label(line, label);
            
            
            strcpy(line, extract_label(line, label));
            
            if (!isalpha(*label))
                exit_program(EXIT_INVALID_LABEL, line_num, line);
            
            
            if(symtable_find(label) != NULL)
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
            
            
            symtable_insert(label, instr_num);
            continue;
        }
        
        if(is_Ctype(line) == 1){
            inst_type = 'C';
            //printf("%c  %s\n", inst_type, line);
            //counter++;
        }
         printf("%u: %c  %s\n", instr_num, inst_type, line);
         instr_num++;
    }
}
