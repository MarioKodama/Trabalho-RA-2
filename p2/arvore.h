#ifndef ARVORE_H
#define ARVORE_H

#include "tipos.h"

/* Arvores binarias de busca usadas para ordenar por energia e por proteina */

void montar_arvore_energia(Alimento* alimento, Node_Tree* root);
void montar_arvore_proteina(Alimento* alimento, Node_Tree* root);
void percorrer_energia(Node_Tree* root, Modo m);
void percorrer_proteina(Node_Tree* root, Modo m);
Node_Tree* criar_arvore_energia(Node_Categoria* categoria);
Node_Tree* criar_arvore_proteina(Node_Categoria* categoria);

#endif
