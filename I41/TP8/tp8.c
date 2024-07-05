#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void Copier(tliste X, uint i, tliste Y, uint j, uint n)
{
    int k = 0;

    while ((i+k <= X.n) && ((j+k) <= Y.n) && (k < n))
    {
        Y.valeurs[j+k] = X.valeurs[i+k];
        k++;
    }
}

void Fusionner(tliste L, uint p, uint q, uint r)
{
    uint ng = q - p + 1, nd = r - q;
    tliste G = {ng, (int*)malloc(sizeof(int) * ng)};
    tliste D = {nd, (int*)malloc(sizeof(int) * nd)};

    Copier(L, p, G, 0, ng);
    Copier(L, q, D, 0, nd);

    int i = 0, j = 0, k = p;

    while (i < ng && j < nd)
    {
        if (G.valeurs[i] <= D.valeurs[j])  
            L.valeurs[k] = G.valeurs[i++];
        else
            L.valeurs[k] = D.valeurs[j++];
        k++; 
    }
    
    Copier(G, i, L, k, ng-i);
    free(G.valeurs);
    free(D.valeurs);
}

void TriFusion(tliste L, uint p, uint r)
{
    if (p < r)
    {
        uint q = (p + (r-p)) / 2;
        TriFusion(L, p, q);
        TriFusion(L, q + 1, r);
        Fusionner(L, p, q, r);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    uint n = atoi(argv[1]);
    int *perm = genperm(n);

    tliste A =  {n, perm};

    TriFusion(A, 0, n-1);
    for (int i = 0; i < n; i++)
        printf("%d ", A.valeurs[i]);
    printf("\n");

    free(perm);

    return 0;
}