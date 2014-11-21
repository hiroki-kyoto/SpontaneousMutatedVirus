#include "stdio.h"
#include "windows.h"

#define MAX_LOOP 10000

int main(int argc, const char** argv)
{
	/*** THE VIRUS LOGIC PART ***/
	//GENE_MARK
	int a = 0;

	printf("GENE PRINT:%d\n", a);
	/*** THE VIRUS LOGIC PART ***/


	// FILE NAME
	char file_name[30] = "test";

	// MAKE A COPY OF HERSELF
	FILE* source = fopen("test.c", "r");
	FILE* descendant = fopen("descendant.c", "w+");
	
	printf("SOURCE FILE OPEN RESULT IS : %d \n", (int)source);
	printf("DESCENDANT FILE CREATED: %d \n", (int)descendant);
	
	if(descendant==NULL)
	{
		printf("ERROR ON CREATING DESCENDANT.\n");
		return -1;
	}
	char buff[100] = {0};
	// REPLACE GENE MARK PROGRAM
	char letter = 0;
	
	// GENE LINE
	int idx = 0;
	int loop = 0;
	
	int buff_idx = 0;
	
	while(!feof(source))
	{
		// ALARM
		if(loop>MAX_LOOP)
			break;
		
		loop ++;
		
		fread(&letter, sizeof(char), 1, source);
		
		buff[buff_idx] = letter;
		buff_idx ++;
		
		if(letter=='\n')
		{
			if(idx==9)
			{
				// TRANSFORM GENE
				memset(buff, 0, 100);
				buff_idx = 0;
				strcat(buff, "int a = 1;\n");
			}
			fwrite(buff, sizeof(char), strlen(buff), descendant);
			// CLEAR BUFFER
			memset(buff, 0, 100);
			buff_idx = 0;
			idx ++;
		}
	}
	
	// DEAL WITH LEFT LETTERS IN BUFFER
	if(strlen(buff)>0)
	{
		strcat(buff, "\n");
		fwrite(buff, sizeof(char), strlen(buff)+1, descendant);
	}
	
	// CLOSE ALL FILES
	fclose(source);
	fclose(descendant);
	
	// until the descendant file is written over
	
	/*** COMPILE HERSELF ***/
	char* source_file = "descendant.c";
	char* dest_file = "descendant.exe";
	char command[100] = {0}; 
	strcat(command, "gcc -o ");
	strcat(command, dest_file);
	strcat(command, " ");
	strcat(command, source_file);
	// COMPILATION
	system(command);
	/***********************/
	
	
	printf("COPYING MYSELF DONE.\n");
	
	printf("WAITING FOR NEXT INSTRUCTION...\n");
	char cmd = getchar();
	if(cmd=='Y')
	{
		printf("BEGIN EXECUTE THE COPYFILE EXECUTION...\n");
//GENE_MARK	
		system("descendant.exe");
		printf("EXECUTION PROCESS IS ACTIVATED, TASK DONE. EXIT SYSTEM.");
	}
	else
		printf("YOU CHOOSE TO EXIT SYSTEM. BYE!");

	return 0;
}
