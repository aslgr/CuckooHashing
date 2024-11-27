#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void adiciona_em_ordem(int key_keeper[], int *size, int chave)
{
    int i = 0;
    int j = *size;

    while (i < *size && chave > key_keeper[i])
        i++;

    while (j > i)
    {
        key_keeper[j] = key_keeper[j-1];
        j--;
    }

    key_keeper[i] = chave;
    (*size)++;
}

void retira_em_ordem(int key_keeper[], int *size, int chave)
{
    int i = 0;
    int j = *size;

    while (chave != key_keeper[i])
        i++;

    while (i < j)
    {
        key_keeper[i] = key_keeper[i+1];
        i++;
    }

    (*size)--;
}

int main()
{
    hashtable *ht;
    if ((ht = cria_hashtable()) == NULL)
    {
        printf("Nao foi possivel criar o hashtable.\n");
        return 0;
    }

    posicao_ht *posicao;

    char *file_line = NULL;
    size_t line_size = 0;
    ssize_t read;

    int i, chave, size = 0;
    int key_keeper[2 * SIZE];

    char operacao;
    char *chave_str;

    while ((read = getline(&file_line, &line_size, stdin)) != -1)
    {
        if ((chave_str = (char*) malloc ((LINE_SIZE-1) * sizeof(char))) == NULL)
        {
            printf("Nao foi possivel alocar a string da chave.\n");
            return 0;
        }

        operacao = file_line[0];

        for (i = 0; i < strlen(file_line)-3; i++)
            chave_str[i] = file_line[i+2];

        chave = atoi(chave_str);

        switch (operacao)
        {
            case ('i') :

                if (insereHash(ht, chave))
                    adiciona_em_ordem(key_keeper, &size, chave);

            break;

            case ('r') :

                if (excluiHash(ht, chave))
                    retira_em_ordem(key_keeper, &size, chave);

            break;
        }

        free(chave_str);
    }

    for (i = 0; i < size; i++)
    {
        if ((posicao = buscaHash(ht, key_keeper[i])) != NULL)
        {
            if (posicao->tabela == 1)
                printf("%d,T1,%d\n", key_keeper[i], posicao->indice);

            else if (posicao->tabela == 2)
                printf("%d,T2,%d\n", key_keeper[i], posicao->indice);

            free(posicao);
        }
    }
    
    free(file_line);
    destroi_hashtable(ht);

    return 0;
}