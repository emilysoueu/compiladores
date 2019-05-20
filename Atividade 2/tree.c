#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Arvore *criar(char *op, int *val){
    Arvore *novo = (Arvore *) malloc(sizeof(Arvore));
    novo->op = op;
    novo->val = val;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;

    return novo;
}

char inserirEsq(Arvore *a, Arvore *b){
    if(a != NULL && b != NULL){
      if(a->esq != NULL)
        return inserirEsq(a->esq, b);
      else{
        a->esq = b;
        b->pai = a;
        return 1;
      }
    }
    return 0;
}

char inserirDir(Arvore *a, Arvore *b){
    if(a != NULL && b != NULL){
      if(a->dir != NULL)
        return inserirDir(a->dir, b);
      else{
        a->dir = b;
        b->pai = a;
        return 1;
      }
    }
    return 0;
}

void print_arvore(Arvore *a){
    if(a != NULL){
      if(a->esq != NULL){
        printf("Esquerda\n");
        print_arvore(a->esq);
      }
      
      printf("Raiz\n");
      if(a->op != NULL)
        printf("%c \n", (char) a->op);
      else
        printf("%d \n", (int) a->val);

      if(a->dir != NULL){
        printf("Direita\n");
        print_arvore(a->dir);
      }
    }
}