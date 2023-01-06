/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 1: Torre de Controle
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Agosto de 2022
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct voo noh;

struct voo
{
    int num_aviao;
    char origem[40];
    bool pediu_urgencia; // Verificar se o aviao pediu urgencia
    noh * prox;
};

int main()
{
    char residuo[80], funcao[25];
    int i, num_urgencia;
    bool achou_voo;
    FILE * entrada,
         * saida;
    noh * inicio;
    noh * p;
    noh * ultimo;
    noh * ant;
    noh * q;
    noh * q_ant;
    // lista inicialmente vazia
    inicio = NULL;
    entrada = fopen("entrada1.txt", "r");
    saida = fopen("Lab1_Sergio_Luis_dos_Santos_Filho.txt", "w");
    // Pular primeiras 8 linhas do arquivo de entrada
    for(i = 0; i < 8; i++)
        fgets(residuo, 75, entrada);
    fscanf(entrada, " %s ", funcao);
    // Inicio do arquivo de saida
    fprintf(saida, "Aeroporto de Sao Jose dos Campos\n");
    fprintf(saida, "DCTA - ITA\n");
    fprintf(saida, "AUTORIZACOES DE POUSO\n");
    fprintf(saida, "=========================================\n");
    fprintf(saida, "FLIGHT  FROM\n\n");
    while(strcmp(funcao,"FIM") != 0)
    {
        // Se o aviao pede para pousar
        if (strcmp(funcao,"pede_pouso") == 0)
        {
            // inserir elemento se a lista estiver vazia
            if (inicio == NULL)
            {
                inicio = (noh *) malloc (sizeof(noh));
                fscanf(entrada, " %d ", &inicio->num_aviao);
                fgets(inicio->origem, 31, entrada);
                inicio->prox = NULL;
                inicio->pediu_urgencia = false;
            }
            // inserir elemento na lista nao vazia
            else
            {
                p = (noh*) malloc (sizeof(noh));
                fscanf(entrada, " %d ", &p->num_aviao);
                fgets(p->origem, 31, entrada);
                // inserir no final da lista
                ultimo = inicio;
                while (ultimo->prox != NULL)
                    ultimo = ultimo->prox;
                ultimo->prox = p;
                p->prox = NULL;
                p->pediu_urgencia = false;
            }
        }
        // Se a pista for liberada
        else if (strcmp(funcao, "pista_liberada") == 0)
        {
            fgets(residuo, 75, entrada);
            if (inicio == NULL)
                fprintf(saida, "0000    Nenhum aviao pousando\n");
            else
            {
                fprintf(saida, "%04d    %s", inicio->num_aviao, inicio->origem);
                p = inicio;
                inicio = inicio->prox;
                // Apagar dados do voo
                free(p);
            }
        }

        // Se o aviao pedir urgencia
        else if (strcmp(funcao, "URGENCIA") == 0)
        {
            fscanf(entrada, " %d ", &num_urgencia);
            fgets(residuo, 75, entrada);
            p = inicio;
            achou_voo = false;
            while(!achou_voo)
            {
                if(num_urgencia == p->num_aviao)
                    achou_voo = true;
                else
                {
                    ant = p;
                    p = p->prox;
                }
            }
            q = inicio;
            while(q->pediu_urgencia)
            {
                q_ant = q;
                q = q->prox;
            }
            if (p != inicio)
            {
                ant->prox = p->prox;
                p->prox = q;
                if(q != inicio)
                    q_ant->prox = p;
                else
                    inicio = p;
            }
            p->pediu_urgencia = true;
        }
        fscanf(entrada, " %s ", funcao);
    }
    fprintf(saida, "\nSituacao da fila\n\n");
    // Se no final nao houver nenhum aviao voando
    if (inicio == NULL)
        fprintf(saida, "Todos os avioes pousaram\n");
    // Printar no arquivo de saida quais sao os avioes que estao voando no final, se houver
    while (inicio != NULL)
    {
        fprintf(saida, "%04d    %s", inicio->num_aviao, inicio->origem);
        inicio = inicio->prox;
    }
    fclose(entrada);
    fclose(saida);
    return 0;
}
