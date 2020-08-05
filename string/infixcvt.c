#include "util.h"
#define MAX_SIZE 256

typedef enum {plus, minus, times, divide, modulos, lpare, rpare, operand } token;
int isp[] =  {  10,    10,    20,     20,      20,     0,    10 }; //In-stack precedence
int icp[] =  {  10,    10,    20,     20,      20,    30,    10 }; //Incoming precedence
char _token[] = {'+',  '-',   '*',    '/',     '%'};
token stack[MAX_SIZE];
int top = -1;

void convert(const char *, char *);
token get_token(char);
char get_char(token);
void push(token);
token pop(void);

int main(void){
	char infix[MAX_SIZE], postfix[MAX_SIZE];
	printf("Please enter a infix expression [operand:a-z] [operator:+-*/%%]\n");
	scanf("%s", infix);
	convert(infix, postfix);
	printf("%s\n", postfix);
	return 0;
}

void convert(const char *infix, char *postfix){
	
	for(; *infix; infix++){
		token e = get_token(*infix);
		
		if(e == operand){
			*postfix++ = *infix;
		}else if(e == rpare){
			while(stack[top] != lpare){
				*postfix++ = get_char(pop());
			}
			pop();
		}else{
			while(top >= 0 && isp[stack[top]] >= icp[e]){
				*postfix++ = get_char(pop());
			}
			push(e);
		}
	}
	
	while(top >= 0){
		*postfix++ = get_char(pop());
	}
	*postfix = 0;
}

token get_token(char c){
	switch(c){
		case '+': return plus;
		case '-': return minus;
		case '*': return times;
		case '/': return divide;
		case '%': return modulos;
		case '(': return lpare;
		case ')': return rpare;
		default: return operand;
	}
}

char get_char(token e){
	return _token[e];
}

void push(token e){
	if(top >= MAX_SIZE - 1)
		exit(1);
	stack[++top] = e;
}

token pop(void){
	if(top <= -1)
		exit(1);
	return stack[top--];
}