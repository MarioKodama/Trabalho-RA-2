#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* Cria um no para o alimento, liga depois do tail e retorna o novo tail */
Node_Alimento* inserir_node(Node_Alimento* tail, Alimento* alimento) {


	Node_Alimento* node = (Node_Alimento*)malloc(sizeof(Node_Alimento));
	node->alimento = alimento;
	node->next = NULL;


	tail->next = node;

	return node;





}






/* Percorre a lista com todos os alimentos e monta uma lista nova
   so com os que sao da categoria pedida. Retorna o inicio dessa lista. */
Node_Alimento* criar_lista_alimento(char* categoria, Node_Alimento* head) {

	Node_Alimento* atual = head;
	Node_Alimento* tail = NULL;
	Node_Alimento* heads = NULL;



	while (atual != NULL) {
		if (!tail) { // primeiro alimento encontrado vira o inicio da lista
			if (!strcmp(categoria, atual->alimento->categoria)) {
				tail = malloc(sizeof(Node_Alimento));
				tail->alimento = atual->alimento;
				tail->next = NULL;
				heads = tail;

			}

		}
		else if (!strcmp(categoria, atual->alimento->categoria)) {
			Node_Alimento* node = malloc(sizeof(Node_Alimento));
			node->alimento = atual->alimento;
			node->next = NULL;
			tail->next = node;
			tail = node;

		}

		atual = atual->next;
	}

	return heads;

}

/* Cria o no de uma categoria (ja com a sua lista de alimentos),
   liga depois do tail e retorna o novo tail */
Node_Categoria* inserir_node_categoria(Node_Categoria* tail, char* categoria, Node_Alimento* head, enum Categoria c) {


	Node_Categoria* node = (Node_Categoria*)malloc(sizeof(Node_Categoria));
	strcpy(node->nome, categoria);
	node->alimentos = criar_lista_alimento(node->nome, head);
	node->next = NULL;
	node->id = c;

	tail->next = node;

	return node;





}

/* Mostra as categorias numeradas a partir de 1 */
void imprimir_categorias(Node_Categoria* head) {
	Node_Categoria* atual = head;
	int count = 0;
	while (atual != NULL) {

		printf("%d: %s\n", ++count, atual->nome);


		atual = atual->next;
	}



}

/* 7. Remove a categoria de numero n (o numero mostrado no menu).
   Recebe Node_Categoria** porque, se a primeira categoria for removida,
   o inicio da lista no main tambem muda. Retorna 1 se removeu, 0 se nao achou. */
int remover_categoria(Node_Categoria** head, int n) {

	Node_Categoria* atual = *head;
	Node_Categoria* anterior = NULL;
	n--;

	while (atual) {

		if (atual->id == n) {

			// tira a categoria da lista
			if (anterior == NULL) *head = atual->next;
			else anterior->next = atual->next;

			// libera os nos da lista de alimentos (os alimentos ficam no buffer do main)
			liberar_lista_alimento(atual->alimentos);

			free(atual);

			// renumera os ids para continuarem batendo com a numeracao do menu
			int id = 0;
			Node_Categoria* c = *head;
			while (c) {
				c->id = (Categoria)id++;
				c = c->next;
			}

			return 1;
		}

		anterior = atual;
		atual = atual->next;
	}

	return 0;
}


/* Lista os alimentos da categoria n com o numero de cada um,
   para o usuario escolher qual remover na opcao 8 */
void imprimir_alimentos_numero(Node_Categoria* head, int n) {

	Node_Categoria* atual = head;
	n--;
	while (atual) {

		if (atual->id == n) {
			printf("----%s\n", atual->nome);
			Node_Alimento* alimento = atual->alimentos;
			while (alimento) {
				printf("%u: %s\n", alimento->alimento->numero, alimento->alimento->desc);
				alimento = alimento->next;
			}
		}

		atual = atual->next;
	}
}

/* 8. Remove da categoria n o alimento com esse numero.
   Retorna 1 se removeu, 0 se nao achou. */
int remover_alimento(Node_Categoria* head, int n, unsigned int numero) {

	Node_Categoria* atual = head;
	n--;
	while (atual) {

		if (atual->id == n) {

			Node_Alimento* alimento = atual->alimentos;
			Node_Alimento* anterior = NULL;

			while (alimento) {

				if (alimento->alimento->numero == numero) {

					// religa a lista pulando o no removido
					if (anterior == NULL) atual->alimentos = alimento->next;
					else anterior->next = alimento->next;

					free(alimento);
					return 1;
				}

				anterior = alimento;
				alimento = alimento->next;
			}

			return 0;
		}

		atual = atual->next;
	}

	return 0;
}

/* Libera todos os nos de uma lista de alimentos.
   So libera os nos: os Alimento ficam no buffer_alimento, liberado no main. */
void liberar_lista_alimento(Node_Alimento* head) {

	Node_Alimento* atual = head;
	while (atual) {
		Node_Alimento* prox = atual->next; // guarda o proximo antes de liberar
		free(atual);
		atual = prox;
	}
}

/* Libera todas as categorias, junto com a lista de alimentos de cada uma */
void liberar_categorias(Node_Categoria* head) {

	Node_Categoria* atual = head;
	while (atual) {
		Node_Categoria* prox = atual->next;
		liberar_lista_alimento(atual->alimentos);
		free(atual);
		atual = prox;
	}
}
