#include<stdio.h>
#include<string.h>

int binarySearch(char *keywords, char find);
int isEmpty();
char peek();
void pop();
void push(char c);
void printTab(int noOfTabs);

char expressions[10000];
int currTop=-1;

char outByte[26000];
int currCount = 0;


int main(int argc, char **argv){
	
	//check arguments are fine;
	if(argc != 2){
		printf ("Incorrect arguments \n");
		return 1;
	}
	
	char *keywords = ",[]{}";
	
	
	printf("processing...%s\n\n\n",argv[1]);
	
	char chBuff[25000];
	
	char *jsonFileName=argv[1];
	int bytesRead = 0;

	char outputFileName[1000];
	
	strcat(outputFileName,argv[1]);
	strcat(outputFileName,"_formatted");
	
	
	
	FILE *jsonFile,*outputFile;
	jsonFile = fopen(jsonFileName,"r");
	outputFile = fopen(outputFileName,"w+");
	
	int popIndicator=0;
	int prePopIndicator=0;

	
	while((bytesRead = fread(chBuff,1,sizeof(chBuff),jsonFile))>0){
			int i=0;
			for(i=0;i<bytesRead;i++){
				int k =binarySearch(keywords,chBuff[i]);
				
				if(popIndicator){
					outByte[currCount]='\n';
					currCount++;
					if(!isEmpty()){
						printTab(currTop);
					}
					popIndicator = 0;
					prePopIndicator =1;
				}
				
				
				
				if(k>=0){
					
					char expression = keywords[k];
					char preExpression;
					if(k!=0){
						preExpression = keywords[k-1];
					}
					
					if(expression==','){
						if(prePopIndicator){
							currCount = currCount - currTop-1;
							prePopIndicator = 0;
						}
					}else if(isEmpty() || peek()==expression){
						if(!isEmpty()){
							outByte[currCount]='\n';
							currCount++;
						}
						push(expression);
						printTab(currTop);
					}else if(peek()!=preExpression){
						outByte[currCount] = '\n';
						currCount++;
						push(expression);
						printTab(currTop);
					}else{
						pop();
						popIndicator = 1;
					}
				}
				
				outByte[currCount]=chBuff[i];
				currCount++;
				if(currCount>=25000){
					fwrite(outByte,1,currCount,outputFile);
					currCount =0;
				}
			}
			
	}
	

	
	fwrite(outByte,1,currCount,outputFile);

	return 0;
}

void printTab(int noOfTabs){
	int i=0;
	for(i=0;i<noOfTabs;i++){
		outByte[currCount] = '\t';
		currCount++;
	}
}

int binarySearch(char *keywords, char find){
	
	int first = 0;
	int last = sizeof(keywords);
	int middle = (first+last)/2;
	
	while(first<=last){
		
		if(keywords[middle]<find){
			first = middle+1;
		}else if(keywords[middle]==find){
			return middle;
		}else{
			last = middle -1;
		}
		middle = (first+last)/2;
	}
	
	return -1;
}

int isEmpty(){
		if(currTop!=-1){
			return 0;
		}else{
			return 1;
		}	
}

char peek(){
	return expressions[currTop];
}

void pop(){
	currTop = currTop -1;
}

void push(char c){
	currTop = currTop + 1;
	expressions[currTop] = c;
}
