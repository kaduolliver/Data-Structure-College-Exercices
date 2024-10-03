#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//A função merge combina dois subarrays ordenados em um único array. 
//Ela compara os elementos de dois subarrays e os mescla de volta no array principal.

//Função mergeSort: O mergeSort divide o vetor em dois subarrays, 
//os ordena recursivamente e depois usa a função merge para combinar as duas metades.

void merge(int v[], int esquerda, int meio, int direita)
{
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = v[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = v[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int v[], int esquerda, int direita)
{
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(v, esquerda, meio);
        mergeSort(v, meio + 1, direita);

        merge(v, esquerda, meio, direita);
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

    mergeSort(vetor, 0, n - 1);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
