#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 500

FILE *text_line;
char textString[MAXLEN];
char resultString[MAXLEN];//temporary string holder for decode function

void encode(char *strText){

	int count = 1;
	int i = 0;
	int index = 0;//index for incrementing post strText after checking how many char repeats
	int len = strlen(strText);
	
	while(i<len){
		if(strText[i] ==  strText[i+1]){
			strText[index++] = strText[i]; 
			while(strText[i] == strText[++i]){
				count++;
			}
			char pointer = count + '0';//turn into a digit
			strText[index++] = pointer;
			count = 1;
		}else{
			strText[index++] = strText[i++];
		}
		
		
	}
	strText[index] = '\0';//End the string

	

}

void decode(char* strText){

	int i;
	int len = strlen(strText);
	int count = 0;
	int index = 0;
	for(i = 0; i < len;){
		char preChar = strText[i++];//store character in char and check if after is digit
		if(strText[i] <= '9' || strText[i] >= '0'){
			count = count * 10 + strText[i] - '0';//if its digit then calculate count
			i++;
		}
	
		while(count>0){//append character until count is 0
			resultString[index++] = preChar;
			count--;
		}
	}
	int tempLen = strlen(resultString);//gather len of the temporary string
	strncpy(strText,resultString,tempLen);//copy temporary string into strText to return
}

int main(int argc, char *argv[]){
	
	int i;
	char flag[10] = "";							//initializing flag 
	int length;
	char digitString[] = "123456789";
	char nonLetters[] = "BDEFHIJKLMNOPQRSUVWXYZ";				//array of letters that should not be in the text file	
	if((text_line = fopen("input.txt", "r"))==NULL){			//if text file does not exist, exit
		printf("Error: No input file specified!");
		exit(1);
	}else{
		text_line = fopen("input.txt","r");
	}	
	if(fgets(textString,MAXLEN,text_line)==NULL){				//if textfile cannot be read then exit
		printf("Error: file not found or cannot be read");
		exit(2);
	}else{
		fgets(textString,MAXLEN,text_line);
	}
	
	length = strlen(textString);
	char *ptr = strpbrk(textString,nonLetters);				//split up character and traverse and check if each character matches an array of letters
	if(ptr != NULL){							//if there are non RLE characters exit
		printf("Error: Invalid format");
	 	exit(3);
	}else{
		for(i=0;i<length-1;i++){					//check for formatting of text string
			if(isspace(textString[i]) || islower(textString[i]) || ispunct(textString[i])){
				printf("Error: Invalid format");
				exit(3);
			}
		}
	
	}
	char *digit_ptr = strpbrk(textString,digitString);
	if(digit_ptr != NULL){
		strncpy(flag,"d",1);
	}else{
		strncpy(flag,"e",1);
	}
	fclose(text_line); 							//close file to prevent overflow
	if(flag[0] == '\0'){							//if flag is not either e or d exit
		printf("Invalid Usage, expected RLE input.txt [e|d]");
		exit(4);
	}
	if(flag[0] == 'e'){							//if flag is e then encode the string
		encode(textString);
		printf("%s\n",textString);
		exit(5);
	}
	if(flag[0] == 'd'){							//if flag is d then encode the string
		decode(textString);
		printf("%s\n", textString);
		exit(5);
	}
}
