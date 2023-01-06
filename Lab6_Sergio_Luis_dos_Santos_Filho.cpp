/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 6: Agenda Eletrônica
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Novembro de 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoTarefa TipoTarefa;
typedef struct TipoAgenda TipoAgenda;

/*--------------------------------------------------*/
struct TipoTarefa
{
    char descricao [42];
    int  prioridade;
};
/*--------------------------------------------------*/
// TAD fila de prioridade
struct TipoAgenda
{
    TipoTarefa * vet;  // o vetor
    int quant,         // quantidade de elementos
        MAX;           // quantidade máxima possível de elementos (será lida do arquivo de entrada)
};
/*--------------------------------------------------*/

/// Funções do TAD:

/// Inicializar
void Inicializar(TipoAgenda * H, int num)
{
    H->vet = (TipoTarefa*) malloc ((num+1)*sizeof(TipoTarefa));
    H->quant = 0;
    H->MAX = num;
}

/// Finalizar
void Finalizar(TipoAgenda * H)
{
    free(H->vet);
}

/// Maximum (Retorna qual é o elemento com maior prioridade)
TipoTarefa Max(TipoAgenda H)
{
    return H.vet[1];
}

/// HeapVazia (Verifica se a fila está vazia)
bool HeapVazia (TipoAgenda H)
{
    if (H.quant == 0)
        return true;
    return false;
}

/// HeapCheia (Verifica se a fila está cheia)
bool HeapCheia (TipoAgenda H)
{
    if (H.quant == H.MAX)
        return true;
    return false;
}

/// Insert: (Inserir elemento no heap - obedecendo a ordem de prioridade)
void Insert(TipoAgenda * H, TipoTarefa X)
{
    int i;
    H->quant ++;
    H->vet[H->quant] = X;
    i = H->quant;
    while(i!=1 && H->vet[i/2].prioridade < X.prioridade)
    {
        TipoTarefa aux  = H->vet[i/2];
        H->vet[i/2] = H->vet[i];
        H->vet[i] = aux;
        i = i/2;
    }
}

/// RemoveMax (Remove elemento com maior prioridade)
void RemoveMax (TipoAgenda * H)
{
    int pai, esq, dir, i;
    int maior;
    // Coloca o ultimo elemento na primeira posicao
    H->vet[1] = H->vet[H->quant];
    // Diminui 1 na quantidade de elementos
    H->quant --;
    pai = 0;
    i = 1;
    while(pai!=i && 2*i <= H->quant)
    {
        pai = i;
        esq = 2*i;
        dir = 2*i +1;
        if(dir <= H->MAX)
        {
            if(H->vet[esq].prioridade > H->vet[dir].prioridade)
                maior = esq;
            else maior = dir;

            if(H->vet[pai].prioridade < H->vet[maior].prioridade)
            {
                TipoTarefa aux = H->vet[pai];
                H->vet[pai] = H->vet[maior];
                H->vet[maior] = aux;
                i = maior;
            }
        }
        else
        {
            maior = esq;
            if(H->vet[pai].prioridade < H->vet[maior].prioridade)
            {
                TipoTarefa aux = H->vet[pai];
                H->vet[pai] = H->vet[maior];
                H->vet[maior] = aux;
                i = maior;
            }
        }
    }
}

int main()
{
    FILE * ent;           // arquivo de entrada
    FILE * sai;           // arquivo de saída
    TipoAgenda A;         // Agenda = fila de prioridade
    TipoTarefa T;         // Cada tarefa na agenda
    int  i;
    int  tamanho_max;     // tamanho maximo da agenda
    char comando [8];     // NOVA, PROXIMA ou FIM
    char linha  [72];     // para pular linhas do cabecalho

    // abrir arquivos
    ent = fopen ("entrada6.txt", "r");
    sai = fopen ("Lab6_Sergio_Luis_dos_Santos_Filho.txt", "w");
    // pular 5 linhas iniciais da entrada
    for (i=1; i<=5; i++)
        fgets (linha, 72, ent);
    // ler tamanho maximo e inicializar agenda
    fscanf (ent, "%d", & tamanho_max);
    Inicializar   (&A,   tamanho_max);
    // pular mais 3 linhas da entrada
    for (i=1; i<=3; i++)
        fgets (linha, 72, ent);
    // escrever 5 linhas iniciais na saída
    fprintf(sai,"Lab6 - Sergio Luis dos Santos Filho\n");
    fprintf(sai,"Agenda Eletronica\n");
    fprintf(sai,"Prof. Armando Gouveia\n");
    fprintf(sai,"ITA - Instituto Tecnológico de Aeronáutica\n");
    fprintf(sai,"2º Semestre de 2022 - Turma 02\n");
    fprintf(sai,"--------------------------------------------------\n");
    fprintf(sai,"RESPOSTAS DAS CONSULTAS\n");
    fprintf(sai,"--------------------------------------------------\n");
    // Processar cada linha da entrada
    do
    {
        fscanf (ent, " %s ", & comando);
        // comando para Inserir
        if (strcmp (comando, "NOVA")==0)
        {
            fscanf (ent, " %d ", & T.prioridade);
            fgets  (T.descricao, 72, ent);
            if (HeapCheia (A))
                fprintf(sai, "ERRO     Agenda cheia. Impossivel inserir. \n");
            else Insert (&A, T);
        }
        // comando para Remover
        if (strcmp (comando, "PROXIMA")==0)
            if (HeapVazia (A))
                fprintf(sai, "AVISO    Nao ha tarefas na agenda  :-) \n");
            else
            {
                T = Max (A);
                fprintf(sai, "%2d       %s", T.prioridade, T.descricao);
                RemoveMax (&A);
            }
        // até chegar comando "FIM"
    }
    while (strcmp (comando, "FIM")!=0);
    // Desfazer a fila e imprimir todas as tarefas remanescentes
    fprintf(sai,"\n--------------------------------------------------\n");
    fprintf(sai,  "FICA PARA O DIA SEGUINTE                          \n");
    fprintf(sai,  "--------------------------------------------------\n");
    while (! HeapVazia (A))
    {
        T = Max (A);
        fprintf(sai, "%2d       %s", T.prioridade, T.descricao);
        RemoveMax (&A);
    }
    // Procedimentos finais
    Finalizar (&A);
    fclose (ent);
    fclose (sai);
    return 0;
}
