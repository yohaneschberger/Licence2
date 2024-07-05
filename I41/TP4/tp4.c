#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ullong;
typedef unsigned int uint;

typedef struct
{
    ullong matrice[2][2];
}tmat;

tmat produit(tmat A, tmat B)
{
    tmat C;
    int i = 0, j, k;
    while(i < 2)
    {
        j = 0;
        while(j < 2)
        {
            C.matrice[i][j] = 0;
            k = 0;
            while(k < 2)
            {
                C.matrice[i][j] += (A.matrice[i][k] * B.matrice[k][j]);
                k++;
            }
            j++;
        }
        i++;
    }
    return C;
}

tmat puissance(tmat M, uint n)
{
    tmat C = M;
    for(int i = 1; i < n; i++)
        C = produit(C, M);
    return C;
}

/*tmat SM(tmat M, uint n)
{
    
}

ullong Fib(uint n)
{

}*/


int main(int argc, char *argv[])
{
    tmat A, B;
    A.matrice[0][0] = 5;
    A.matrice[0][1] = 2;
    A.matrice[1][0] = 1;
    A.matrice[1][1] = 4;

    B.matrice[0][0] = 3;
    B.matrice[0][1] = 7;
    B.matrice[1][0] = 5;
    B.matrice[1][1] = 2;

    tmat res = produit(A,B);
    printf("%llu, %llu \n%llu, %llu\n", res.matrice[0][0],res.matrice[0][1],res.matrice[1][0],res.matrice[1][1]);

    tmat res2 = puissance(A,3);
    printf("%llu, %llu\n%llu, %llu\n", res2.matrice[0][0],res2.matrice[0][1],res2.matrice[1][0],res2.matrice[1][1]);

    return 0;
}