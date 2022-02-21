#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../headers/rbtree.h"
#include "../headers/set.h"

typedef struct info {
  int id;
  char nome[30];
  float valor;
} Info_i;


Comp 
comparar (void *valor_1, void *valor_2) {
  Info_i a = *((Info_i *) valor_1);
  Info_i b = *((Info_i *) valor_2);

  if (a.id < b.id) {
    return MENOR;
  } else if (a.id > b.id) {
    return MAIOR;
  } else {
    return IGUAL;
  }
}


void
pFormat (void *item) {
  Info_i *info_i = item;
  printf("raiz: %i string: %s float: %f\n", info_i->id, info_i->nome, info_i->valor);
}


int
main() {
  Set *A = SetInicializar();
  Set *B = SetInicializar();
      
  Info_i item_1[10] = {{20,"A",7.5},
                       {10,"A",7.5},
                       {25,"B",9.7},
                       {5,"C",8.7},
                       {13,"C",5.7},
                       {11,"C",5.7},
                       {24,"B",9.7},
                       {26,"C",8.7},
                       {4,"A",7.5},
                       {12,"A",7.5}};
  
  Info_i item_2[10] = {{20,"A",7.5},
                       {10,"A",7.5},
                       {25,"B",9.7},
                       {5,"C",8.7},
                       {13,"C",5.7},
                       {11,"C",5.7},
                       {24,"B",9.7},
                       {26,"C",8.7},
                       {4,"A",7.5},
                       {12,"A",7.5}};

  printf(" A -------------------\n");
  SetInserir(&item_1[0], A, comparar);
  SetInserir(&item_1[1], A, comparar);
  SetInserir(&item_1[4], A, comparar);
  SetInserir(&item_1[5], A, comparar);
  SetInserir(&item_1[7], A, comparar);
  SetExibir(A, pFormat);
  printf("\n");
  
  printf(" B -------------------\n");
  SetInserir(&item_1[7], B, comparar);
  SetInserir(&item_1[8], B, comparar);
  SetInserir(&item_1[4], B, comparar);
  SetInserir(&item_1[2], B, comparar);
  SetExibir(B, pFormat);
  printf("\n");

  printf(" Diferença -------------------\n");
  Set *D = SetDiferenca(A, B, comparar);
  SetExibir(D, pFormat);
  printf("\n");
  
  printf(" União -------------------\n");
  Set *U = SetUniao(A, B, comparar);
  SetExibir(U, pFormat);
  printf("\n");
  
  printf(" Intersecção -------------------\n");
  Set *I = SetInterseccao(A, B, comparar);
  SetExibir(I, pFormat);
  printf("\n");

  SetLiberarMemoria(A);
  SetLiberarMemoria(B);
  SetLiberarMemoria(D);
  SetLiberarMemoria(U);
  SetLiberarMemoria(I);
  
  return 0;
}
