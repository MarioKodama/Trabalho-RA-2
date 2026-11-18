#ifndef LISTA_H
#define LISTA_H

#include "tipos.h"

/* Listas encadeadas de alimentos e de categorias */

Node_Alimento* inserir_node(Node_Alimento* tail, Alimento* alimento);
Node_Alimento* criar_lista_alimento(char* categoria, Node_Alimento* head);
Node_Categoria* inserir_node_categoria(Node_Categoria* tail, char* categoria, Node_Alimento* head, enum Categoria c);
void imprimir_categorias(Node_Categoria* head);

/* 7. Remove uma categoria (n = numero mostrado no menu) */
int remover_categoria(Node_Categoria** head, int n);

/* 8. Remove um alimento especifico de uma categoria */
void imprimir_alimentos_numero(Node_Categoria* head, int n);
int remover_alimento(Node_Categoria* head, int n, unsigned int numero);

/* Liberacao de memoria */
void liberar_lista_alimento(Node_Alimento* head);
void liberar_categorias(Node_Categoria* head);

#endif
