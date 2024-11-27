/*header do hashing*/

#define SIZE 11
#define LINE_SIZE 100
#define TABELA1 1
#define TABELA2 2

typedef struct item {
    int chave;
    int excluido;
} item;

typedef struct hashtable {
    item *T1[SIZE];
    item *T2[SIZE];
} hashtable;

typedef struct posicao_ht {
    int indice;
    int tabela;
} posicao_ht;

hashtable *cria_hashtable();

posicao_ht *buscaHash(hashtable *ht, int chave);

int insereHash(hashtable *ht, int chave);

int excluiHash(hashtable *ht, int chave);

hashtable *destroi_hashtable(hashtable *ht);
