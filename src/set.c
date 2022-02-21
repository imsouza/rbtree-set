#include "../headers/rbtree.h"
#include "../headers/set.h"

struct set {
  RBTree *node;
  int qtde;
};


Set *
SetInicializar () {
  Set *set    = mallocSafe (sizeof(Set));
  set->node   = RBTreeInicializar();
  set->qtde   = 0;
  return set;
}


Set *
SetInserir (void *dado, Set *set, Comp (*comparar)(void *, void *)) {
  if (set != NULL) {
    set->node = RBTreeInserirNo(set->node, \
                                RBTreeCriarNo(dado), \
                                &(set->qtde), \
                                comparar);
  }

  return set;
}


Set *
SetRemover (void *dado, Set *set, Comp (*comparar)(void *, void *)) {
  if (set->node != NULL) {
    set->node = RBTreeRemoverNo(set->node, \
                                dado, \
                                &set->qtde, \
                                comparar);
  }

  return set;
}


void 
SetExibir (Set *set, void (*pFormat)(void *)) {
  RBTreeExibir(set->node, pFormat);
}


int
SetTamanho (Set *set) {
  return set->qtde;
}


bool
SetPertence (void *dado, Set *set, Comp (*comparar)(void *, void *)) {
  return RBTreeBuscar(dado, set->node, comparar) != NULL;
}


Set *
SetUniao (Set *A, Set *B, Comp (*comparar)(void *, void *)) {
  Set *C = SetInicializar();
  C->node = RBTreeCopiarArvore(&C->node, A->node, &(C->qtde), comparar);
  C->node = RBTreeCopiarArvore(&C->node, B->node, &(C->qtde), comparar);
  return C;
}


Set *
SetInterseccao (Set *A, Set *B, Comp (*comparar)(void *, void *)) {
  if (A == NULL || B == NULL) {
    return NULL;
  }

  Set *C = SetInicializar();

  if (A->qtde < B->qtde) {
    C->node = RBTreeRetornaNosIguais(&C->node, A->node, B->node, &(C->qtde), comparar);
  } else {
    C->node = RBTreeRetornaNosIguais(&C->node, B->node, A->node, &(C->qtde), comparar);
  }

  return C;
}


Set *
SetDiferenca (Set *A, Set *B, Comp (*comparar)(void *, void *)) {
  if ((A == NULL || A->node == NULL) && (B == NULL || B->node == NULL)) {
    return NULL;
  }
  
  Set *C = SetInicializar();

  if (A == NULL || A->node == NULL) {
    RBTreeCopiarArvore(&C->node, B->node, &(C->qtde), comparar);
    return C;
  }

  if (B == NULL || B->node == NULL) {
    RBTreeCopiarArvore(&C->node, A->node, &(C->qtde), comparar);
    return C;
  }

  C->node = RBTreeRetornaNosDiferentes(&C->node, A->node, B->node, &(C->qtde), comparar);

  return C;
}


void 
SetLiberarMemoria (Set *set) {
  if (set != NULL) {
    RBTreeLiberarMemoria(set->node);
    free(set);
    set = NULL;
  }
}