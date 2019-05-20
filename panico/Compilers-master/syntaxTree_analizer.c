#include <stdio.h>
#include <stdlib.h>
#include "syntaxTree.h"

#define TRUE 1
#define FALSE 0

int digit(char token);
void error();
void match(char expectedToken);
void treePreOrder(syntaxTree *root);
syntaxTree *expTree();
syntaxTree *termTree();
syntaxTree *factorTree();

char token;

int main(){
  syntaxTree *result;
  token = getchar();

  result = expTree();

  treePreOrder(result);

  if(token=='\n')
	printf("Result = %d\n", resultSyntaxTree(result));
  else
	error();

  return 0;
}


syntaxTree *expTree(){
  syntaxTree *temp = termTree();
  syntaxTree *newTemp;	

  while(token == '+' || token == '-'){
	newTemp = createNode((int) token, OPERATOR);
	match(token);
	leftChild(newTemp, temp);
	rightChild(newTemp, termTree());
	temp = newTemp;
  }
	
  return temp;
}


syntaxTree *termTree(){
  syntaxTree *temp = factorTree();
  syntaxTree *newTemp;

  while(token == '*' || token == '/' || token == '%'){
	newTemp = createNode((int) token, OPERATOR);
	match(token);
	leftChild(newTemp, temp);
	rightChild(newTemp, factorTree());
	temp = newTemp;
  }

  return temp;
}


syntaxTree *factorTree(){
  syntaxTree *temp = NULL;
  int auxTemp;

  if(token == '('){
	match('(');
	temp = expTree();
	match(')');
  } else if(digit(token)){
	ungetc(token, stdin);
	scanf("%d", &auxTemp);
	temp = createNode(auxTemp, NUMBER);
	token = getchar();
  } else {
	error();
  }

  return temp;
}


void error(){
  fprintf(stderr, "Error\n");
  exit(1);
}


void match(char expectedToken){
  if(token == expectedToken)
	token = getchar();
  else
	error();
}


int digit(char token){
  if(token >= '0' && token <= '9')
	return TRUE;
  return FALSE;
}