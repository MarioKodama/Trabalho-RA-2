#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "arquivo.h"

/* 9. Regrava o arquivo com os alimentos que sobraram em todas as categorias.
   Retorna quantos alimentos foram gravados, ou -1 se nao conseguiu abrir o arquivo. */
int salvar_dados(Node_Categoria* head, const char* nome_arquivo) {

	FILE* file = fopen(nome_arquivo, "wb");
	if (file == NULL) return -1;

	int total = 0;
	Node_Categoria* categoria = head;

	while (categoria) {

		Node_Alimento* alimento = categoria->alimentos;
		while (alimento) {
			fwrite(alimento->alimento, sizeof(Alimento), 1, file);
			total++;
			alimento = alimento->next;
		}

		categoria = categoria->next;
	}

	fclose(file);
	return total;
}
