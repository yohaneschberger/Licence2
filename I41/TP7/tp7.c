#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>  

typedef unsigned int uint;

void Echanger(int *T, int a, int b)
{
    int tmp = T[a];
    T[a] = T[b];
    T[b] = tmp;
}

int *genperm(uint n)
{
    int *perm = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        perm[i] = i+1;
    printf("\n");
    for(int i = 0; i<n; i++)
    {
        int index = rand() % n;
        int tmp = perm[i];
        perm[i] = perm[index];
        perm[index] = tmp;
    }
    return perm;
}

void Tamiser(int *T, uint n, uint i, uint *cpt) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < n && T[left] > T[largest])
    {
        largest = left;
        *cpt += 1;
    }

    if (right < n && T[right] > T[largest])
    {
        largest = right;
        *cpt += 1;
    }

    if (largest != i) {
        Echanger(T, i, largest);
 
        Tamiser(T, n, largest, cpt);
    }
}

void Entasser(int *T, uint n, uint *cpt)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Tamiser(T, n, i, cpt);
}
 
void TriTas(int *T, uint n, uint *cpt) {
    Entasser(T,n,cpt);
 
    for (int i = n-1; i >= 0; i--) {
        Echanger(T, 0, i);
        Tamiser(T, i, 0, cpt);
    }
}
 
int main(int argc, char *argv[]) 
{
    srand(time(NULL));
    uint nbr = atoi(argv[1]);

    FILE *f1 = fopen("./graph.txt", "w+");
    FILE *f2 = fopen("./graph_log.txt", "w+");
    FILE *f3 = fopen("./graph_log2.txt", "w+");

    if (f1 != NULL && f2 != NULL && f3 != NULL)
    {
        for (int i = 1; i <= nbr; i++)
        {
            int *perm = genperm(i);
            uint *cpt = calloc(1, sizeof(uint));

            TriTas(perm, i, cpt);
            for(int j = 0; j < i; j++)
                printf("%d ", perm[j]);

            fprintf(f1, "%d %d\n", i, *cpt);
            fprintf(f2, "%d %f\n", i, i * log(i));
            fprintf(f3, "%d %f\n", i, (i * log(i))*2);

            free(perm);
            free(cpt);
        }
        fclose(f1);
        fclose(f2);
        fclose(f3);
    }

    system("gnuplot -persist -e \"plot './graph.txt' with lines linewidth 1.5, './graph_log.txt' with lines linewidth 1.5, './graph_log2.txt' with lines linewidth 1.5\"");

    return 0;
}
