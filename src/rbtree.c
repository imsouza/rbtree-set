#include "../headers/rbtree.h"

RBTree *
RBTreeInicializar () {
  RBTree *raiz = NULL;
  return raiz;
}


RBTree *
RBTreeExterno () {
  RBTree *no = mallocSafe (sizeof(RBTree));
  no->cor    = BLACK;
  no->pai    = NULL;
  no->esq    = NULL;
  no->dir    = NULL;
  no->info.dado  = NULL;
  return no;
}


RBTree *
RBTreeCriarNo (void *dado) {
  RBTree *no     = mallocSafe (sizeof(RBTree));
  no->info.dado  = dado;
  no->pai        = NULL;
  no->esq        = RBTreeExterno();
  no->dir        = RBTreeExterno();
  no->cor        = RED;
  return no;
}


tCor 
RBTreeCor (RBTree *raiz) {
  if (raiz == NULL) {
    return BLACK;
  } else {
    return raiz->cor;
  }
}


RBTree *
RBTreeRotacaoEsquerda (RBTree *raiz, RBTree *pivo) {
  RBTree *filho = pivo->dir;
  pivo->dir = filho->esq;
  
  if (filho->esq != NULL) {
    filho->esq->pai = pivo;
  }

  filho->pai = pivo->pai;

  if(pivo->pai == NULL){
    raiz = filho;
  } else if (pivo == pivo->pai->esq) {
    pivo->pai->esq = filho;
  } else {
    pivo->pai->dir = filho;
  }

  filho->esq = pivo;
  pivo->pai = filho;

  return raiz;
}


RBTree *
RBTreeRotacaoDireita (RBTree *raiz, RBTree *pivo) {
  RBTree *filho = pivo->esq;
  pivo->esq = filho->dir;

  if (filho->dir != NULL) {
    filho->dir->pai = pivo;
  }

  filho->pai = pivo->pai;

  if(pivo->pai == NULL){
    raiz = filho;
  } else if (pivo == pivo->pai->dir) {
    pivo->pai->dir = filho;
  } else {
    pivo->pai->esq = filho;
  }  

  filho->dir = pivo;
  pivo->pai = filho;

  return raiz;
}


RBTree *
RBTreeInserirNo (RBTree *raiz, RBTree *novo, int *raizQtde, Comp (*comparar)(void *, void *)) {
  RBTree *no = raiz;
  RBTree *pai = NULL;
  
  while (no != NULL) {   
    if (comparar(novo->info.dado, no->info.dado) == IGUAL) {
      RBTreeLiberarNo(novo->esq);
      RBTreeLiberarNo(novo->dir);
      RBTreeLiberarNo(novo);
      novo = NULL;
      return raiz;
    }

    pai = no;

    if (comparar(novo->info.dado, no->info.dado) == MENOR) {
      if (no->esq->info.dado != NULL) {
        no = no->esq;
      } else {
        break;
      }
    } else {
      if (no->dir->info.dado != NULL) {
        no = no->dir;
      } else {
        break;
      }
    }
  }

  novo->pai = pai;
  novo->esq->pai = novo;
  novo->dir->pai = novo;

  if (pai == NULL) {
    raiz = novo;
    raiz->cor = BLACK;
  } else {
    if (comparar(novo->info.dado, pai->info.dado) == MENOR) {
      RBTreeLiberarNo(pai->esq);
      pai->esq = novo;
    } else {
      RBTreeLiberarNo(pai->dir);
      pai->dir = novo;
    }

    raiz = RBTreeConsertarInserir(raiz, novo);
  } 
  
  *raizQtde += 1;
  return raiz;
}


RBTree *
RBTreeConsertarInserir (RBTree *raiz, RBTree *novo) {
  RBTree *pai, *avo, *tio;
  
  while (novo->pai != NULL && novo->pai->cor == RED) {
    pai = novo->pai;
    avo = pai->pai;

    if (pai == avo->esq) {
      tio = avo->dir;

      if(tio->cor == RED){
        pai->cor = BLACK;
        tio->cor = BLACK;
        avo->cor = RED;
        novo = avo;
      } else {
        if (novo == pai->dir ){
          novo = pai;
          raiz = RBTreeRotacaoEsquerda(raiz, novo);
        }

        novo->pai->cor = BLACK;
        avo->cor = RED;
        raiz = RBTreeRotacaoDireita(raiz, avo);
      }
    } else {
      tio = avo->esq;

      if (tio->cor == RED) {
        pai->cor = BLACK;
        tio->cor = BLACK;
        avo->cor = RED;
        novo = avo;
      } else {
        if (novo == pai->esq) {
          novo = pai;
          raiz = RBTreeRotacaoDireita(raiz, novo);
        }

        novo->pai->cor = BLACK;
        avo->cor = RED;
        raiz = RBTreeRotacaoEsquerda(raiz, avo);
      }
    }
  }

  raiz->cor = BLACK;
  return raiz;
}


