typedef struct _arvore_{
    char *op;
    int *val;
    struct _arvore_ *pai;
    struct _arvore_ *esq;
    struct _arvore_ *dir;
} Arvore;

Arvore *criar(char *op, int *val);

char inserirEsq(Arvore *a, Arvore *b);

char inserirDir(Arvore *a, Arvore *b);

void print_arvore(Arvore *a);