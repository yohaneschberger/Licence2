#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef unsigned int uint;

typedef struct {
  uint n;        // longueur de la liste
  int *valeurs;
} tliste;

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

void Fusionner(tliste arr, int l, int m, int r, uint *cpt) 
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    tliste G = {n1, (int*)malloc(sizeof(int) * n1)};
    tliste D = {n2, (int*)malloc(sizeof(int) * n2)};
 
    for (int i = 0; i < n1; i++)
        G.valeurs[i] = arr.valeurs[l + i];
    for (int j = 0; j < n2; j++)
        D.valeurs[j] = arr.valeurs[m + 1 + j];
 
    int i = 0, j = 0, k = l;
 
    while (i < n1 && j < n2) 
    {
        if (G.valeurs[i] <= D.valeurs[j]) 
        {
            arr.valeurs[k] = G.valeurs[i];
            i++;
        }
        else 
        {
            arr.valeurs[k] = D.valeurs[j];
            j++;
        }
        k++;
        *cpt += 1;
    }
 
    while (i < n1) 
    {
        arr.valeurs[k] = G.valeurs[i];
        i++;
        k++;
    }
 
    while (j < n2) 
    {
        arr.valeurs[k] = D.valeurs[j];
        j++;
        k++;
    }

    free(G.valeurs);
    free(D.valeurs);
}
 
void TriFusion(tliste arr, int l, int r, uint *cpt) 
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;
 
        TriFusion(arr, l, m, cpt);
        TriFusion(arr, m + 1, r, cpt);
 
        Fusionner(arr, l, m, r, cpt);
    }
}
 
int main(int argc, char *argv[]) 
{
    srand(time(NULL));
    uint nbr = atoi(argv[1]);

    FILE *f1 = fopen("./graph.txt", "w+");
    FILE *f2 = fopen("./graph_log.txt", "w+");

    if (f1 != NULL && f2 != NULL)
    {
        for (int i = 1; i <= nbr; i++)
        {
            int *perm = genperm(i);
            uint *cpt = calloc(1, sizeof(uint));
            tliste A =  {i, perm};

            TriFusion(A, 0, i-1, cpt);

            fprintf(f1, "%d %d\n", i, *cpt);
            fprintf(f2, "%d %f\n", i, i * log(i));

            free(perm);
            free(cpt);
        }
        fclose(f1);
        fclose(f2);
    }

    system("gnuplot -persist -e \"plot './graph.txt' with lines linewidth 1.5, './graph_log.txt' with lines linewidth 1.5\"");

    return 0;
}