RBTree *
RBTreeTransferePai (RBTree *raiz, RBTree *antigo, RBTree *novo) {  
  if (antigo->pai == NULL) {
    raiz = novo;
  } else {
    if (antigo == antigo->pai->esq) {
      antigo->pai->esq = novo;
    } else if (antigo == antigo->pai->dir) {
      antigo->pai->dir = novo;
    }
  }

  novo->pai = antigo->pai;
  return raiz;
}


RBTree *
RBTreeRemoverNo (RBTree *raiz, void *valor, int *qtde, Comp (*comparar)(void *, void *)) {
  RBTree *noY, *noX, *retirado;

  tCor corDoSucessorDeX;
  
  retirado = RBTreeBuscar(valor, raiz, comparar);

  if (retirado == NULL) {
    return raiz;
  }
  
  if (retirado != NULL) {
    noX = retirado;
    corDoSucessorDeX = retirado->cor;

    if (retirado->esq->info.dado == NULL) {
      noY = retirado->dir;
      raiz = RBTreeTransferePai(raiz, retirado, retirado->dir);
      RBTreeLiberarNo(retirado->esq);
    } else if (retirado->dir->info.dado == NULL) {
      noY = retirado->esq;   
      raiz = RBTreeTransferePai(raiz, retirado, retirado->esq);
      RBTreeLiberarNo(retirado->dir);
    } else {
      noX = RBTreeBuscarMinimo(retirado);
      corDoSucessorDeX = noX->cor;
      noY = noX->dir;

      if (noX->pai == retirado) {
          noY->pai = noX;
      } else {
        raiz = RBTreeTransferePai(raiz, noX, noX->dir);
        noX->dir = retirado->dir;
        noX->dir->pai = noX;
      }

      raiz = RBTreeTransferePai(raiz, retirado, noX);
      RBTreeLiberarNo(noX->esq);
      noX->esq = retirado->esq;
      noX->esq->pai = noX;
      noX->cor = retirado->cor;
    }

    (*qtde)--;
  }

  if (corDoSucessorDeX == BLACK) {
    raiz = RBTreeConsertarRemoverNo(raiz, noY);
  }

  RBTreeLiberarNo(retirado);
  return raiz;
}


RBTree *
RBTreeConsertarRemoverNo (RBTree *raiz, RBTree *novo) {
  RBTree *no;

  while (novo != raiz && novo->cor == BLACK) {
    if (novo == novo->pai->esq) {
      no = novo->pai->dir;

      if (no->cor == RED) {
        no->cor = BLACK;
        novo->pai->cor = RED;
        raiz = RBTreeRotacaoEsquerda(raiz, novo->pai);
        no = novo->pai->dir;
      }

      if (no->esq->cor == BLACK && no->dir->cor == BLACK) {
        no->cor = RED;
        novo = novo->pai;
      } else {
        if (no->dir->cor == BLACK) {
          no->esq->cor = BLACK;
          no->cor = RED;
          raiz = RBTreeRotacaoDireita(raiz, no);
          no = novo->pai->dir;
        }

        no->cor = novo->pai->cor;
        novo->pai->cor = BLACK;
        no->dir->cor = BLACK;
        raiz = RBTreeRotacaoEsquerda(raiz, novo->pai);
        novo = raiz;
      } 
    } else {
      no = novo->pai->esq;

      if (no->cor == RED) {
        no->cor = BLACK;
        novo->pai->cor = RED;
        raiz = RBTreeRotacaoDireita(raiz, novo->pai);
        no = novo->pai->esq;
      }

      if (no->dir->cor == BLACK && no->esq->cor == BLACK) {
        no->cor = RED;
        novo = novo->pai;
      } else {
        if (no->esq->cor == BLACK) {
          no->dir->cor = BLACK;
          no->cor = RED;
          raiz = RBTreeRotacaoEsquerda(raiz, no);
          no = novo->pai->esq;
        }

        no->cor = novo->pai->cor;
        novo->pai->cor = BLACK;
        no->esq->cor = BLACK;
        raiz = RBTreeRotacaoDireita(raiz, novo->pai);
        novo = raiz;
      }
    }
  }

  novo->cor = BLACK;
  return raiz;
}


RBTree *
RBTreeBuscar (void *dado, RBTree *raiz, Comp (*comparar)(void *valor_1, void *valor_2)) {
  if (raiz == NULL || raiz->info.dado == NULL) {
    return NULL;
  } 
  int RESULT = comparar(dado, raiz->info.dado);
  
  if(RESULT == IGUAL){
    return raiz;
  } else if (RESULT == MENOR) {
    return RBTreeBuscar(dado, raiz->esq, comparar);
  } else {
    return RBTreeBuscar(dado, raiz->dir, comparar);
  }
}


