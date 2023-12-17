#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int isKeyword(char * word){
	const char *keywords[34] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
                                "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile", "while", "printf", "scanf"};
	for(int i =0; i < 34; i++){
		if(strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

void main(){
	FILE *inputfile, *outputfile;
	inputfile = fopen("inp.txt", "r");
	outputfile = fopen("output.txt", "w+");
	if(inputfile == NULL || outputfile == NULL ){
		printf("Error in opening files!");
		return;
	}

	int lineNum = 0, ch;
	char buffer[40];
	fprintf(outputfile, "LineNo\tLexeme\tToken\n");

	while((ch = fgetc(inputfile)) != EOF){
		if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
			fprintf(outputfile, "%d\t%c\tArithematic Operator\n", lineNum, ch);

		else if(ch == '@' || ch == ']' || ch == '[' || ch == '$' || ch == '&')
			fprintf(outputfile, "%d\t%c\tSpecial Symbol\n", lineNum, ch);

		else if(ch == '>' || ch == '<' || ch == '='){
			int nextChar = fgetc(inputfile);
			if(nextChar == '=')
				fprintf(outputfile, "%d\t%c%c\tRelational Operator\n", lineNum, ch, nextChar);
			else{
				fprintf(outputfile, "%d\t%c\tRelational Operator\n", lineNum, ch);
				fseek(inputfile, -1, SEEK_CUR);
			}
		}

		else if(isalnum(ch)){
			int index = 0;
			buffer[index++] = ch;

			while((ch = fgetc(inputfile)) != EOF && isalnum(ch))
				buffer[index++] = ch;
			buffer[index] = '\0';

			if(isKeyword(buffer))
				fprintf(outputfile, "%d\t%s\tKeyword\n", lineNum, buffer);
			else
				fprintf(outputfile, "%d\t%s\tIdentifier\n", lineNum, buffer);
			
			fseek(inputfile, -1, SEEK_CUR);
		}
		else if(ch == '\n') lineNum++;
	}
	fclose(inputfile);
	fclose(outputfile);
}