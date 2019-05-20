#include<stdlib.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0

typedef enum { NUMBER, OPERATOR } typeNode;

typedef struct _syntaxtree_{
	struct _syntaxtree_ *left;
	struct _syntaxtree_ *right;
	int key;
	typeNode type;
} syntaxTree;

syntaxTree *createNode(int data, typeNode type){
	syntaxTree *newnode = (syntaxTree*)malloc(sizeof(syntaxTree));

	if (newnode != NULL){

		newnode->left = NULL;
		newnode->right = NULL;
		newnode->key = data;
		newnode->type = type;

		return newnode;
	}

	return NULL;
}

void leftChild(syntaxTree *node, syntaxTree *newnode){
	if (node != NULL){
		if (newnode != NULL){
			node->left = newnode;
		}
	}
}

void rightChild(syntaxTree *node, syntaxTree *newnode){
	if (node != NULL){
		if (newnode != NULL){
			node->right = newnode;
		}
	}
}

void treePreOrder(syntaxTree *root){
	if (root != NULL){
		if ((char)root->key == '+' || (char)root->key == '-' || (char)root->key == '*' || (char)root->key == '/' || (char)root->key == '%'){
			printf("%c\n", root->key);	
		} else {
			printf("%d\n", root->key);
		}
		treePreOrder(root->left);
		treePreOrder(root->right);
	}
}

int resultSyntaxTree(syntaxTree *node){
	if (node != NULL){
		if (node->type == NUMBER){
			return node->key;
		} else {
			switch((char) node->key){
				case '+':
				  return resultSyntaxTree(node->left) + resultSyntaxTree(node->right);
				case '-':
				  return resultSyntaxTree(node->left) - resultSyntaxTree(node->right);
				case '*':
				  return resultSyntaxTree(node->left) * resultSyntaxTree(node->right);
				case '/':
				  return resultSyntaxTree(node->left) / resultSyntaxTree(node->right);
				case '%':
				  return resultSyntaxTree(node->left) % resultSyntaxTree(node->right);
				}
		}
	}
}