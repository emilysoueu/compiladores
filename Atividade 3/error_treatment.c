#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char token;

int expo(void);
int term(void);
int fator(void);

void error(void){
	fprintf(stderr,"Error\n");
	//exit(1);
}

void match (char tokenEsperado){
	if (token == tokenEsperado)
		token = getchar();
	else
		//error();
    printf("%c é",token);
    while(!isdigit(token)) 
     
    token = getchar();

}

int main(void) {
	int result;
	token = getchar(); 
	result = expo();

	if (token == '\n') 
		printf("Resultado = %d\n", result);
	else
		error();
		//return 0;

}

int expo(void){
	int temp = term();

	while((token == '+')||(token == '-') ||(token == '/') ||(token == '%')){
		switch(token){
			case '+': match('+');
					temp += term();
					break;
			case '-': match('-');
					temp -= term();
					break;
      case '/': match('/');
          temp /= term();
          break;
      case '%': match('%');
          temp = temp%term();
          break;

		}
		//return temp;
	}
  return temp;
}

int factor(void){
	int temp;

	if (token == '('){
		match ('(');
		temp = expo();
		match(')');
	}else if (isdigit(token)){
		ungetc(token,stdin);
		scanf("%d", &temp);
		token = getchar();
	}else
		error();
    return temp;

}

int term(void){
	int temp = factor();

	while(token == '*'){
		match('*');
		temp *= factor();
	}
	return temp;
}