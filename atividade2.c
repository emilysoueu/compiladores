
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char token;
node* exp(void);
node* term(void);
node* fator(void);


typedef struct _node_{
	//int valor;
	char op;
	struct _node_* filho_esquerdo;
	struct _node_* filho_direito;
}node;


node* criar(char dado){
	node* novo = (node*)malloc(sizeof(node));
	if (novo == NULL) return NULL;

	/**
	if (isdigit(dado) == 0){ //se for 0 não é número
		novo->op = dado;
		//novo->valor = 0;// apenas para teste;
		novo->filho_esquerdo = NULL;
		novo->filho_direito = NULL;
	}else{
		//novo->op = 0;
		novo->valor = dado;// apenas para teste;
		novo->filho_esquerdo = NULL;
		novo->filho_direito = NULL;]

	}
	*/
	novo->op = dado;
	novo->filho_esquerdo = NULL;
	novo->filho_direito = NULL;

	return novo;


}

node* inserir(char dado, node* root){
	node* temp = criar(dado);
	node* lado_esq;
	node* lado_dir;

	if ( root == NULL){
		root = temp;
	}else if (root != NULL && root-> filho_esquerdo == NULL){
		root->filho_esquerdo = inserir(dado,root->filho_esquerdo);
	}else if (root != NULL && root ->filho_direito == NULL){
		root->filho_direito = inserir(dado,root->filho_direito);
	}
	return root;

}

void emOrde(node* raiz){
    if (raiz == NULL) return;

    emOrde(raiz->filho_esquerdo);   
    printf("%c ",raiz->op);
    emOrde(raiz->filho_direito);
}




void error(void){
	printf(stderr,"Error\n");
	exit(1);
}

// funcão casamento
void match (char tokenEsperado){
	//char token;
	if (token == tokenEsperado)
		token = getchar();
	else
		error();
}

node* term(void);



node* exp(void){
	//char token;
	node* temp = term();     // provavelmente problemas com os tipos ja que ta node mas acho que deveria ser char
	node* novaTemp;

	//temp = term();

	while((token == '+')||(token == '-') ||(token == '/') ||(token =='%')){
	    switch(token){
			case '+': {
				match('+');
                novaTemp = inserir('+',novaTemp);
                //printf("%c\n",novaTemp->op );
                temp =  inserir('1',novaTemp); // inserido na força bruta
                //printf("%d\n",novaTemp->filho_esquerdo->op );
                term() =  inserir('5',novaTemp); // inserido na força bruta
                //printf("%d\n",term->filho_direito->op );
				temp  = novaTemp; 
				printf("\n\n");

				printf("Árvore Inserida:\n");
				emOrde(temp);
				printf("\n");
				}			

			break;

        }
	}
	return temp;

}

node* factor(void){
	//char token;
	node* temp;

	if (token == '('){
		match ('(');
		temp = exp();
		match(')');
	}else if (isdigit(token)){
		ungetc(token,stdin);
		scanf("%d",temp);
		token = getchar();
	}else
		error();

    return temp;

}


node* term(void){
	//char token;
	node* temp = factor();

	while((token == '+')||(token == '-') ||(token == '/') ||(token =='%')){
	    switch(token){
	    	case '+':{
	    		match('+');
	    		temp->op += factor();

	    	}break;
	    	// case '*':{
	    		// match('*');
				// temp->op *= factor();
// 
	    	// }break;

		//}
	}
	return temp;
}

int main(void) {
	//char token;
	node* resultado;


	printf("Insira a expresao:\n");
	token = getchar();  
	
	resultado = exp(); 

	printf("\n\n");
	printf("\nResultado main  = %d\n", resultado);
	printf("\n\n");

}



