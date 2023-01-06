/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 4: Agenda Eletrônica
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Outubro de 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados dados;
typedef struct fila fila;

// struct onde serao guardados os dados de cada evento
struct dados
{
    int imp;       // importancia do elemento
    char desc[50]; // descrição do elemento
};

struct fila
{
    dados * vet;
    int inicio,   // posição do início
        fim,      // posição do fim
        quant,    // quantidade de elementos
        quantMax; // quantidade máxima possível de elementos
};

/// Funções do TAD:

/// Inicializar
void Inicializar(fila * L, int num)
{
    L->quantMax = num;
    L->vet = (dados *) malloc ((L->quantMax) * (sizeof(dados)));
    L->inicio = 0;
    L->fim = (L->quantMax)-1;
    L->quant = 0;
}

/// Finalizar
void Finalizar(fila * L)
{
    free(L->vet);
}

/// Maximum (Retorna qual é o elemento com maior prioridade)
dados Maximum(fila L)
{
    return (L.vet[L.inicio]);
}

/// RemoveMax (Remove elemento com maior prioridade)
void RemoveMax (fila * L)
{
    L->inicio = ((L->inicio)+1)%(L->quantMax);
    L->quant = (L->quant) - 1;
}

/// FilaVazia (Verifica se a fila está vazia)
bool FilaVazia (fila L)
{
    if(L.quant == 0)
        return true;
    return false;
}

/// FilaCheia (Verifica se a fila está cheia)
bool FilaCheia (fila L)
{
    if(L.quant == L.quantMax)
        return true;
    return false;
}

/// Insert: (Inserir elemento na fila - obedecendo a ordem de prioridade)
void Insert(dados X, fila * L)
{
    int med, i;

    if (L->quant == 0)
    {
        L->fim = (L->fim +1)% (L->quantMax);
        L->vet[L->fim] = X;
    }

    else
    {
        // valor medio
        med = (L->inicio + L->quant/2)%L->quantMax;
        if(L->vet[med].imp > X.imp)
        {
            for(i = L->fim; X.imp > L->vet[i].imp; i = (i-1+L->quantMax)% L->quantMax)
                L->vet[(i+1) % L->quantMax] = L->vet[i];
            i = (i + 1)%L->quantMax;
            L->fim = (L->fim + 1)%L->quantMax;
        }
        else
        {
            for(i = L->inicio; X.imp < L->vet[i].imp; i = (i+1)% L->quantMax)
                L->vet[(i-1+L->quantMax)%L->quantMax] = L->vet[i];
            i = (i - 1 + L->quantMax)%L->quantMax;
            L->inicio = (L->inicio - 1 + L->quantMax)%L->quantMax;
        }
        L->vet[i] = X;
    }

    // soma um a quantidade de elementos na fila
    L->quant = (L->quant) + 1;
}

int main()
{
    char lixo[80], funcao[10];
    fila L;
    dados X;
    int num;
    FILE * entrada,
         * saida;

    entrada = fopen("entrada4.txt","r");
    saida = fopen("Lab4_Sergio_Luis_dos_Santos_Filho.txt","w");

    for(int i = 0; i < 5; i++)
        fgets(lixo, 75, entrada);

    // ler quantidade maxima
    fscanf(entrada, " %d ", &num);
    // inicializa fila
    Inicializar(&L, num);

    for(int i = 0; i < 3; i++)
        fgets(lixo, 75, entrada);

    fprintf(saida,"Lab4 - Sergio Luis dos Santos Filho\n");
    fprintf(saida,"Agenda Eletronica\n");
    fprintf(saida,"Prof. Armando Gouveia\n");
    fprintf(saida,"ITA - Instituto Tecnológico de Aeronáutica\n");
    fprintf(saida,"2º Semestre de 2022 - Turma 02\n");
    fprintf(saida,"--------------------------------------------------\n");
    fprintf(saida,"RESPOSTAS DAS CONSULTAS\n");
    fprintf(saida,"--------------------------------------------------\n");
    // ler qual a funçao que sera desempenhada
    fscanf(entrada, " %s ", funcao);
    // enquanto nao terminar as funcoes
    while(strcmp(funcao, "FIM") != 0)
    {
        // se for adicionar um novo elemento a fila
        if(strcmp(funcao, "NOVA") == 0)
        {
            fscanf(entrada, " %d ", &X.imp);
            fgets(X.desc, 45, entrada);
            // se fila esta cheia avisa
            if(FilaCheia(L))
                fprintf(saida, "ERRO     Agenda cheia. Impossivel inserir.\n");
            // senao, insere elemento na lista
            else
                Insert(X, &L);
        }
        // se perguntar qual eh o proximo elemento
        else if(strcmp(funcao, "PROXIMA") == 0)
        {
            // se fila esta vazia avisa
            if(FilaVazia(L))
                fprintf(saida, "AVISO    Nao ha tarefas na agenda  :-)\n");
            // senao, diga qual eh o elemento de maior prioridade e tire-o da fila
            else
            {
                X = Maximum(L);
                fprintf(saida, "%2d       %s", X.imp, X.desc);
                RemoveMax(&L);
            }
        }
        // ler qual a funçao que sera desempenhada
        fscanf(entrada, " %s ", funcao);
    }
    // dizer as tarefas para o dia seguinte
    fprintf(saida, "\n--------------------------------------------------\n");
    fprintf(saida, "FICA PARA O DIA SEGUINTE\n");
    fprintf(saida, "--------------------------------------------------\n");
    // se a fila esta vazia nao tem tarefa para o dia seguinte
    if(FilaVazia(L))
        fprintf(saida, "Agenda vazia! Nao restam tarefas para o dia seguinte.\n");
    // se a fila nao estiver vazia dizer as tarefas que sobraram em ordem decrescente de prioridade
    else
    {
        while(!FilaVazia(L))
        {
            X = Maximum(L);
            fprintf(saida, "%2d       %s", X.imp, X.desc);
            RemoveMax(&L);
        }
    }

    // finalizar fila
    Finalizar(&L);
    fclose(entrada);
    fclose(saida);

    return 0;
}
