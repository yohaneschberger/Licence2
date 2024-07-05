#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long long ullong;

typedef enum 
{
    TRUE = 1,
    FALSE = 0
} tbool;

uchar Increment(uint *A, uchar n, uchar b)
{
    uint i = 0;
    while ((i<n) && (A[i] == b-1))
    {
      A[i] = 0;
      i++;
    }
    if (i<n)
    {
      A[i] = A[i] + 1;
    }
    return i;
}

ullong test(uchar n, uchar b)
{
    uint *A = (uint*)malloc(sizeof(uint) * n);
    uint possibilites = 1;
    for (int i = 0; i < n; i++)
    {
        possibilites *= b;
        A[i] = 0;
    }

    uint modifications = 0;
    for (int i = 0; i < possibilites; i++)
        modifications += Increment(A,n,b);

    return modifications;
}

uint TailleMot(char * mot) {
    int taille = 0;
    while(mot[taille] != '\0')
        taille++;
    return taille;
}

tbool EstPrefixe(char *pre, char *mot)
{
    uint T_pre = TailleMot(pre);
    if (T_pre > TailleMot(mot))
        return FALSE;

    for (int i = 0; i < TailleMot(mot); i++)
        if (mot[i] != pre[i]) return FALSE;
    return TRUE;
}

tbool BienParenthesee(char *expr)
{
    uint taille_expr = TailleMot(expr);
    int count = 0;

    for(uint i = 0; i < taille_expr; i++) {
        if(expr[i] == '(') count++;
        if(expr[i] == ')') count--;
        if(count < 0) return FALSE;
    }
    return count == 0 ? TRUE : FALSE;
}

int main()
{
    uchar n = 7;
    uchar b = 10;

    uint A[] = {9,9,9,2,9,9,2};
    uint i = Increment(A, n, b);
    uint total = test(30,2);

    printf("%i\n", i);
    printf("%i\n", total);

    tbool t = EstPrefixe("Bon","Bonjour");

    printf("%d\n", t);

    tbool test_3 = BienParenthesee("(3+2(5-1))");
    tbool test_4 = BienParenthesee("((2+3)(1-(1/2))-2)");
    tbool test_5 = BienParenthesee(")2(+(3-1)");

    printf("(3+2(5-1)) ? %d\n", test_3);
    printf("((2+3)(1-(1/2))-2) ? %d\n", test_4);
    printf(")2(+(3-1) ? %d\n", test_5);

    return 0;
}