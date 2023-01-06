/*
 Sergio Luis dos Santos Filho
 Turma 2
 Exercício 3: Ordenacao
 Programa compilado com CodeBlocks 20.03
 Instituto Tecnológico de Aeronáutica
 CES-11: Algoritmos e Estruturas de Dados
 Prof. Armando
 Setembro de 2022
*/

/*
Observação: Foi utilizado apenas um vetor para a leitura das strings para que
ocupasse um menor de espaço, possibilitando uma melhoria nos algoritmos de or-
denação, visto que eles utilizam bastante do espaço da memória
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 52
typedef char tipelemento [MAX];
typedef char vetor [MAX];
int contador; // contador de comparacoes
int quant; // quantidade de strings para se ordenar


// funcao que soma um no contador de comparacoes e retorna
// a comparacao entre a e b
int compara (const char * a, const char * b)
{
    contador ++;
    return strcmp (a, b);
}

/// Funcoes do Quick Sort
//--------------------------------------------------
//    PARTITION
//--------------------------------------------------
int Partition (vetor * V, int ini, int fim)
{
    tipelemento pivo, aux;
    int esq, dir;

    strcpy(pivo,"");
    strcpy(pivo, V[ini]); // O pivo é o primeiro da esquerda
    esq  = ini + 1;
    dir  = fim;
    do
    {
        // percorrer da esquerda para a direita. encontrar alguem >= pivo
        while (esq < fim && compara(V[esq],pivo)<0)
            esq++;
        // percorrer da direita para a esquerda. encontrar alguem < pivo
        while (ini < dir && compara(pivo,V[dir]) <= 0)
            dir--;
        // se achou um a esquerda e outro a direita
        if(esq < dir)
        {
            // permutar
            strcpy(aux,V[esq]);
            strcpy(V[esq],V[dir]);
            strcpy(V[dir],aux);
        }
        // caso contrario, terminara a repeticao
    }
    while (esq < dir);

    // trocar o pivo com o elemento que "divide" os subvetores
    strcpy(V[ini],V[dir]);
    strcpy(V[dir],pivo);
    // retornar a posição da "divisa"
    return dir;
}

//--------------------------------------------------
//    QUICK SORT
//--------------------------------------------------
void QuickSort (vetor * V, int ini, int fim)
{
    int p; //posição do pivo
    if (ini < fim)
    {
        p = Partition (V, ini, fim);
        QuickSort     (V, ini, p-1);
        QuickSort     (V, p+1, fim);
    }
}

/// Funcoes do Merge Sort
//--------------------------------------------------
//    MERGE
//--------------------------------------------------
void Merge (vetor * V, int ini, int fim)
{
    int med,
        i,     // percorre T
        j,     // percorre lado esquerdo de V
        k;     // percorre lado direito  de V

    static vetor * T =  (vetor *) malloc ((quant)*sizeof(vetor));

    med = (ini+fim)/2; //mesmo arredondamento feito ao chamar MergeSort
    j = ini;
    k = med+1;
    i = ini;
    //percorrer selecionando os menores
    while (j <= med && k <= fim)
    {
        if (compara(V[j],V[k]) <= 0)
        {
            strcpy(T[i],V[j]);
            j++;
        }
        else
        {
            strcpy(T[i],V[k]);
            k++;
        }
        i++;
    }
    //se sobrou algo a esquerda, copiar para T
    while(j <= med)
    {
        strcpy(T[i],V[j]);
        i++;
        j++;
    }
    //se sobrou algo a direita, copiar para T
    while(k<=fim)
    {
        strcpy(T[i],V[k]);
        i++;
        k++;
    }
    // V recebe T
    for(i=ini; i<=fim; i++)
        strcpy(V[i],T[i]);
}

//--------------------------------------------------
//    MERGE SORT
//--------------------------------------------------
void MergeSort (vetor * V, int ini, int fim)
{
    int med;
    if (ini < fim)
    {
        med = (ini+fim)/2;          // dividir ao meio
        MergeSort (V, ini,   med);  // ordenar lado esquerdo
        MergeSort (V, med+1, fim);  // ordenar lado direito
        Merge     (V, ini,   fim);  // mesclar as duas metades
    }
}

int main()
{
    vetor * V; // ponteiro que guardadara as strings
    clock_t inicio, fim;
    float   delta_t;
    FILE * entrada,
         * saida_bubble,
         * saida_merge,
         * saida_quick;
    // abrir arquivos
    saida_bubble = fopen("Lab3_Sergio_Luis_dos_Santos_Filho_bubble.txt", "w");
    saida_merge = fopen("Lab3_Sergio_Luis_dos_Santos_Filho_merge.txt", "w");
    saida_quick = fopen("Lab3_Sergio_Luis_dos_Santos_Filho_quick.txt", "w");

/// Bubble Sort
    contador = 0; // contador de comparacoes
    // abrir e ler o arquivo de entrada guardando as strings
    entrada = fopen("entrada3.txt", "r");
    fscanf(entrada, "%d", &quant);
    V = (vetor*) malloc (quant*sizeof(vetor));
    for(int i =0; i < quant; i++)
        fscanf(entrada," %s ", V[i]);
    // fechar o arquivo de entrada
    fclose(entrada);

    int i, j;
    tipelemento aux;
    // inicia a marcacao do tempo
    inicio = clock();
    // ordena as strings
    for(int m = (quant - 1); m>=0 ; m--)
    {
        for(int k = 0; k < m; k++)
        {
            i = k;
            j = i++;
            if(compara(V[i],V[j]) < 0)
            {
                strcpy(aux,V[i]);
                strcpy(V[i],V[j]);
                strcpy(V[j],aux);
            }
        }
    }
    // termina a macacao do tempo
    fim    = clock();
    // calcula o tempo que durou em segundos
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    // escrever no arquivo de saida do Bubble-Sort
    fprintf(saida_bubble, "Algoritmo: Bubble-Sort\n\n");
    fprintf(saida_bubble, "Tamanho da entrada: %d\n", quant);
    fprintf(saida_bubble, "Comparações feitas: %d\n", contador);
    fprintf(saida_bubble, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(saida_bubble, "--------------------------------------------------\n");
    for (int i = 0; i < quant; i++)
        fprintf(saida_bubble,"%s\n",V[i]);
    // libera espaco de V
    free(V);

/// Quick Sort
    contador = 0; // contador de comparacoes
    // abrir e ler o arquivo de entrada guardando as strings
    entrada = fopen("entrada3.txt", "r");
    fscanf(entrada, "%d", &quant);
    V = (vetor*) malloc (quant*sizeof(vetor));
    for(int i =0; i < quant; i++)
        fscanf(entrada," %s ", V[i]);
    // fechar o arquivo de entrada
    fclose(entrada);
    // inicia a marcacao do tempo
    inicio = clock();
    // ordena as strings
    QuickSort (V, 0, quant-1);
    // termina a macacao do tempo
    fim    = clock();
    // calcula o tempo que durou em segundos
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    // escrever no arquivo de saida do Quick-Sort
    fprintf(saida_quick, "Algoritmo: Quick-Sort\n\n");
    fprintf(saida_quick, "Tamanho da entrada: %d\n", quant);
    fprintf(saida_quick, "Comparações feitas: %d\n", contador);
    fprintf(saida_quick, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(saida_quick, "--------------------------------------------------\n");
    for (int i = 0; i < quant; i++)
        fprintf(saida_quick,"%s\n",V[i]);
    // libera espaco de V
    free(V);

/// Merge Sort
    contador = 0; // contador de comparacoes
    // abrir e ler o arquivo de entrada guardando as strings
    entrada = fopen("entrada3.txt", "r");
    fscanf(entrada, "%d", &quant);
    V = (vetor*) malloc (quant*sizeof(vetor));
    for(int i =0; i < quant; i++)
        fscanf(entrada," %s ", V[i]);
    // fechar o arquivo de entrada
    fclose(entrada);
    // inicia a marcacao do tempo
    inicio = clock();
    // ordena as strings
    MergeSort (V, 0, quant-1);
    // termina a macacao do tempo
    fim    = clock();
    // calcula o tempo que durou em segundos
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    // escrever no arquivo de saida do Merge-Sort
    fprintf(saida_merge, "Algoritmo: Merge-Sort\n\n");
    fprintf(saida_merge, "Tamanho da entrada: %d\n", quant);
    fprintf(saida_merge, "Comparações feitas: %d\n", contador);
    fprintf(saida_merge, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(saida_merge, "--------------------------------------------------\n");
    for (int i = 0; i < quant; i++)
        fprintf(saida_merge,"%s\n",V[i]);
    // libera espaco de V
    free(V);

    // fechar arquivos de saida
    fclose(saida_bubble);
    fclose(saida_merge);
    fclose(saida_quick);
    return 0;
}
