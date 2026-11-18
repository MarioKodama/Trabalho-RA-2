#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* Insere o alimento na arvore de energia: menor vai para a esquerda,
   maior ou igual para a direita. Desce recursivamente ate achar um lugar vazio. */
void montar_arvore_energia(Alimento* alimento, Node_Tree* root) {

	Node_Tree* atual = root;
	if (alimento->energia < atual->alimento->energia) {
		if (atual->left == NULL) {
			Node_Tree* node = malloc(sizeof(Node_Tree));
			node->alimento = alimento;
			node->left = NULL;
			node->right = NULL;
			atual->left = node;
			atual = node;
			return;

		}
		else {
			montar_arvore_energia(alimento, atual->left);
		}

	}
	else {
		if (atual->right == NULL) {
			Node_Tree* node = malloc(sizeof(Node_Tree));
			node->alimento = alimento;
			node->left = NULL;
			node->right = NULL;
			atual->right = node;
			atual = node;
			return;
		}
		else {
			montar_arvore_energia(alimento, atual->right);
		}
	}



}

/* Igual a montar_arvore_energia, mas comparando a proteina */
void montar_arvore_proteina(Alimento* alimento, Node_Tree* root) {

	Node_Tree* atual = root;
	if (alimento->proteina < atual->alimento->proteina) {
		if (atual->left == NULL) {
			Node_Tree* node = malloc(sizeof(Node_Tree));
			node->alimento = alimento;
			node->left = NULL;
			node->right = NULL;
			atual->left = node;
			atual = node;
			return;

		}
		else {
			montar_arvore_proteina(alimento, atual->left);
		}

	}
	else {
		if (atual->right == NULL) {
			Node_Tree* node = malloc(sizeof(Node_Tree));
			node->alimento = alimento;
			node->left = NULL;
			node->right = NULL;
			atual->right = node;
			atual = node;
			return;
		}
		else {
			montar_arvore_proteina(alimento, atual->right);
		}
	}



}

/* Percorre direita -> raiz -> esquerda, entao imprime do maior para o menor.
   Em MIN_MAX so imprime quem esta entre 100 e 300 kcal. */
void percorrer_energia(Node_Tree* root, Modo m) {

    if (root == NULL) return;

    percorrer_energia(root->right, m);
	if (m == NORMAL)
    printf("%s: %d Kcal\n", root->alimento->desc, root->alimento->energia);

	else if (m == MIN_MAX) {
		if (root->alimento->energia >= 100 && root->alimento->energia <= 300)printf("%s: %d Kcal\n", root->alimento->desc, root->alimento->energia);
	}

    percorrer_energia(root->left, m);
}

/* Mesmo percurso, por proteina. Em MIN_MAX so imprime quem esta entre 6 e 10 g. */
void percorrer_proteina(Node_Tree* root, Modo m) {

	if (root == NULL) return;

	percorrer_proteina(root->right, m);

	if(m == NORMAL)
	printf("%s: %.2fg\n", root->alimento->desc, root->alimento->proteina);

	else if (m == MIN_MAX) {
		if(root->alimento->proteina >= 6 && root->alimento->proteina <= 10)printf("%s: %.2fg\n", root->alimento->desc, root->alimento->proteina);

	}

	percorrer_proteina(root->left, m);
}

/* Monta uma arvore nova a partir da lista atual da categoria:
   o primeiro alimento e a raiz e os outros sao inseridos um a um.
   Como e criada a cada consulta, ja reflete as remocoes. */
Node_Tree* criar_arvore_energia(Node_Categoria* categoria) {

		if (categoria->alimentos == NULL) return NULL; /* categoria ficou vazia apos remocoes */

		Node_Tree* root = malloc(sizeof(Node_Tree));

		root->alimento = categoria->alimentos->alimento;
		root->left = NULL;
		root->right = NULL;

		Node_Alimento* atual = categoria->alimentos->next;

		while (atual) {
			montar_arvore_energia(atual->alimento, root);
			atual = atual->next;
		}

		return root;



}

/* Igual a criar_arvore_energia, mas por proteina */
Node_Tree* criar_arvore_proteina(Node_Categoria* categoria) {

	if (categoria->alimentos == NULL) return NULL; /* categoria ficou vazia apos remocoes */

	Node_Tree* root = malloc(sizeof(Node_Tree));

	root->alimento = categoria->alimentos->alimento;
	root->left = NULL;
	root->right = NULL;

	Node_Alimento* atual = categoria->alimentos->next;

	while (atual) {
		montar_arvore_proteina(atual->alimento, root);
		atual = atual->next;
	}

	return root;



}

/* Libera a arvore em pos-ordem (filhos antes do pai).
   So libera os nos: os Alimento continuam no buffer. */
void liberar_arvore(Node_Tree* root) {

	if (root == NULL) return;

	liberar_arvore(root->left);
	liberar_arvore(root->right);
	free(root);
}
