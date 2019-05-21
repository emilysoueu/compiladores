#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.c"

char token;

tree *expressao(void);
tree *termo(void);
tree *fatorNew(void);
int sum(tree *a);

char filhoEsq(tree *a, tree *b){
    if(a != NULL && b != NULL){
      if(a->esq != NULL)
        return filhoEsq(a->esq, b);
      else{
        a->esq = b;
        b->pai = a;
        return 1;
      }
    }
    return 0;
}

char filhoDir(tree *a, tree *b){
    if(a != NULL && b != NULL){
      if(a->dir != NULL)
        return filhoDir(a->dir, b);
      else{
        a->dir = b;
        b->pai = a;
        return 1;
      }
    }
    return 0;
}

void printaTree(tree *a){
    if(a != NULL){
      if(a->esq != NULL){
        printf("Esquerda\n");
        printaTree(a->esq);
      }
      
      printf("Raiz\n");
      if(a->op != NULL)
        printf("%c \n", (char) a->op);
      else
        printf("%d \n", (int) a->val);

      if(a->dir != NULL){
        printf("Direita\n");
        printaTree(a->dir);
      }
    }
}


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
  tree *resultado;
  token = getchar(); //Carga de marca com primeiro caractere com verificação a frente

  resultado = expressao();

  if (token == '\n'){ //teste final de linha
    printf("tree gerada:\n");
    printaTree(resultado);
    printf("Resultado: %d", sum(resultado));
  }else
    error();//Caracteres indevidos na linha
  
  return 0;
}


tree *expressao(void){
  tree *novatemp, *temp;
  char *op = NULL;
  temp = termo();
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
    filhoEsq(novatemp, temp);
    filhoDir(novatemp, termo());
    temp = novatemp;
  }

  return temp;
}

tree *factorTree(void){
  tree *temp = NULL;
  int val;

  if (token == '('){
    match ('(');
    temp = expressao();
    match(')');
  }else if (isdigit(token)){
    ungetc(token,stdin);
    scanf("%d", &val);
    temp = criar(NULL, (int*) val);
    token = getchar();
  }else
    error();
  
  return temp;
}

tree *termo(void){
  tree *novatemp, *temp;
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
    filhoEsq(novatemp, temp);
    filhoDir(novatemp, termo());
    temp = novatemp;
  }

  return temp;
}

int sum(tree *a){
  int resultado, aux;

  if(a->esq != NULL)
    resultado = sum(a->esq);
  
  if(a->val != NULL)
    resultado = (int) a->val;
  else{
    if(a->dir->op != NULL)
      aux = sum(a->dir);
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