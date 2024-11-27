#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

int hashcode1(int chave)
{
    return (chave % SIZE);
}

int hashcode2(int chave)
{
    return (SIZE*(chave*0.9 - floor(chave*0.9)));
}

hashtable *cria_hashtable()
{
    int i;
    hashtable *ht;
    if ((ht = (hashtable*) malloc (sizeof(hashtable))) == NULL)
        return NULL;

    for (i = 0; i < SIZE; i++)
    {
        ht->T1[i] = NULL;
        ht->T2[i] = NULL;
    }

    return ht;
}

item *inicia_posicao(int chave)
{
    item *aux;
    if ((aux = (item*) malloc (sizeof(item))) == NULL)
        return NULL;

    aux->chave = chave;
    aux->excluido = 0;

    return aux;
}

posicao_ht *buscaHash(hashtable *ht, int chave)
{
    posicao_ht *p;
    if ((p = (posicao_ht*) malloc (sizeof(posicao_ht))) == NULL)
        return NULL;
    
    int index = hashcode1(chave);
    p->tabela = 1;

    if (ht->T1[index] == NULL){
        free(p);
        return NULL;
    }
    else if (ht->T1[index]->excluido || ht->T1[index]->chave != chave)
    {
        index = hashcode2(chave);
        p->tabela = 2;

        if (ht->T2[index] == NULL || ht->T2[index]->chave != chave){
            free(p);
            return NULL;
        }
    }

    p->indice = index;

    return p;
}

int insereHash(hashtable *ht, int chave)
{
    int index = hashcode1(chave);

    if (ht->T1[index] == NULL){
        ht->T1[index] = inicia_posicao(chave);
    }
    else if (ht->T1[index]->excluido){
        ht->T1[index]->chave = chave;
        ht->T1[index]->excluido = 0;
    }
    else
    {
        if (chave == ht->T1[index]->chave)
            return 0;
        
        int chave_T2 = ht->T1[index]->chave;
        int index_aux = hashcode2(chave_T2);

        if (ht->T2[index_aux] == NULL){
            ht->T2[index_aux] = inicia_posicao(chave_T2);
            ht->T1[index]->chave = chave;
        } else return 0;
    }

    return 1;
}

int excluiHash(hashtable *ht, int chave)
{
    int index = hashcode2(chave);

    if (ht->T2[index] != NULL){
        ht->T2[index] = NULL;
    }
    else
    {
        index = hashcode1(chave);

        if (ht->T1[index] != NULL && !ht->T1[index]->excluido){
            ht->T1[index]->excluido = 1;
        } else return 0;
    }

    return 1;
}

hashtable *destroi_hashtable(hashtable *ht)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        if (ht->T1[i] != NULL)
            free(ht->T1[i]);
        
        if (ht->T2[i] != NULL)
            free(ht->T2[i]);
    }

    free(ht);

    return NULL;
}
