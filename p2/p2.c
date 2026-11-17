#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct { unsigned int numero; char desc[128]; unsigned int energia; float proteina; char categoria[64]; }Alimento;
typedef struct Node_Alimento { Alimento* alimento; struct Node_Alimento* next; }Node_Alimento;
typedef struct Node_Categoria { char nome[64]; Node_Alimento* alimentos; struct Node_Categoria* next;} Node_Categoria;
typedef struct vector { void* data; int n;}vector;
typedef struct Node_Tree { Alimento* alimento; struct Node_Tree* left; struct Node_Tree* right;}Node_Tree;

int buffer_size = 600;

vector filtrar_categorias(Node_Alimento* head) {
	void* start = malloc(64);
	vector seens;
	seens.data = start;
	

	Node_Alimento* current = head;
	strcpy(seens.data, current->alimento->categoria);
	seens.n = 1;

	while (current != NULL) {
		int found = 0;
		for (unsigned short i = 0; i < seens.n; i++) {
			if (!strcmp(current->alimento->categoria, (char*)seens.data + i * 64)) {
				found = 1;
				break;
			 }
			
		}
		
		if (!found) {
			seens.n++;
			seens.data = realloc(seens.data, 64 * seens.n);
			strcpy((char*)seens.data + (seens.n - 1) * 64, current->alimento->categoria);
			
		}

		current = current->next;
	}


	return seens;


}

Node_Alimento* inserir_node(Node_Alimento* tail, Alimento* alimento) {
	
	
	Node_Alimento* node = (Node_Alimento*)malloc(sizeof(Node_Alimento));
	node->alimento = alimento;
	node->next = NULL; 

	tail->next = node;

	return node;





}




void order(char* data, int inicio, int fim) {

	if (inicio >= fim)return;

	int menor = inicio;

	for (int i = inicio + 1; i <= fim; i++) {

		char* atual = data + i * 64;
		char* comparado = data + menor * 64;

		if (strcmp(atual, comparado) < 0) {
			menor = i;
		}
	}

	char temp[64];

	strcpy(temp, data + inicio * 64);
	strcpy(data + inicio * 64, data + menor * 64);
	strcpy(data + menor * 64, temp);

	order(data, inicio + 1, fim);
}

Node_Alimento* criar_lista_alimento(char* categoria, Node_Alimento* head) {

	Node_Alimento* atual = head;
	Node_Alimento* tail = NULL;
	Node_Alimento* heads = NULL;
	
	

	while (atual != NULL) {
		if (!tail) {
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

Node_Categoria* inserir_node_categoria(Node_Categoria* tail, char* categoria, Node_Alimento* head) {


	Node_Categoria* node = (Node_Categoria*)malloc(sizeof(Node_Categoria));
	strcpy(node->nome, categoria);
	node->alimentos = criar_lista_alimento(node->nome, head);
	node->next = NULL;

	tail->next = node;

	return node;





}

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

void percorrer_energia(Node_Tree* root) {

    if (root == NULL) return;

    percorrer_energia(root->right);

    printf("%d\n", root->alimento->energia);

    percorrer_energia(root->left);
}

void percorrer_proteina(Node_Tree* root) {

	if (root == NULL) return;

	percorrer_proteina(root->right);

	printf("%.2f\n", root->alimento->proteina);

	percorrer_proteina(root->left);
}

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, ".UTF8");

	FILE* file = fopen("dados.bin", "rb");
	if (file == NULL)return -1;

	unsigned int byte = 0;
	unsigned int total = 0;
	Alimento* buffer_alimento = (Alimento*)malloc(sizeof(Alimento) * buffer_size);

	while ((byte = fread(&buffer_alimento[total], sizeof(Alimento), 1, file)) > 0)total += byte;
	
	Node_Alimento* head = (Node_Alimento*)malloc(sizeof(Node_Alimento));
	head->alimento = &buffer_alimento[0];
	head->next = NULL;

	Node_Alimento* tail = head;

	for (unsigned int i = 1; i < total; i++) {
		tail = inserir_node(tail, &buffer_alimento[i]);
	}

	vector categorias = filtrar_categorias(head);

	order(categorias.data, 0, categorias.n - 1);

	Node_Categoria* head_categoria = (Node_Categoria*)malloc(sizeof(Node_Categoria));
	strcpy(head_categoria->nome, categorias.data);
	head_categoria->alimentos = criar_lista_alimento(head_categoria->nome, head);
	head_categoria->next = NULL;

	Node_Alimento* tail_alimento  = head_categoria->alimentos;

	Node_Categoria* tail_categoria = head_categoria;

	for (unsigned int i = 1; i < categorias.n; i++) {
		tail_categoria = inserir_node_categoria(tail_categoria, (char*)categorias.data + i * 64, head);

	}

	Node_Categoria* al = head_categoria;

	

	while (al != NULL) {

		printf("--------%s\n", al->nome);

		Node_Tree* root = malloc(sizeof(Node_Tree));

		root->alimento = al->alimentos->alimento;
		root->left = NULL;
		root->right = NULL;

		Node_Alimento* atual = al->alimentos->next;

		while (atual != NULL) {

			montar_arvore_energia(atual->alimento, root);

			atual = atual->next;
		}

		//percorrer_energia(root);

		al = al->next;
	}


	Node_Categoria* al2 = head_categoria;

	while (al2 != NULL) {

		printf("--------%s\n", al2->nome);

		Node_Tree* root = malloc(sizeof(Node_Tree));

		root->alimento = al2->alimentos->alimento;
		root->left = NULL;
		root->right = NULL;

		Node_Alimento* atual = al2->alimentos->next;

		while (atual != NULL) {

			montar_arvore_proteina(atual->alimento, root);

			atual = atual->next;
		}

		percorrer_proteina(root);

		al2 = al2->next;
	}


	

}