RBTree *
RBTreeBuscarMinimo (RBTree *raiz) {
  RBTree *temp1 = raiz;
  RBTree *temp2 = raiz->dir;

  while (temp2->info.dado != NULL) {
    temp1 = temp2;
    temp2 = temp2->esq;
  }

  return temp1;
}


int 
RBTreeTotalNos (RBTree *raiz) {
  if (raiz->info.dado == NULL) {
    return 0;
  } else {
    return RBTreeTotalNos(raiz->esq) + \
    RBTreeTotalNos(raiz->dir) + 1;
  }
}


int 
RBTreeAltura (RBTree *raiz) {
  if (raiz->info.dado == NULL) {
    return -1;
  }

  int hSTL = RBTreeAltura(raiz->esq);
  int hSTR = RBTreeAltura(raiz->dir);

  if (hSTL > hSTR) {
    return hSTL + 1;
  } else {
    return hSTR + 1;
  }
}


int 
RBTreeTotalFolhas (RBTree *raiz) {
  if (raiz == NULL) {
    return 0;
  } else if (raiz->esq->info.dado == NULL && \
             raiz->dir->info.dado == NULL) { 
    return 1; 
  }

  return RBTreeTotalFolhas(raiz->esq) + \
  RBTreeTotalFolhas(raiz->dir);
}


bool 
RBTreeEstaVazia (RBTree *raiz) {
  return (raiz == NULL);
}


void 
RBTreeExibir (RBTree *raiz, void (*pFormat)(void *)) {
  if(raiz == NULL || raiz->info.dado == NULL){
    return;
  }

  RBTreeExibir(raiz->esq, pFormat);

  if (raiz->cor == BLACK) {
    printf("cor: "BBLK"black "reset);
  } else {
    printf("cor:   "BRED"red "reset);
  }

  pFormat(raiz->info.dado);
  RBTreeExibir(raiz->dir, pFormat);
}


RBTree *
RBTreeCopiarArvore (RBTree **raiz, RBTree *no, int *qtde, Comp (*comparar)(void *valor_1, void *valor_2)) {
  if(no == NULL || no->info.dado == NULL){
    return *raiz;
  }
  
  if (RBTreeBuscar(no->info.dado, *raiz, comparar) == NULL) {
    *raiz = RBTreeInserirNo(*raiz, \
                             RBTreeCriarNo(no->info.dado), \
                             &(*qtde), \
                             comparar);
  }

  RBTreeCopiarArvore(raiz, no->esq, qtde, comparar);
  RBTreeCopiarArvore(raiz, no->dir, qtde, comparar);
  
  return *raiz;
}


RBTree *
RBTreeRetornaNosIguais (RBTree **raiz, RBTree *no_1, RBTree *no_2, \
int *qtde, Comp (*comparar)(void *valor_1, void *valor_2)) {
  if (no_1 == NULL || no_1->info.dado == NULL){
    return NULL;
  }
  
  if (RBTreeBuscar(no_1->info.dado, no_2, comparar) != NULL) {
    *raiz = RBTreeInserirNo(*raiz, \
                             RBTreeCriarNo(no_1->info.dado), \
                             qtde, \
                             comparar);
  }
  
  RBTreeRetornaNosIguais(raiz, no_1->esq, no_2, qtde, comparar);
  RBTreeRetornaNosIguais(raiz, no_1->dir, no_2, qtde, comparar);

  return *raiz;
}


RBTree *
RBTreeRetornaNosDiferentes (RBTree **raiz, RBTree *no_1, RBTree *no_2, int *qtde, Comp (*comparar)(void *valor_1, void *valor_2)) {
  if (no_1 == NULL || no_1->info.dado == NULL) {
    return NULL;
  }

  if (RBTreeBuscar(no_1->info.dado, no_2, comparar) == NULL) {
    *raiz = RBTreeInserirNo(*raiz, \
                             RBTreeCriarNo(no_1->info.dado), \
                             qtde, \
                             comparar);
  }

  RBTreeRetornaNosDiferentes(raiz, no_1->esq, no_2, qtde, comparar);
  RBTreeRetornaNosDiferentes(raiz, no_1->dir, no_2, qtde, comparar);

  return *raiz;
}


void 
RBTreeLiberarMemoria (RBTree *raiz) {
  if (raiz != NULL) {
    RBTreeLiberarMemoria(raiz->esq);
    RBTreeLiberarMemoria(raiz->dir);
    free(raiz);
    raiz = NULL;
  }
}


void 
RBTreeLiberarNo (RBTree *no) {
  if (no != NULL) {
    free(no);
    no = NULL;
  }
}