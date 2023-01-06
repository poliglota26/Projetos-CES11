/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 7: PERT
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Dezembro de 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vertice
{
    char rotulo;
    int predecessor;
    char descricao [40];
    int duracao;
};

int matriz[55][55]; //Matriz que armazenara o grafo
vertice noh[55];
int ini_ciclo; // guarda o inicio do ciclo se houver
int quant;
bool ciclo; // verifica se ha ou nao ciclo
bool descoberto[55];
bool visitado[55];
char guarda_ciclo[60];
char ordenacao_topologica[60];
int num;
int tempo_minimo;
int TMT[55]; // tempo minimo para termino
FILE * ent,
     * sai;
// reinicia descoberto e visitado como falso
void reseta()
{
    for(int i = 1; i <= quant; i++)
    {
        descoberto[i] = false;
        visitado[i] = false;
    }
}
// busca posicao que esta no vetor noh
int Busca (char L)
{
    for(int a = 1; a<=quant; a++)
    {
        if(noh[a].rotulo == L)
            return a;
    }
    return -1;
}
// busca em profundidade para verificar se ha ciclo
void DFS_Ciclo(int x)
{
    descoberto[x] = true;
    for(int i = 1; i <= quant && !ciclo; i++)
    {
        if(matriz[x][i] == 1)
        {
            noh[i].predecessor = x;
            if(!descoberto[i])
                DFS_Ciclo(i);

            else if (!visitado[i])
            {
                ini_ciclo = i;
                ciclo = true;
            }
        }
    }
    visitado[x] = true;
}

void Percorrer_Ciclo()
{
    ciclo = false;
    reseta();

    for(int i = 1; i <= quant && !ciclo; i++)
    {
        if(!descoberto[i])
        {
            noh[i].predecessor = -1;
            DFS_Ciclo(i);
        }
    }
}
// busca em profundidade para encontrar ordenacao topologica
void DFS_Ordenacao(int x)
{
    descoberto[x] = true;
    for(int i = 1; i <= quant; i++)
    {
        if(matriz[x][i] == 1)
            if(!descoberto[i])
                DFS_Ordenacao(i);
    }
    ordenacao_topologica[num] = noh[x].rotulo;
    num++;
}

void Percorrer_Ordenacao()
{
    reseta();
    for(int i = 1; i <= quant; i++)
    {
        if(!descoberto[i])
            DFS_Ordenacao(i);
    }
}
// encontrar o tempo minimo para termino de uma tarefa
void Tempo_Minimo_Termino()
{
    for(int a = quant-1; a>=0; a--)
    {
        int p = Busca(ordenacao_topologica[a]);
        TMT[p] = noh[p].duracao;
        noh[p].predecessor = -1;
        for(int i = 1; i <= quant; i++)
        {
            if(matriz[i][p] == 1)
            {
                if(TMT[p]<TMT[i] + noh[p].duracao)
                {
                    TMT[p] = TMT[i] + noh[p].duracao;
                    noh[p].predecessor = i;
                }
            }
        }
    }
}
// encontrar caminho critico
void Caminho_Critico(int n)
{
    int pred = noh[n].predecessor;
    if (pred != -1)
        Caminho_Critico(pred);
    fprintf(sai,"  %c   %s %2d\n", noh[n].rotulo, noh[n].descricao, noh[n].duracao);
}

int main()
{
    char linha [80];
    char tarefas_precedentes [120];
    char letra;
    int k = 1;
    int i,j;
    int ultimo_caminho; // onde termina o caminho critico

    ent = fopen("entrada7.txt", "r");
    sai = fopen("Lab7_Sergio_Luis_dos_Santos_Filho.txt", "w");

    // pular 7 linhas iniciais da entrada
    for (int a=1; a<=7; a++)
        fgets (linha, 75, ent);
    fscanf(ent, " %c ", &letra);

    // guardar as informacoes nos vertices
    while(letra != '-')
    {
        noh[k].rotulo = letra;
        fgets(noh[k].descricao,31,ent);
        fscanf(ent, " %d ", &noh[k].duracao);
        fscanf(ent, " %s ", linha);
        fscanf(ent, " %c ", &letra);
        k++;
        quant++;
    }
    fclose(ent);

    ent = fopen("entrada7.txt", "r");
    // pular 7 linhas iniciais da entrada
    for (int a=1; a<=7; a++)
        fgets (linha, 75, ent);
    fscanf(ent, " %c ", &letra);
    k = 1;
    // preencher a matriz
    while(letra != '-')
    {
        fgets(linha,34,ent);
        fscanf(ent, " %s ",tarefas_precedentes);
        i = 0;
        while(tarefas_precedentes[i] != NULL)
        {
            if(tarefas_precedentes[i] != ',' && tarefas_precedentes[i] != '.')
            {
                j = Busca(tarefas_precedentes[i]);
                matriz[j][k] = 1;
            }
            i++;
        }
        fscanf(ent, " %c ", &letra);
        k++;
    }

    // escrever 5 linhas iniciais na saída
    fprintf(sai,"Lab7 - Sergio Luis dos Santos Filho\n");
    fprintf(sai,"PERT/CPM\n");
    fprintf(sai,"Prof. Armando Gouveia\n");
    fprintf(sai,"ITA - Instituto Tecnológico de Aeronáutica\n");
    fprintf(sai,"2º Semestre de 2022 - Turma 02\n");
    fprintf(sai,"------------------------------------------------------------\n\n");

    /// TESTE DE ACICLICIDADE
    // Verificar se ha ciclo no grafo
    Percorrer_Ciclo();
    // Caso tenha ciclo
    if(ciclo)
    {
        fprintf (sai, "Ha ciclo no grafo, logo eh impossivel buscar o caminho critico\n");
        fprintf (sai, "Ciclo: ");
        j = noh[ini_ciclo].predecessor;
        i = 0;
        while(ini_ciclo != j)
        {
            guarda_ciclo[i] = noh[j].rotulo;
            j = noh[j].predecessor;
            i++;
        }
        guarda_ciclo[i] = noh[ini_ciclo].rotulo;
        for(int t = i; t>=0; t--)
            fprintf(sai, "%c ", guarda_ciclo[t]);
        fprintf(sai, "\n");
    }
    // caso nao tenha ciclo
    else
    {
        /// Ordenacao Topologica
        fprintf(sai,"UMA ORDENACAO TOPOLOGICA:\n\n");
        Percorrer_Ordenacao();
        for(int a = quant-1; a>=0; a--)
            fprintf(sai, "%c ", ordenacao_topologica[a]);
        fprintf(sai,"\n\n");

        /// Caminho Critico
        Tempo_Minimo_Termino();
        ultimo_caminho = -1;
        for(int a = 1; a<=quant; a++)
        {
            if(tempo_minimo < TMT[a])
            {
                tempo_minimo = TMT[a];
                ultimo_caminho = a;
            }
        }
        fprintf(sai,"------------------------------------------------------------\n\n");
        fprintf(sai,"CAMINHO CRITICO:\n\n");
        fprintf(sai,"TAREFA        DESCRICAO           DURACAO\n\n");
        Caminho_Critico(ultimo_caminho);
        fprintf(sai,"                                   ----\n");
        fprintf(sai,"TEMPO MINIMO PARA O PROJETO:         %d semanas\n",tempo_minimo);
    }

    fclose(sai);
    fclose(ent);
    return 0;
}
