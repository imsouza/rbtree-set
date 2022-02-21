#ifndef SET_H_
#define SET_H_

#include "rbtree.h"
#include "util.h"

typedef struct set Set;

Set *SetInicializar();
Set *SetInserir(void *, Set *,  Comp (*)(void *, void *));
Set *SetRemover(void *, Set *, Comp (*)(void *, void *));
Set *SetUniao(Set *, Set *, Comp (*)(void *, void *));
Set *SetInterseccao (Set *, Set *, Comp (*)(void *, void *));
Set *SetDiferenca(Set *, Set *, Comp (*)(void *, void *));
int SetTamanho(Set *);
bool SetPertence(void *, Set *, Comp (*)(void *, void *));
void SetExibir(Set *, void (*)(void *));
void SetLiberarMemoria(Set *);

#endif