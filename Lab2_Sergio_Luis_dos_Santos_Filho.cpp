/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 2: Produto de Matrizes
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Setembro de 2022
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int col[25]; // guarda o numero de colunas de dada matriz
int lin[25]; // guarda o numero de linhas de dada matriz
int num_chamadas; // numero de chamadas da funcao m
int melhor[21][21]; // matriz que guarda o melhor corte de cada chamada
int ordem_corte; // ordem do corte
FILE * entrada,
     * saida;

//**************************************
// Funcao que recebe as posições de duas matrizes
// e retorna o minimo de operacoes entre elas
int m(int i, int j)
{
    int valor; // quantidade de operacoes
    int mc; // melhor corte
    int minimo = 0; // menor numero de operacoes
    bool primeiro = true; // caso seja o primeiro
    num_chamadas++;
    // se i = j retorna 0
    if(i == j)
        return 0;

    // se i != j retorna o valor minimo de operacoes
    for(int k = i; k < j; k++)
    {
        valor = m(i,k) + m(k+1,j) + lin[i]*col[k]*col[j];
        if(primeiro || valor < minimo)
        {
            minimo = valor;
            primeiro = false;
            mc = k;
        }
    }
    melhor[i][j] = mc;

    return minimo;
}
//***************************************

//***************************************
// Funcao que recebe as posições de duas matrizes
// e escreve na tela onde é feito o corte na menor operação
void escreve(int i, int j)
{
    if(i != j)
    {
        escreve(i, melhor[i][j]);
        escreve(melhor[i][j] + 1, j);
        if(i == melhor[i][j])
        {
            if(melhor[i][j]+1 == j)
                fprintf(saida, "    %d x  %d \n", i, j);
            else
                fprintf(saida, "    %d x  %d- %d \n", i, melhor[i][j]+1, j);
        }
        else if(j == melhor[i][j] + 1)
            fprintf(saida, " %d- %d x  %d \n", i, melhor[i][j], j);
        else
            fprintf(saida, " %d- %d x  %d- %d \n", i, melhor[i][j], melhor[i][j]+1, j);
    }
}

//***************************************
int main()
{
    char residuo[80];
    int qtd; // quantidade de matrizes
    int num_min; // numero minimo de operacoes

    entrada = fopen("entrada2.txt", "r");
    saida = fopen("Lab2_Sergio_Luis_dos_Santos_Filho.txt", "w");

    // Pular primeiras 5 linhas do arquivo de entrada
    for(int i = 0; i < 5; i++)
        fgets(residuo, 75, entrada);
    fscanf(entrada, " %d ", &qtd);

    // Pular proxima linha do arquivo de entrada
    fgets(residuo, 75, entrada);

    for(int i = 1; i <= qtd; i++)
    {
        fscanf(entrada, " %d ", &lin[i]);
        fscanf(entrada, " %d ", &col[i]);
    }

    // chamar função que retorna numero minimo de operacoes para matrizes dadas
    num_min = m(1, qtd);

    // saida
    fprintf(saida, "Lab2 - Sergio Luis dos Santos Filho \n");
    fprintf(saida, "Exercicio 2\n");
    fprintf(saida, "Produto de Matrizes \n\n");
    fprintf(saida, "Total de multiplicacoes escalares = %d\n\n", num_min);
    fprintf(saida, "Chamadas aa funcao: %d\n\n", num_chamadas);
    fprintf(saida, "Melhor ordem para realizar o produto:\n");
    // escreve as melhores posicoes para os cortes
    escreve(1,qtd);
    fclose(entrada);
    fclose(saida);

    return 0;
}
