#ifndef RBTREE_H_
#define RBTREE_H_

#include "util.h"

typedef enum {
  BLACK,
  RED
} tCor;

typedef enum {
  MENOR,
  MAIOR,
  IGUAL
} Comp;

typedef struct item {
  void *dado;
} Info;

typedef struct no {
  tCor cor;
  Info info;
  struct no *pai;
  struct no *esq;
  struct no *dir;
} RBTree;

RBTree *RBTreeInicializar();
RBTree *RBTreeCriarNo(void *); 
RBTree *RBTreeRotacaoEsquerda(RBTree *, RBTree *);
RBTree *RBTreeRotacaoDireita(RBTree *, RBTree *);
RBTree *RBTreeInserirNo(RBTree *, RBTree *, int *, Comp (*)(void *, void *));
RBTree *RBTreeConsertarInserir(RBTree *, RBTree *);
RBTree *RBTreeTransferePai(RBTree *, RBTree *, RBTree *);
RBTree *RBTreeRemoverNo(RBTree *, void *, int *qtde, Comp (*)(void *, void *));
RBTree *RBTreeConsertarRemoverNo(RBTree *, RBTree *);
RBTree *RBTreeCopiarArvore(RBTree **, RBTree *, int *, Comp (*)(void *, void *));
RBTree *RBTreeRetornaNosIguais(RBTree **, RBTree *, RBTree *, int *, Comp (*)(void *, void *));
RBTree *RBTreeRetornaNosDiferentes(RBTree **, RBTree *, RBTree *, int *, Comp (*)(void *, void *));
RBTree *RBTreeRemoverMinimo(void *, RBTree *);
RBTree *RBTreeBuscar(void *, RBTree *, Comp (*)(void *, void *));
RBTree *RBTreeBuscarMinimo(RBTree *);
int RBTreeTotalNos(RBTree *);
int RBTreeAltura(RBTree *);
int RBTreeTotalFolhas(RBTree *);
bool RBTreeEstaVazia(RBTree *);
void RBTreeExibir(RBTree *, void (*)(void *));
void RBTreeLiberarMemoria(RBTree *);
void RBTreeLiberarNo(RBTree *);

#endif