#include <stdio.h>
#include <stdlib.h>
#include "tree.c"
#include <ctype.h>

/* EBNF
Casamaneto = chama getToken e pega o próximo
Além de verificar a sintaxe ja faz o cálculo
*/

//Implementar uma calculadora para aritmética de inteiros simples segundo a EBNF

char token;

int exp(void); //Realiza a operação da calculadora
int term(void);
int fator(void);
Arvore *expTree(void);
Arvore *termTree(void);
Arvore *fatorTree(void);
int soma_tree(Arvore *a);

void error(void){
	printf("Error\n");
	exit(1);
}

void match (char tokenEsperado){
	if (token == tokenEsperado)
		token = getchar();
	else
		error();
}

int main(void) { //calculadora com árvore sintática
	Arvore *resultado;
	token = getchar(); //Carga de marca com primeiro caractere com verificação a frente

	resultado = expTree();

	if (token == '\n'){ //teste final de linha
    printf("Arvore gerada:\n");
    print_arvore(resultado);
    printf("Resultado: %d", soma_tree(resultado));
	}else
		error();//Caracteres indevidos na linha
	
  return 0;
}

/*int main(void) { //calculadora normal
	int resultado;
	token = getchar(); //Carga de marca com primeiro caractere com verificação a frente

	resultado = exp();

	if (token == '\n'){ //teste final de linha
    printf("Resultado: %d", resultado);
	}else
		error();//Caracteres indevidos na linha
	
  return 0;
}*/

int exp(void){
	int temp = term();

	while((token == '+')||(token == '-') ||(token == '/') ||(token =='%')){
		switch(token){
			case '+': match('+');
					temp += term();
					break;
			case '-': match('-');
					temp -= term();
					break;
		}
	}
	
  return temp;
}

int factor(void){
	int temp;

	if (token == '('){
		match ('(');
		temp = exp();
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

	while(token == '*' || token == '/' || token == '%'){
		switch(token){
      case '*': match('*');
        temp *= factor();
        break;
      case '/': match('/');
        temp /= term();
        break;
      case '%': match('%');
        temp = temp%term();
        break;
    }
	}
	return temp;
}

Arvore *expTree(void){
  Arvore *novatemp, *temp;
  char *op = NULL;
  temp = termTree();
  while(token == '+' || token == '-'){
    switch(token){
			case '+': match('+');
        op = malloc(1);
        op = (char *) '+';
        novatemp = criar(op, NULL);
        break;
			case '-': match('-');
        op = malloc(1);
        op = (char *) '-';
        novatemp = criar(op, NULL);
        break;
		}
    inserirEsq(novatemp, temp);
    inserirDir(novatemp, termTree());
    temp = novatemp;
  }

  return temp;
}

Arvore *factorTree(void){
	Arvore *temp = NULL;
  int val;

	if (token == '('){
		match ('(');
		temp = expTree();
		match(')');
	}else if (isdigit(token)){
    ungetc(token,stdin);
		scanf("%d", &val);
    temp = criar(NULL, (int *) val);
		token = getchar();
	}else
		error();
  
  return temp;
}

Arvore *termTree(void){
  Arvore *novatemp, *temp;
  char *op = NULL;
	temp = factorTree();

	while(token == '*' || token == '/' || token == '%'){
		switch(token){
      case '*': match('*');
        op = malloc(1);
        op = (char *) '*';
        novatemp = criar(op, NULL);
        break;
      case '/': match('/');
        op = malloc(1);
        op = (char *) '/';
        novatemp = criar(op, NULL);
        break;
      case '%': match('%');
        op = malloc(1);
        op = (char *) '%';
        novatemp = criar(op, NULL);
        break;
    }
    inserirEsq(novatemp, temp);
    inserirDir(novatemp, termTree());
    temp = novatemp;
	}

	return temp;
}

int soma_tree(Arvore *a){
  int resultado, aux;

  if(a->esq != NULL)
    resultado = soma_tree(a->esq);
  
  if(a->val != NULL)
    resultado = (int) a->val;
  else{
    if(a->dir->op != NULL)
      aux = soma_tree(a->dir);
    else
      aux = (int) a->dir->val;
    switch((char) a->op){
      case '+':
        resultado+= aux;
        break;
      case '-':
        resultado-= aux;
        break;
      case '/':
        resultado = aux / resultado;
        break;
      case '%':
        resultado = aux % resultado;
        break;
      case '*':
        resultado = aux * resultado;
        break;        
    }
  }
  return resultado;
}