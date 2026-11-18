#ifndef TIPOS_H
#define TIPOS_H

/* Tipos usados em todo o programa */

/* Registro de um alimento, do mesmo jeito que esta gravado no dados.bin */
typedef struct { unsigned int numero; char desc[128]; unsigned int energia; float proteina; char categoria[64]; }Alimento;

/* Uma posicao para cada categoria; MAX_CATEGORIAS e o total */
typedef enum Categoria {
	Alimentos_preparados,
	Bebidas,
	Carnes_derivados,
	Cereais_derivados,
	Frutas_derivados,
	Gorduras_oleos,
	Leguminosas_derivados,
	Leite_derivados,
	Miscelaneas,
	Nozes_sementes,
	Outros_alimentos_industrializados,
	Ovos_derivados,
	Pescados_frutosdomar,
	Produtos_acucarados,
	Verduras_hortalicas_derivados,
	MAX_CATEGORIAS
}Categoria;

/* NORMAL lista tudo; MIN_MAX lista so os valores dentro da faixa pedida (opcoes 5 e 6) */
typedef enum { NORMAL, MIN_MAX }Modo;

/* No da lista de alimentos (aponta para o alimento no buffer, nao copia) */
typedef struct Node_Alimento { Alimento* alimento; struct Node_Alimento* next; }Node_Alimento;
/* No da lista de categorias; cada categoria guarda a sua propria lista de alimentos */
typedef struct Node_Categoria { enum Categoria id; char nome[64]; Node_Alimento* alimentos; struct Node_Categoria* next; } Node_Categoria;
typedef struct vector { void* data; int n;}vector;
/* No das arvores binarias de busca (por energia ou por proteina) */
typedef struct Node_Tree { Alimento* alimento; struct Node_Tree* left; struct Node_Tree* right;}Node_Tree;

#endif
