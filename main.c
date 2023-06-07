#include <stdio.h>

struct no{
    int chave;
    int cor; //0 = preto, 1 = vermelho
    struct no *esq, *dir, *pai;
};

struct no *raiz = NULL;

void rotacao_esq(struct no *x){
    struct no *y;
    y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL){
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == NULL){
        raiz = y;
    }else if(x == x->pai->esq){
        x->pai->esq = y;
    }else{
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void rotacao_dir(struct no *x){
    struct no *y;
    y = x->esq;
    x->esq = y->dir;
    if(y->dir != NULL){
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == NULL){
        raiz = y;
    }else if(x == x->pai->dir){
        x->pai->dir = y;
    }else{
        x->pai->esq = y;
    }
    y->dir = x;
    x->pai = y;
}

struct no *cria_arvore(int chave){
    struct no *n;
    n = (struct no*)malloc(sizeof(struct no));
    n->chave = chave;
    n->cor = 1;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    return n;
}
