#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _tree_{
    char *operacao;
    int *valores;
    struct _tree_ *pai;
    struct _tree_ *esq;
    struct _tree_ *dir;
} tree;

tree *criar(char *operacao, int *valores){
    tree *novo = (tree *) malloc(sizeof(tree));
    novo->operacao = operacao;
    novo->valores = valores;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;

    return novo;
}

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
      if(a->operacao != NULL)
        printf("%c \n", (char) a->operacao);
      else
        printf("%d \n", (int) a->valores);

      if(a->dir != NULL){
        printf("Direita\n");
        printaTree(a->dir);
      }
    }
}

/// CALCULADORA SINTÁTICA

/*
Casamento = chama getToken e pega o próximo
Além de verificar a sintaxe ja faz o cálculo
*/

//Implementar uma calculadora para aritmética de inteiros simples segundo a EBNF



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
  char *operacao = NULL;
  temp = termo();
  while(token == '+' || token == '-'){
    switch(token){
      case '+': match('+');
        operacao = malloc(1);
        operacao = (char *) '+';
        novatemp = criar(operacao, NULL);
        break;
      case '-': match('-');
        operacao = malloc(1);
        operacao = (char *) '-';
        novatemp = criar(operacao, NULL);
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
  int valores;

  if (token == '('){
    match ('(');
    temp = expressao();
    match(')');
  }else if (isdigit(token)){
    ungetc(token,stdin);
    scanf("%d", &valores);
    temp = criar(NULL, (int*) valores);
    token = getchar();
  }else
    error();
  
  return temp;
}

tree *termo(void){
  tree *novatemp, *temp;
  char *operacao = NULL;
  temp = factorTree();

  while(token == '*' || token == '/' || token == '%'){
    switch(token){
      case '*': match('*');
        operacao = malloc(1);
        operacao = (char *) '*';
        novatemp = criar(operacao, NULL);
        break;
      case '/': match('/');
        operacao = malloc(1);
        operacao = (char *) '/';
        novatemp = criar(operacao, NULL);
        break;
      case '%': match('%');
        operacao = malloc(1);
        operacao = (char *) '%';
        novatemp = criar(operacao, NULL);
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
  
  if(a->valores != NULL)
    resultado = (int) a->valores;
  else{
    if(a->dir->operacao != NULL)
      aux = sum(a->dir);
    else
      aux = (int) a->dir->valores;
    switch((char) a->operacao){
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