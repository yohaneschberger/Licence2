#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

typedef struct
{
    float nombre;
    char op;
    enum {unaire, binaire, nombre} type;
} TJETON;

typedef TJETON *TEXPR;

typedef struct TCELL
{
    float nombre;
    struct TCELL *suivant;
} TCELL;

typedef TCELL *TLISTE;

TJETON Chaine2Jeton(char *chaine)
{
    TJETON jeton;
    jeton.type = nombre;
    int len = strlen(chaine);

    if (len == 1)
    {
        char c = chaine[0];
        if (c == '-' || c == '+') {
            jeton.op = c;
            jeton.type = unaire;
        } else {
            jeton.op = c;
            jeton.type = binaire;
        }
    } else {
        // Sinon, c'est un nombre
        jeton.nombre = atof(chaine);
    }
    return jeton;
}

TEXPR Arg2Expr(char *arguments[], int n)
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
    TCELL *P = (TCELL*)malloc(sizeof(TCELL));
    P->nombre = nombre;
    P->suivant = pile;

    return P;
}

TLISTE Depiler(TLISTE pile, float *nombre)
{
    if (pile == NULL)return NULL;
    TCELL *L = pile;
    *nombre = L->nombre;
    pile = pile->suivant;
    free(L);

    return pile;
}

void AfficherPile(TLISTE pile)
{
    printf("Contenu de la pile : ");
    if(pile == NULL)
    {
        printf("Pile vide\n");
        return;
    }
    
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
    TLISTE pile; // Déclaration d'une pile

    for (int i = 0; i < n; i++) {
        TJETON jeton = expr[i]; // Récupérer le jeton courant de l'expression

        // Vérifier le type du jeton
        if (jeton.type == nombre) {
            // Si c'est un nombre, empiler sur la pile
            pile = Empiler(pile, jeton.nombre);
        } else if (jeton.type == unaire) {
            // Si c'est un opérateur unaire, dépiler le nombre au sommet de la pile, appliquer l'opération et empiler le résultat sur la pile
            float x;
            pile = Depiler(pile, &x);
            float resultat = Operer(x, 0, jeton.op);
            pile = Empiler(pile, resultat);
        } else if (jeton.type == binaire) {
            // Si c'est un opérateur binaire, dépiler les deux derniers nombres de la pile, appliquer l'opération et empiler le résultat sur la pile
            float y, x;
            pile = Depiler(pile, &y);
            pile = Depiler(pile, &x);
            float resultat = Operer(x, y, jeton.op);
            pile = Empiler(pile, resultat);
        }
    }

    // Vérifier si la pile est vide à la fin de l'évaluation
    if (pile != NULL) {
        printf("Erreur : pile non vide à la fin de l'évaluation\n");
        exit(EXIT_FAILURE);
    }

    // Récupérer le résultat final de l'expression évaluée
    float resultat;
    pile = Depiler(pile, &resultat);

    return resultat; // Renvoyer le résultat final de l'expression évaluée
}


int main(int argc, char **argv)
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

    float resultat = Evaluer(expr, strlen(expr));

    printf("%f\n", resultat);

    free(expr);

    return 0;
}