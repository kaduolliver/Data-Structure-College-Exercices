#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função shellSort: O algoritmo Shell Sort melhora o Insertion Sort 
//comparando elementos que estão a uma certa "distância" uns dos outros (definida pelo intervalo). 
//À medida que o intervalo diminui, o vetor vai ficando cada vez mais ordenado.

void shellSort(int v[], int n)
{

    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2)
    {

        for (int i = intervalo; i < n; i++)
        {
            int temp = v[i];
            int j;

            for (j = i; j >= intervalo && v[j - intervalo] > temp; j -= intervalo)
            {
                v[j] = v[j - intervalo];
            }
            v[j] = temp;
        }
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

    shellSort(vetor, n);

    printf("Vetor ordenado: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
