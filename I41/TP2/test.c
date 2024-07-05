#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct timespec spec;

typedef unsigned int uint;

uint *genperm(uint n)
{
    int *perm = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        perm[i] = i;
    }
    clock_gettime(0, &spec);
    srand(spec.tv_nsec);
    for(int i = 0; i<n; i++)
    {
        int index = rand() % n;
        int tmp = perm[i];
        perm[i] = perm[index];
        perm[index] = tmp;
    }
    return perm;
}

void Echanger(int *T, uint a, uint b)
{
    int tmp = T[a];
    T[a] = T[b];
    T[b] = tmp;
}

int Tamiser(int *T, uint i, uint n)
{
    int C = 2;
    uint ifils = 2 * i;
    if ((ifils < n) && (T[ifils+1] > T[ifils]))
        ifils++;
    if ((ifils <= n) && (T[i] < T[ifils]))
    {
        Echanger(T, i, ifils);
        C += Tamiser(T, ifils, n);
    }
}

int Entasser(int *T, uint n)
{
    int i = n / 2;
    int C = i;
    while (i >= 0)
    {
        C += Tamiser(T, i, n-1);
        i--;
    }
    return C;
}
int TriTas(int *T, uint n)
{
    int k = n-1;

    int C = Entasser(T, n) + k;
    while (k > 0)
    {
        Echanger(T, 0, k);
        C += Tamiser(T, 0, k-1);
        k--;
    }
    return C;
}

int main(int argc, char **argv)
{
    // Récupère dans argv la taille n du tableau.
    int n = atoi(argv[1]);
    // Récupère dans argv la durée requise pour l'évaluation.
    int length = atoi(argv[2]);
    //
    int *eval_tri = malloc(length * sizeof(int));
    int *eval_log = malloc(length * sizeof(int));
    //
    FILE *file_1 = fopen("./graph_eval.txt", "w+");
    FILE *file_2 = fopen("./graph_log.txt", "w+");
    //
    if (file_1 != NULL && file_2 != NULL)
    {
        int i = 1;
        while (i < length)
        {
            // Génère une tableau de taille n, de permutations aléatoires.
            int *perms = genperm(i);
            int coeff = 7;
            int eval_tri = TriTas(perms, i) / coeff;
            // Ecriture dans le fichier
            fprintf(file_1, "%d %d\n", i, eval_tri);
            fprintf(file_2, "%d %f\n", i, i * log10(i));
            i++;
        }
        fclose(file_1);
        fclose(file_2);
    }

    system("gnuplot -persist -e \"plot './graph_eval.txt' with lines linewidth 1.5, './graph_log.txt' with lines linewidth 1.5\"");
    free(eval_tri);
    free(eval_log);

    return 0;
}