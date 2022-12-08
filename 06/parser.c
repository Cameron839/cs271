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
#include "hack.h"

#define MAX_LINE_LENGTH  200


/*add_predefined_symbols function*/
void add_predefined_symbols(){
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        predefined_symbol ps = predefined_symbols[i];
        symtable_insert(ps.name, ps.address);
    }
}


/*assemble functin*/
void assemble(const char * file_name, instruction* instructions, int num_instructions){
    
    char *f_name = malloc(strlen(file_name) + 5);
   
    strcpy(f_name, file_name);
    strcat(f_name, ".hack");

    FILE * file = fopen(f_name, "w");

    opcode opcode;
    int address = 16;
    for(int i=0; i < num_instructions; i++) {
        if(instructions[i].sometype == A_type) {
            if((instructions[i].instr.a.operand.address) == 1){
                opcode = instructions[i].instr.a.operand.address;
    } else {
        if((symtable_find(instructions[i].instr.a.operand.label) == NULL)){
            opcode = address;
            symtable_insert(instructions[i].instr.a.operand.label, address++);
    }else{
        opcode = symtable_find(instructions[i].instr.a.operand.label)->addr;
    }

        free(instructions[i].instr.a.operand.label);
}
    }else if(instructions[i].sometype == C_type){
        opcode = instruction_to_opcode(instructions[i].instr.c);
    }
fprintf(file, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(opcode));
        }
        fclose(file);
    
}

/*instruction_to_opcode function*/
opcode instruction_to_opcode(c_instruction instr){
    opcode op = 0;
    op |= (7 << 13);
    
    
    op |= (instr.a << 12);
    op |= (instr.comp << 6);
    op |= (instr.dest << 3);
    op |= (instr.jump << 0);
    
    return op;
    
}



/*parse_c_instruction function*/
void parse_C_instruction(char *line, c_instruction *instr){
    
    char *temp = strtok(line, ";");
    char *jump = strtok(NULL, "=");
    
    char *comp;
    
    if(jump == NULL){
        char *dest = strtok(temp, "=");
        instr->dest = str_to_destid(dest);
        instr->jump = str_to_jumpid(jump);
        
        comp = strtok(NULL, "=");
    } else {
        
        instr->jump = str_to_jumpid(jump);
        instr->dest = str_to_destid(NULL);
        
        comp = temp;
    }
    
    int a;
    instr->comp = str_to_compid(comp, &a);
    instr->a = a;
    
    
    
   /* //(dest=comp;)jump
    char *temp = strtok(line, ";");
    
    //dest=comp; (jump)
    char *jump = strtok(NULL, ";");
    
    //(dest)=comp
    char *dest = strtok(temp, "=");
    
    //dest=(comp)
    char *comp = strtok(NULL, "=");
    
    
   instr->jump = str_to_jumpid(jump);
   instr->dest = str_to_destid(dest);
    
    int a = 0;
    instr->comp = str_to_compid(comp, &a);
    instr->a = a ? 1: 0;
    */
}


/*parse_A_instruction function*/
bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = "";
    s = malloc(strlen(line));
    strcpy(s, line+1);
    
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if(s == s_end){
        instr->operand.label = malloc(strlen(line));
        strcpy(instr->operand.label, s);
        instr->is_addr = false;
    } else if (*s_end != 0){
        return false;
    } else {
        instr->operand.address = result;
        instr->is_addr = true;
    }
    return true;
}


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
int parse(FILE * file, instruction *instructions){
    instruction instr;

    //char tmp_line[MAX_LINE_LENGTH] = {0};
    char line[MAX_LINE_LENGTH]={0};
    //strcpy(tmp_line, line);
    char label[MAX_LABEL_LENGTH] = {0};
    
    unsigned int counter = 0;
   // char insert_label[20] = "";
    unsigned int line_num  = *line;
    unsigned int instr_num = counter;
    
    add_predefined_symbols();
   
    
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
    
        
        //char inst_type = '\0';
        
        
        if(is_Atype(line) == 1){
            //inst_type = 'A';
            //printf("%c  %s\n", inst_type, line);
            //counter++;
            if (!parse_A_instruction(line, &instr.instr.a)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
             }
             instr.sometype = A_type;
            printf("A: %s\n", line + 1);
    
        }
        
        
        if(is_label(line) ){
            //inst_type = 'L';
            //extract_label(line, label);
            
            
            strcpy(line, extract_label(line, label));
            
            if (!isalpha(*label))
                exit_program(EXIT_INVALID_LABEL, line_num, line);
            
            
            if(symtable_find(label) != NULL)
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
            
            
            symtable_insert(label, instr_num);
            continue;
            
        }
        
        
        if (is_Ctype(line) == 1){
            //inst_type = 'C';
            //printf("%c  %s\n", inst_type, line);
            //printf("%s\n", line);
            char tmp_line[MAX_LINE_LENGTH] = "";
            strcpy(tmp_line, line);
            parse_C_instruction(tmp_line, &instr.instr.c);
            
            if (instr.instr.c.dest == -1)
                    exit_program(EXIT_INVALID_C_DEST, line_num, line);
            
            if (instr.instr.c.comp == -1)
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            
            if (instr.instr.c.jump == -1)
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
                
    
            
                    printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);
            
            instr.sometype = C_type;
                     
        }
         
        instructions[instr_num++] = instr;
    }
    return instr_num;
}
