/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 5: Índice de Livro
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Novembro de 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct noh noh;
typedef char [30];
FILE * entrada,
     * saida;
int v[10];
int k=0;

// noh da árvore
struct noh
{
    char info [35];
    noh * pai,
        * fesq,
        * idir;
};

noh * raiz;

// procura elemento na arvore e retorna ponteiro para ele
noh * Busca(tipelemento info, noh * X)
{
    noh * p;
    noh * resposta;

    if (X == NULL)
        return NULL;

    if(strcmp(X->info, info) == 0)
        return X;

    p = X->fesq;
    resposta = NULL;

    while(p != NULL && resposta == NULL)
    {
        resposta = Busca(info, p);
        p = p->idir;
    }
    return resposta;
}

// visita noh e printa ele
void visita(noh * X)
{
    int j = 1;
    while(j<5 && v[j] != 0)
    {
        fprintf(saida,"%d.", v[j]);
        j++;
    }
    fprintf(saida, "      %s\n", X->info);
}

// faz a visita em PreOrdem
void PreOrdem (noh * X)
{
    noh * p;
    visita(X);
    p = X->fesq;
    k++;
    while(p!=NULL)
    {
        v[k]++;
        PreOrdem(p);
        p = p->idir;
    }
    v[k] = 0;
    k--;
}

// Remove uma subarvore em PosOrdem
void PosOrdem_Remover(noh * X)
{
    /*noh * p;
    noh * q;
    p = X->fesq;
    while(p!=NULL)
    {
        q = p;
        p = p->idir;
        PosOrdem_Remover(q);
    }

    X->fesq = NULL;
    X->idir = NULL;
    X = NULL;
    free(X);*/
    noh *p;
    noh *q;
    p = X->fesq;
    q = X->idir;

    if(p!=NULL)
        PosOrdem_Remover(p);
    if(q!=NULL)
        PosOrdem_Remover(q);
    X = NULL;
    free(X);
}

int main()
{
    char lixo[80];
    char funcao[15]; // funcao utilizada
    char info[25];   // informacao 1
    char info_2[25]; // informacao 2
    char ins [15];   // instrucao
    int cont_lista = 0;
    noh * p;
    noh * q;
    raiz = NULL;

    entrada = fopen("entrada5.txt","r");
    saida = fopen("Lab5_Sergio_Luis_dos_Santos_Filho.txt","w");

    for(int i = 0; i < 4; i++)
        fgets(lixo,75,entrada);

    fprintf(saida,"Lab5 - Sergio Luis dos Santos Filho\n");
    fprintf(saida,"Índice de Livro\n");
    fprintf(saida,"ITA - Instituto Tecnológico de Aeronáutica\n");
    fprintf(saida,"--------------------------------------------------\n");

    fscanf(entrada, " %s ", funcao);

    // enquanto nao chegar ao fim
    while(strcmp(funcao, "FIM") != 0)
    {
        // se for para adicionar titulo
        if(strcmp(funcao, "TITULO") == 0)
        {
            fscanf(entrada," %s ", info);
            p = (noh*) malloc (sizeof(noh));
            p->fesq = raiz;
            if (raiz != NULL)
                raiz->pai = p;
            raiz = p;
            raiz->idir = NULL;
            raiz->pai = NULL;
            strcpy(raiz->info, info);
        }

        // se for inserir um elemento

        else if(strcmp(funcao, "INSERIR") == 0)
        {
            fscanf(entrada, " %s ", info);
            fscanf(entrada, " %s ", ins);
            fscanf(entrada, " %s ", info_2);

            p = Busca(info_2, raiz);

            if(p == NULL)
            {
                fprintf(saida, "ERRO: nao encontrado item %s\n", info_2);
                fprintf(saida, "--------------------------------------------------\n");
            }

            else
            {
                q = (noh*) malloc (sizeof(noh));
                strcpy(q->info, info);
                if (strcmp(ins, "SUB") == 0)
                {
                    q->idir = p->fesq;
                    p->fesq = q;
                    q->pai = p;
                    q->fesq = NULL;
                }

                else if(strcmp(ins, "SEGUINTE_A") == 0)
                {
                    if (p == raiz)
                    {
                        fprintf(saida, "OPERACAO INVALIDA\n");
                        fprintf(saida, "--------------------------------------------------\n");
                    }
                    else
                    {
                        q->idir = p->idir;
                        q->pai = p->pai;
                        p->idir = q;
                        q->fesq = NULL;
                    }

                }
            }

        }

        // se pedir para dizer toda lista
        else if(strcmp(funcao, "LISTA") == 0)
        {
            cont_lista++;
            fprintf(saida, "LISTA %d\n\n", cont_lista);
            if (raiz != NULL)
                PreOrdem(raiz);
            fprintf(saida, "--------------------------------------------------\n");
        }
        // remover uma subarvore
        else if(strcmp(funcao, "REMOVER") == 0)
        {
            fscanf(entrada," %s ", info);

            p = Busca(info,raiz);
            if(p == NULL)
            {
                fprintf(saida, "ERRO: nao encontrado item %s\n", info);
                fprintf(saida, "--------------------------------------------------\n");
            }
            else
            {
                if(p != raiz)
                {
                    q = p->pai->fesq;
                    if(q == p)
                    {
                        p->pai->fesq = p->idir;
                    }

                    else
                    {
                        while(q->idir != p)
                            q = q->idir;
                        q->idir = p->idir;
                    }
                    PosOrdem_Remover(p);
                }

                else
                {
                    PosOrdem_Remover(p);
                    raiz = NULL;
                }


            }

        }
        // transferir uma subarvore de um lugar para outro
        else if(strcmp(funcao, "TRANSFERIR") == 0)
        {
            fscanf(entrada, " %s ", info);
            fscanf(entrada, " %s ", ins);
            fscanf(entrada, " %s ", info_2);

            p = Busca(info, raiz);
            q = Busca(info_2, raiz);

            if(p == NULL)
            {
                fprintf(saida, "ERRO: nao encontrado item %s\n", info);
                fprintf(saida, "--------------------------------------------------\n");
            }
            else if(q == NULL)
            {
                fprintf(saida, "ERRO: nao encontrado item %s\n", info_2);
                fprintf(saida, "--------------------------------------------------\n");
            }

            else
            {
                // retirar conexoes do noh p
                noh * m;
                m = p->pai->fesq;
                if(m == p)
                    p->pai->fesq = p->idir;

                else
                {
                    while(m->idir != p)
                        m = m->idir;
                    m->idir = p->idir;
                }


                if (strcmp(ins, "SUB") == 0)
                {
                    p->idir = q->fesq;
                    q->fesq = p;
                    p->pai = q;
                }
                else if(strcmp(ins, "SEGUINTE_A") == 0)
                {
                    if (p == raiz)
                    {
                        fprintf(saida, "OPERACAO INVALIDA\n");
                        fprintf(saida, "--------------------------------------------------\n");
                    }
                    else
                    {
                        p->idir = q->idir;
                        q->idir = p;
                        p->pai = q->pai;
                    }

                }
            }

        }
        fscanf(entrada, " %s ", funcao);
    }

    return 0;
}
