#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função quickSort: Implementa o algoritmo Quick Sort de forma recursiva. 
//Ela divide o array em duas partes ao redor do pivô e ordena cada parte recursivamente.

void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particao(int v[], int inicio, int fim)
{
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (v[j] < pivo)
        {
            i++;
            trocar(&v[i], &v[j]);
        }
    }
    trocar(&v[i + 1], &v[fim]);
    return i + 1;
}

void quickSort(int v[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int pi = particao(v, inicio, fim);

        quickSort(v, inicio, pi - 1);
        quickSort(v, pi + 1, fim);
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

    quickSort(vetor, 0, n - 1);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
