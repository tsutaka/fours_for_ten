#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Formula List Struct*/
struct list{
	char str[16];
	double answer;
	struct list *next;
};

/*Calculater*/
int calculater(char *input){
	double val[4];
	char sig[3];
	int cnt;
	
	/*get val*/
	val[0] = double(input[0] - '0');
	val[1] = double(input[2] - '0');
	val[2] = double(input[4] - '0');
	val[3] = double(input[6] - '0');
	/*get sig*/
	sig[0] = input[1];
	sig[1] = input[3];
	sig[2] = input[5];
	
	/*Multiplication and division*/
	cnt = 0;		
	while(cnt <= 2){
		if(sig[cnt] == '*'){						//For multiplication
			val[cnt + 1] = val[cnt] * val[cnt + 1];
			sig[cnt] = ' ';				//If sig is blank, num before blank is invalid.
		}
		else if(sig[cnt] == '/'){					//For division
			val[cnt + 1] = val[cnt] / val[cnt + 1];
			sig[cnt] = ' ';				//If sig is blank, num before blank is invalid.
		}
		//printf("debug:%2.1f%c%2.1f%c%2.1f%c%2.1f\n", val[0], sig[0], val[1], sig[1], val[2], sig[2], val[3]);
		cnt++;
	}
	
	/*Addition and subtraction*/
	cnt = 0;		
	while(cnt < 3){
		if(sig[cnt] == '+'){						//For add
			if(cnt == 0 && sig[cnt + 1] == ' ' && sig[cnt + 2] == ' '){
				val[cnt + 3] = val[cnt] + val[cnt + 3];
			}
			else if(cnt <= 1 && sig[cnt + 1] == ' '){
				val[cnt + 2] = val[cnt] + val[cnt + 2];
			}
			else{
				val[cnt + 1] = val[cnt] + val[cnt + 1];
			}
		}
		else if(sig[cnt] == '-'){					//For sub
			if(cnt == 0 && sig[cnt + 1] == ' ' && sig[cnt + 2] == ' '){
				val[cnt + 3] = val[cnt] - val[cnt + 3];
			}
			else if(cnt <= 1 && sig[cnt + 1] == ' '){
				val[cnt + 2] = val[cnt] - val[cnt + 2];
			}
			else{
				val[cnt + 1] = val[cnt] - val[cnt + 1];
			}
		}
		//printf("debug:%2.1f%c%2.1f%c%2.1f%c%2.1f\n", val[0], sig[0], val[1], sig[1], val[2], sig[2], val[3]);
		cnt++;
	}
	return val[3];
}

/*Generate list of formula*/
struct list *generator(char input[16]){
	struct list *head = NULL;
	struct list *now;
	int cnt = 0;
	char str[16];
	int counter[3];
	
	/*Input check*/
	while(cnt < 4){
		if(input[cnt] < '0' || input[cnt] > '9'){
			printf("Not numerics!\n");
			return NULL;
		}
		cnt++;
	}
	for(counter[0] = 0; counter[0] < 4; counter[0]++){
		for(counter[1] = 0; counter[1] < 4; counter[1]++){
			for(counter[2] = 0; counter[2] < 4; counter[2]++){
				str[0] = input[0];
				str[2] = input[1];
				str[4] = input[2];
				str[6] = input[3];
				str[7] = '\0';
				for(cnt = 0; cnt < 3; cnt++){
					switch(counter[cnt]){
						case 0: str[cnt*2+1] = '+'; break; 
						case 1: str[cnt*2+1] = '-'; break; 
						case 2: str[cnt*2+1] = '*'; break; 
						case 3: str[cnt*2+1] = '/'; break; 
					}
				}
				now = (struct list *)malloc(sizeof(list));
				strncpy(now->str, str, 15);
				now->answer = calculater(now->str);
				now->next = head;
				head = now;
			}
		}
	}
	return head;
}

/*Show list of formula*/
int showList(struct list *inputList){
	int cnt = 0;
	
	printf("*** List(%c%c%c%c) ***\n", 
		inputList->str[0], inputList->str[2], 
		inputList->str[4], inputList->str[6]);
		
	while(inputList != NULL){
		if(inputList->answer >= 9.999 && inputList->answer <= 10.001 ){
			printf("%d:%s=%2.0f\n", cnt, inputList->str, inputList->answer);
			cnt++;
		}
		inputList = inputList->next;
	}

	return cnt;
}

/*clear lsit of formula*/
int clearList(struct list *inputList){
	struct list *delPtr;
	int cnt = 0;
	
	while(inputList != NULL){
		delPtr = inputList;
		inputList = inputList->next;
		free(delPtr);
		cnt++;
	}
	return cnt;
}

int main(){
	char str[16];		//For input string
	struct list *head;	//Top of list address
	
	while(true){
		printf("\n***<<< 4 numbers for results in 10 >>>***\n");
		printf("input 4 numbers (xxxx)>>");
		
		fgets(str, 5, stdin);
		str[strlen(str)] = '\0';	//Replace \n to \0
		fflush(stdin);				//Clear stdin stream
		
		head = generator(str);					//Generate list of formula
		printf("sum:%d\n", showList(head));		//Show list of formula
		clearList(head);						//delete list of formula
	}
	
	return 0;
}