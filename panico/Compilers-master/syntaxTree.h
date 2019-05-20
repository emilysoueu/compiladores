#ifndef SYNTAX_TREE_h_
#define SYNTAX_TREE_h_

#define TRUE 1
#define FALSE 0

typedef enum { NUMBER, OPERATOR } typeNode;

typedef struct _syntaxtree_{
	struct _syntaxtree_ *left;
	struct _syntaxtree_ *right;
	int key;
	typeNode type;
} syntaxTree;

	#ifndef syntaxTree_c_

		syntaxTree *createNode(int data, typeNode type);
		void leftChild(syntaxTree *node, syntaxTree *newnode);
		void rightChild(syntaxTree *node, syntaxTree *newnode);
		void treePreOrder(syntaxTree *root);
		int resultSyntaxTree(syntaxTree *node);

	#else

		extern syntaxTree *createNode(int data, typeNode type);
		extern void leftChild(syntaxTree *node, syntaxTree *newnode);
		extern void rightChild(syntaxTree *node, syntaxTree *newnode);
		extern void treePreOrder(syntaxTree *root);
		extern int resultSyntaxTree(syntaxTree *node);

	#endif
#endif