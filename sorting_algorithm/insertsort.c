#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//O algoritmo de Insertion Sort percorre o vetor, começando do segundo elemento, 
//e insere cada elemento em sua posição correta em relação aos elementos anteriores. 
//Para isso, ele desloca os elementos maiores para a frente, criando espaço para o elemento atual.

void insertionSort(int v[], int n)
{
    int i, j, chave;
    for (i = 1; i < n; i++)
    {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > chave)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = chave;
    }
}

int main()
{
    int vetor[6];
    int i, j;
    int n = 6;

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        vetor[i] = rand() % 100;

        for (j = 0; j < i; j++)
        {
            if (vetor[i] == vetor[j])
            {
                i--;
                break;
            }
        }
    }

    printf("Vetor original: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    insertionSort(vetor, n);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
