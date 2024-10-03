#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--SelectionSort--
// Em cada itera��o, o algoritmo seleciona o
// menor elemento do vetor n�o ordenado e o coloca
// na posi��o correta. O processo se repete at� que o vetor esteja ordenado.

void selectionSort(int v[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }

        temp = v[min];
        v[min] = v[i];
        v[i] = temp;
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

    selectionSort(vetor, n);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
