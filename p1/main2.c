
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct { unsigned int numero; char desc[64]; unsigned int energia; float proteina; char categoria[64]; }Alimento;

Alimento* lista;
int main(int argc, char* argv[]){


FILE* file = fopen("dados.bin", "rb");
int size = 0;
int total = 0;

do
{
    total+=size;
    lista = realloc(lista, sizeof(Alimento) * (total + 1));

}
while((size = fread(&lista[total], sizeof(Alimento), 1, file))>0);

for (unsigned int i = 0; i < total; i++){

    printf("%s\n", lista[i].categoria);
}



return 0;
}
