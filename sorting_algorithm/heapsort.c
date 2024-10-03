#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função heapSort: Constrói um max-heap a partir do array original e, em seguida, 
//ordena o array movendo o maior elemento (a raiz) para o final, 
//reconstruindo o heap com os elementos restantes.

void heapify(int v[], int n, int i)
{
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && v[esq] > v[maior])
        maior = esq;

    if (dir < n && v[dir] > v[maior])
        maior = dir;

    if (maior != i)
    {
        int temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;

        heapify(v, n, maior);
    }
}

void heapSort(int v[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; i--)
    {

        int temp = v[0];
        v[0] = v[i];
        v[i] = temp;

        heapify(v, i, 0);
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

    heapSort(vetor, n);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
