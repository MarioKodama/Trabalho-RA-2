#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct { unsigned int numero; char desc[128]; unsigned int energia; float proteina; char categoria[64]; }Alimento;

Alimento* lista;
unsigned int capacidade = 100;


int verify(char* atual){
    if (*atual == '\n' || *atual == '\r' || *atual == '\0')return 0;
    if(!strncmp(atual, "Categoria:", 10) || !strncmp(atual, "numero:", 7) || !strncmp(atual, "desc:", 5) || !strncmp(atual, "energia:", 8) || !strncmp(atual, "proteina:", 9))return 0;
    return 1;
}


int parser(FILE* oldFile){

    unsigned int byte = 0;
    unsigned int total = 0;
    char c;
    
    while((byte = fread(&c, 1, 1, oldFile)) > 0)total+=byte;
    rewind(oldFile);
    char* buffer = (char*)malloc(total +1);
    fread(buffer, total, 1, oldFile);
    buffer[total] = '\0';
    int count = 0;
    char categoria[64];
    char numero[16];
    char desc[128];
    char energia[16];
    char proteina[16];
    for(unsigned int i = 0; i < total; i++){
        char* atual = buffer+i;

        if(!strncmp(atual, "Categoria:", 10)){
            i += 10;
            atual+=10;
            int index = 0;
            memset(categoria, 0, sizeof(categoria));
            while(*atual!='\r'){
                categoria[index++] = *atual;
                atual++;
                
                
            }
            i = atual - buffer - 1;


        }

        else if (!strncmp(atual, "numero:", 7)){
            int index = 0;
            atual+=7;
            i += 7;
            memset(numero, 0, sizeof(numero));

            while(verify(atual)){
                numero[index++] = *atual;
                atual++;
                
                
            }
            i = atual - buffer - 1;
        }

         else if (!strncmp(atual, "desc:", 5)){
            int index = 0;
            atual+=5;
            i+=5;
            memset(desc, 0, sizeof(desc));

            while(verify(atual)){
                desc[index] = *atual;
                atual++;
                index++;

            }
            i = atual - buffer - 1;
        }

         else if (!strncmp(atual, "energia:", 8)){
            int index = 0;
            atual+=8;
            i += 8;
            memset(energia, 0, sizeof(energia));

            while(verify(atual)){
                energia[index++] = *atual;
                atual++;
                
            }
            i = atual - buffer - 1;
        }

         else if (!strncmp(atual, "proteina:", 9)){
            int index = 0;
            atual+=9;
            i += 9;
            memset(proteina, 0, sizeof(proteina));

            while(verify(atual)){
                
                proteina[index++] = *atual;
                atual++;
                
            }
            i = atual - buffer - 1;

            Alimento A;
            strcpy(A.categoria, categoria);
            strcpy(A.desc, desc);
            A.numero = atoi(numero);
            A.energia = atoi(energia);
            A.proteina = atof(proteina);
            if (count == capacidade) { capacidade += 100; lista = (Alimento*)realloc(lista, sizeof(Alimento) * capacidade); }

            
            memcpy(&lista[count++], &A, sizeof(Alimento));
            
        }




    }
        

    

return count;
}


int main(int argc, char* argv[]){

    setlocale(LC_ALL, ".UTF8");

    FILE* dados = fopen("dados.txt", "rb");
    if(!dados){printf("%s", "Erro ao abrir arquivo"); return -1;}
    FILE* novos_dados = fopen("dados.bin", "wb");
    if(!novos_dados){printf("%s", "Erro ao criar arquivo bin"); return -1;}
    lista = (Alimento*)malloc(sizeof(Alimento) * capacidade);
    int total_alimentos = parser(dados);
    fwrite(lista, sizeof(Alimento)*total_alimentos, 1, novos_dados);
    
    for(unsigned int i = 0; i < total_alimentos; i++){
        printf("Categoria: %s\n", lista[i].categoria);
        printf("Numero: %d\n", lista[i].numero);
        printf("Descricao: %s\n", lista[i].desc);
        printf("Energia: %d\n", lista[i].energia);
        printf("Proteina: %.2f\n", lista[i].proteina);
        printf("\n");
	}


    free(lista);
    
   



return 0;
}
