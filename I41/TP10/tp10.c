#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct 
{
    float nombre;
    char op;
    enum {unaire, binaire, nombre} type;
} TJETON;

typedef TJETON *TEXPR;

typedef struct tcell
{
    float nombre;
    struct tcell *suivant;
} TCELL;

typedef TCELL *TLISTE;

TJETON Chaine2Jeton(char *chaine)
{
    TJETON jeton;
    float nombre;
    char op;

    if (sscanf(chaine, "%f", &nombre) > 0)
    {
        jeton.nombre = nombre;
        jeton.op = '\0';
        jeton.type = nombre;
    }
    else
    {
        sscanf(chaine, "%c", &op);
        jeton.nombre = 0.0;
        jeton.op = op;
        if (op == '_')
            jeton.type = unaire;
        else
            jeton.type = binaire;
    }
    return jeton;
}

TEXPR Arg2Expr(char **arguments, int n)
{
    TEXPR tabj = malloc(sizeof(TEXPR) * n);

    for(int i=0; i < n; i++)
    {
        tabj[i] = Chaine2Jeton(arguments[i]);
    }
    return tabj;
}

TLISTE Empiler(TLISTE pile, float nombre)
{
    TLISTE p = malloc(sizeof(TCELL));
    p->nombre = nombre;
    p->suivant = pile;
    pile = p;
    return p;
}

TLISTE Depiler(TLISTE pile, float *nombre)
{
    TLISTE L = pile;
    pile = pile->suivant;
    *nombre = L->nombre;
    free(L);
    return pile;
}

void AfficherPile(TLISTE pile)
{
    if(pile == NULL)return;

    TLISTE e = pile;
    while (e != NULL)
    {
        printf("%f -> ", e->nombre);
        e = e->suivant;
    }
    printf("\n");
}

void AfficherExpr(TEXPR expr, uint n)
{
    printf("JETON : |");
    for (int i = 0; i < n; i++)
    {
        TJETON jeton = expr[i];
        if ((jeton.type == unaire) || (jeton.type == binaire))
            printf(" %c |", jeton.op);
        else
            printf(" %3.2f |", jeton.nombre);
    }
    printf("\n");
}

float Operer(float x, float y, char op)
{
    float res;
    switch (op)
    {
    case '+':
        res = x+y;
        break;
    case '-':
        res = x-y;
        break;
    case '*':
        res = x*y;
        break;
    case '/':
        res = x/y;
        break;
    case '_':
        res = -x;
        break;
    }
    return res;
}

float Evaluer(TEXPR expr, uint n)
{
    return 0.0;
}

int main(int argc, char *argv[])
{
    uint n = argc - 1;
    TEXPR expr = malloc(sizeof(TJETON) * n);

    if (n < 1)
    {
        printf("Syntaxe: %s expr\n", argv[0]);
        return 1;
    }
    else
        expr = Arg2Expr(argv + 1, n);

    AfficherExpr(expr, n);

    free(expr);

    return 0;
}