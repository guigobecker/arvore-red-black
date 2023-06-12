#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1


typedef struct No {
    int dado;
    int cor;
    struct No* pai;
    struct No* esquerda;
    struct No* direita;
}No;

// Função para criar nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->cor = VERMELHO;
    novoNo->pai = NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para trocar as cores
void trocarCores(No* a, No* b) {
    int temp;
    temp = a->cor;
    a->cor = b->cor;
    b->cor = temp;
}

// Função de rotação a esquerda
void rotacionarEsquerda(No** raiz, No* no) {
    No* filhoDireita = no->direita;
    no->direita = filhoDireita->esquerda;

    if (no->direita != NULL)
        no->direita->pai = no;

    filhoDireita->pai = no->pai;

    if (no->pai == NULL)
        *raiz = filhoDireita;
    else if (no == no->pai->esquerda)
        no->pai->esquerda = filhoDireita;
    else
        no->pai->direita = filhoDireita;

    filhoDireita->esquerda = no;
    no->pai = filhoDireita;
}

// Função de rotação a direita
void rotacionarDireita(No** raiz, No* no) {
    No* filhoEsquerda = no->esquerda;
    no->esquerda = filhoEsquerda->direita;

    if (no->esquerda != NULL)
        no->esquerda->pai = no;

    filhoEsquerda->pai = no->pai;

    if (no->pai == NULL)
        *raiz = filhoEsquerda;
    else if (no == no->pai->esquerda)
        no->pai->esquerda = filhoEsquerda;
    else
        no->pai->direita = filhoEsquerda;

    filhoEsquerda->direita = no;
    no->pai = filhoEsquerda;
}

// Função para balancear a arvore depois da inserção
void balancearInsercao(No** raiz, No* no) {
    No* pai = NULL;
    No* avo = NULL;

    while (no != *raiz && no->cor != PRETO && no->pai->cor == VERMELHO) {
        pai = no->pai;
        avo = pai->pai;

        if (pai == avo->esquerda) {
            No* tio = avo->direita;

            if (tio != NULL && tio->cor == VERMELHO) {
                pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            } else {
                if (no == pai->direita) {
                    rotacionarEsquerda(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                rotacionarDireita(raiz, avo);
                trocarCores(pai, avo);
                no = pai;
            }
        } else {
            No* tio = avo->esquerda;

            if (tio != NULL && tio->cor == VERMELHO) {
                pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            } else {
                if (no == pai->esquerda) {
                    rotacionarDireita(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                rotacionarEsquerda(raiz, avo);
                trocarCores(pai, avo);
                no = pai;
            }
        }
    }

    (*raiz)->cor = PRETO;
}

// Função para inserir um nó na árvore
void inserir(No** raiz, int dado) {
    No* novoNo = criarNo(dado);

    No* pai = NULL;
    No* atual = *raiz;

    while (atual != NULL) {
        pai = atual;
        if (dado < atual->dado)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }

    novoNo->pai = pai;

    if (pai == NULL)
        *raiz = novoNo;
    else if (dado < pai->dado)
        pai->esquerda = novoNo;
    else
        pai->direita = novoNo;

    balancearInsercao(raiz, novoNo);
}

// Função para imprimir a árvore em ordem
void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}

// Função para buscar um nó na árvore
No* buscar(No* raiz, int dado) {
    if (raiz == NULL || raiz->dado == dado)
        return raiz;

    if (dado < raiz->dado)
        return buscar(raiz->esquerda, dado);

    return buscar(raiz->direita, dado);
}

// Função para balancear a árvore depois da exclusão
void balancearExclusao(No** raiz, No* no, No* noPai) {
    No* irmao;

    while ((no == NULL || no->cor == PRETO) && (no != *raiz)) {
        if (no == noPai->esquerda) {
            irmao = noPai->direita;

            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                noPai->cor = VERMELHO;
                rotacionarEsquerda(raiz, noPai);
                irmao = noPai->direita;
            }

            if ((irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) &&
                (irmao->direita == NULL || irmao->direita->cor == PRETO)) {
                irmao->cor = VERMELHO;
                no = noPai;
                noPai = no->pai;
            } else {
                if (irmao->direita == NULL || irmao->direita->cor == PRETO) {
                    if (irmao->esquerda != NULL)
                        irmao->esquerda->cor = PRETO;

                    irmao->cor = VERMELHO;
                    rotacionarDireita(raiz, irmao);
                    irmao = noPai->direita;
                }

                irmao->cor = noPai->cor;
                noPai->cor = PRETO;

                if (irmao->direita != NULL)
                    irmao->direita->cor = PRETO;

                rotacionarEsquerda(raiz, noPai);
                no = *raiz;
                break;
            }
        } else {
            irmao = noPai->esquerda;

            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                noPai->cor = VERMELHO;
                rotacionarDireita(raiz, noPai);
                irmao = noPai->esquerda;
            }

            if ((irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) &&
                (irmao->direita == NULL || irmao->direita->cor == PRETO)) {
                irmao->cor = VERMELHO;
                no = noPai;
                noPai = no->pai;
            } else {
                if (irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) {
                    if (irmao->direita != NULL)
                        irmao->direita->cor = PRETO;

                    irmao->cor = VERMELHO;
                    rotacionarEsquerda(raiz, irmao);
                    irmao = noPai->esquerda;
                }

                irmao->cor = noPai->cor;
                noPai->cor = PRETO;

                if (irmao->esquerda != NULL)
                    irmao->esquerda->cor = PRETO;

                rotacionarDireita(raiz, noPai);
                no = *raiz;
                break;
            }
        }
    }

    if (no != NULL)
    {
        no->cor = PRETO;
    }
}


// Função para excluir nó da arvore
void excluir(No** raiz, int dado) {
    No* no = buscar(*raiz, dado);

    if (no == NULL)
        return;

    No* noFilho = NULL;
    No* noPai = NULL;

    if (no->esquerda == NULL || no->direita == NULL)
        noPai = no;
    else
        noPai = no->direita;

    if (no->esquerda != NULL)
        noFilho = no->esquerda;
    else
        noFilho = no->direita;

    if (noFilho != NULL)
        noFilho->pai = noPai;

    if (noPai->pai == NULL)
        *raiz = noFilho;
    else if (noPai == noPai->pai->esquerda)
        noPai->pai->esquerda = noFilho;
    else
        noPai->pai->direita = noFilho;

    if (no != noPai)
        no->dado = noPai->dado;

    if (noPai->cor == PRETO)
        balancearExclusao(raiz, noFilho, noPai);

    free(noPai);
}

// Função para deletar a arvore da memória
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;

    int opcao, valor;
    while (1)
    {
        printf("1 - Inserir\n2 - Excluir\n3 - Buscar\n4 - Imprimir\n5 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            printf("Digite o valor a ser inserido: \n");
            scanf("%d", &valor);
            inserir(&raiz, valor);
            break; 
        case 2:
            printf("Digite o valor a ser excluido: \n");
            scanf("%d", &valor);
            excluir(&raiz, valor);
            break;
        case 3:
            printf("Digite o valor a ser buscado: \n");
            scanf("%d", &valor);
            buscar(raiz, valor) ? printf("\nEncontrado\n\n\n") : printf("\nNao encontrado\n\n\n");
            break;
        case 4:
            printf("Arvore Red-Black em ordem: ");
            imprimirEmOrdem(raiz);
            printf("\n\n");
            break;
        case 5:
            return 0;
        default:
            printf("Opcao invalida\n");
        }
    }
    
    liberarArvore(raiz);
    return 0;
}
