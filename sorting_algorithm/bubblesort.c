#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--BubbleSort--
//Compara cada par de elementos adjacentes e os 
//troca se estiverem na ordem errada. 
//Esse processo é repetido até que o vetor esteja ordenado.

void bubbleSort(int v[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {

                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int vetor[6];
    int i, j, temp;
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

    bubbleSort(vetor, n);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
