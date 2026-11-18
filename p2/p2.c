#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "tipos.h"
#include "lista.h"
#include "arvore.h"
#include "arquivo.h"

// nomes das categorias exatamente como aparecem no dados.bin (com o espaco no inicio)
const char* nome_categorias[MAX_CATEGORIAS] = {
	" Alimentos preparados",
" Bebidas (alcoólicas e não alcoólicas)",
 " Carnes e derivados",
 " Cereais e derivados",
 " Frutas e derivados",
 " Gorduras e óleos",
 " Leguminosas e derivados",
 " Leite e derivados",
 " Miscelâneas",
 " Nozes e sementes",
 " Outros alimentos industrializados",
" Ovos e derivados",
 " Pescados e frutos do mar",
 " Produtos açucarados",
 " Verduras, hortaliças e derivados"
};

int buffer_size = 600; // capacidade maxima de alimentos lidos do arquivo

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, ".UTF8");

	FILE* file = fopen("dados.bin", "rb");
	if (file == NULL)return -1;

	unsigned int byte = 0;
	unsigned int total = 0;
	Alimento* buffer_alimento = (Alimento*)malloc(sizeof(Alimento) * buffer_size); //Alocamos memoria suficiente na heap para inserir os alimentos

	
	
	while ((byte = fread(&buffer_alimento[total], sizeof(Alimento), 1, file)) > 0)total += byte; //Lemos do .bin as estruturas e mapeamos na heap

	fclose(file);


	//inicio da lista encadeada dos alimentos
	Node_Alimento* head = (Node_Alimento*)malloc(sizeof(Node_Alimento));
	head->alimento = &buffer_alimento[0];
	head->next = NULL;

	Node_Alimento* tail = head;

	// liga o resto dos alimentos na lista
	for (unsigned int i = 1; i < total; i++) {
		tail = inserir_node(tail, &buffer_alimento[i]);
	}


	//inicio da lista encadeada das categorias
	Node_Categoria* head_categoria = (Node_Categoria*)malloc(sizeof(Node_Categoria));
	strcpy(head_categoria->nome, nome_categorias[0]);
	head_categoria->alimentos = criar_lista_alimento(nome_categorias[0], head);
	head_categoria->next = NULL;
	head_categoria->id = Alimentos_preparados;

	Node_Alimento* tail_alimento  = head_categoria->alimentos;

	Node_Categoria* tail_categoria = head_categoria;

	// cria as outras categorias, cada uma ja com a sua lista de alimentos
	for (Categoria c = Bebidas; c < MAX_CATEGORIAS; c++) {
		tail_categoria = inserir_node_categoria(tail_categoria, nome_categorias[c], head, c);

	}

	

	static int show = 0;
	static int selected = -1;
	static int modificado = 0; /* vira 1 quando alguma categoria ou alimento e removido */
	// loop do menu; show controla se o menu precisa ser mostrado de novo
	while (1) {

		if (!show) {
			printf("%s\n", "1. Listar Categorias");
			printf("%s\n", "2. Listar elementos da categoria");
			printf("%s\n", "3. Listar elementos por energia da categoria");
			printf("%s\n", "4. Listar elementos por proteina da categoria");
			printf("%s\n", "5. Listar elementos por energia da categoria entre 100 e 300 kcal");
			printf("%s\n", "6. Listar elementos por proteina da categoria entre 6 e 10 gramas");
			printf("%s\n", "7. Remover uma categoria");
			printf("%s\n", "8. Remover um alimento");
			printf("%s\n", "9. Encerrar o programa");


			show = 1;
		}

		scanf("%d", &selected);



		if (selected == 1) { // listar categorias
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf(" %s\n", "Digite 0 para voltar");




		}
		else if(selected == 2) { // listar os alimentos da categoria escolhida
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");




					// procura a categoria pelo id (o menu comeca em 1, o id em 0)
					Node_Categoria* atual = head_categoria;
					n--;
					while (atual) {

						if (atual->id == n) {
							printf("----%s\n", atual->nome);
							Node_Alimento* alimento = atual->alimentos;
							while (alimento) {
								printf("%s\n", alimento->alimento->desc);

								alimento = alimento->next;
							}


						}

						atual = atual->next;


			}





		}

		else if (selected == 3) { // ordenar por energia usando a arvore
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");




			Node_Categoria* atual = head_categoria;
			n--;
			while (atual) {

				if (atual->id == n) {
					printf("----%s\n", atual->nome);

					Node_Tree* root = criar_arvore_energia(atual);
					percorrer_energia(root, NORMAL);



				}

				atual = atual->next;


			}





		}

		else if (selected == 4) { // ordenar por proteina usando a arvore
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");




			Node_Categoria* atual = head_categoria;
			n--;
			while (atual) {

				if (atual->id == n) {
					printf("----%s\n", atual->nome);

					Node_Tree* root = criar_arvore_proteina(atual);
					percorrer_proteina(root, NORMAL);



				}

				atual = atual->next;


			}





		}

		else if (selected == 5) { // energia entre 100 e 300 kcal
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");




			Node_Categoria* atual = head_categoria;
			n--;
			while (atual) {

				if (atual->id == n) {
					printf("----%s\n", atual->nome);

					Node_Tree* root = criar_arvore_energia(atual);
					percorrer_energia(root, MIN_MAX);



				}

				atual = atual->next;


			}





			}

		else if (selected == 6) { // proteina entre 6 e 10 g
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");




			Node_Categoria* atual = head_categoria;
			n--;
			while (atual) {

				if (atual->id == n) {
					printf("----%s\n", atual->nome);

					Node_Tree* root = criar_arvore_proteina(atual);
					percorrer_proteina(root, MIN_MAX);



				}

				atual = atual->next;


			}





			}

		else if (selected == 7) { // remover categoria
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria que deseja remover:");
			int n;
			scanf("%d", &n);
			system("cls");

			if (remover_categoria(&head_categoria, n)) {
				modificado = 1;
				printf("%s\n", "Categoria removida.");
			}
			else printf("%s\n", "Categoria não encontrada.");

			printf(" %s\n", "Digite 0 para voltar");

		}

		else if (selected == 8) { // remover alimento
			selected = -1;
			system("cls");
			imprimir_categorias(head_categoria);
			printf("%s", "Digite o número da categoria:");
			int n;
			scanf("%d", &n);
			system("cls");

			imprimir_alimentos_numero(head_categoria, n);
			printf("%s", "Digite o número do alimento que deseja remover:");
			unsigned int numero;
			scanf("%u", &numero);
			system("cls");

			/* as arvores sao criadas de novo a partir da lista em toda consulta
			   (opcoes 3 a 6), entao depois da remocao elas ja saem atualizadas */
			if (remover_alimento(head_categoria, n, numero)) {
				modificado = 1;
				printf("%s\n", "Alimento removido.");
			}
			else printf("%s\n", "Alimento não encontrado.");

			printf(" %s\n", "Digite 0 para voltar");

		}

		else if (selected == 9) { // encerrar

			// so gera um novo dados.bin se algo foi removido
			if (modificado) {
				int gravados = salvar_dados(head_categoria, "dados.bin");
				if (gravados < 0) printf("%s\n", "Erro ao gravar dados.bin");
				else printf("dados.bin atualizado (%d alimentos).\n", gravados);
			}

			free(buffer_alimento);
			return 0;
		}

		// 0 volta para o menu
		if (selected == 0 && show) {
			show = 0;
			system("cls");

		}




	}







	



}
