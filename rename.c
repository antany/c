#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]){
	char *fileName = argv[2];
	char *fileCounter = argv[1];
	int i=0;
	char c;
	unsigned long length;
	int isAlph=1;
	int isExtn=0;

	length = strlen(fileName);
	for(i=0;i<=length;i++){
		c = fileName[i];
		if(c=='.'){	
			if(isAlph){
				printf("\b");
			}
			isExtn=1;
		}
		if((c>='a' && c<='z') || (c>='A' && c<='Z')||isExtn){
			if(isAlph && !isExtn){
				if(c>='Z' && c!=' '){
					c=c-32;
				}
			}				
				printf("%c",c);
				isAlph=0;
		}else{
			if(!isAlph)
			printf(" ");
			isAlph=1;
		}
	}

	return 0;
}
