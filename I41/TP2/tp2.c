#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  TRUE = 1,
  FALSE = 0
} tbool;

typedef unsigned short ushort;
typedef unsigned int uint;

uint TailleMot(char * mot) {
    int taille = 0;
    while (mot[taille] != '\0')
        taille++;
    return taille;
}

tbool EstPalindrome(char *phrase)
{
  int t = TailleMot(phrase);
  int i = 0;
  while (i < t/2)
  {
    if (phrase[i] != phrase[t - i - 1])
      return FALSE;
    i++;
  }
  return TRUE;
}

void TriSelection(int *liste, ushort n)
{
  int i, j, tmp, min;
  for (i=0; i < n-1; i++)
  {
    min = i;
    for (j=i+1; j < n; j++)
      if (liste[j] < liste[min])
        min = j;
    if (min != i)
    {
        tmp = liste[i];
        liste[i] = liste[min];
        liste[min] = tmp;
    }
  }
}

void Affiche_Liste(int *liste, ushort n)
{
  for (int i = 0; i < n-1; i++)
    printf("%3d", liste[i]);
  printf("\n\n");
}

uint PairOuImpaire(uint n)
{
  return n%2 == 0 ? n/2 : 3*n+1;
}

uint Syracuse(uint u0)
{
  uint u = u0, n = 0;
  while (u > 1)
  {
    u = PairOuImpaire(u);
    n++;
  }
  return n;
}

void Analyse(uint u0, int *temps, int *altitude)
{
  *temps = 1;
  *altitude = u0;
  uint u;
  while ((u = PairOuImpaire(u0)) != 1)
  {
    if (u > *altitude)
      *altitude = u;
    (*temps)++;
  }
}

int main(int argc, char **argv){
  tbool test = EstPalindrome(argv[1]);

  printf("Est-ce un palindrome: %s\n", test ? "Oui" : "Non");

  int n, i;
  printf("Nombres d'entiers que vous voulez triez: ");
  scanf("%d",&n);

  int *liste = (int*)malloc(sizeof(int) * n);
  printf("\n");

  for (i=0; i < n; i++){
    printf("Donner l'entier %d: ", i);
    scanf("%d", &liste[i]);
  }

  Affiche_Liste(liste,n);
  TriSelection(liste,n);
  Affiche_Liste(liste,n);

  uint result = PairOuImpaire(atoi(argv[2]));
  uint result2 = Syracuse(atoi(argv[3]));

  printf("Pair ou Impair: %d\n", result);
  printf("%d\n", result2);

  int precision;
  printf("Entrez la précision de vol: \n");
  scanf(" %d", &precision);

  FILE *file = fopen("./mongraphe.txt", "w+"); 
  if (file != NULL)
  {
    for(int i = 1; i <= precision; i++)
    {
      uint min_n = Syracuse(i);
      fprintf(file, "%i %i\n", i, min_n);
    }
  }
  fclose(file);
  system("gnuplot -persist -e \"plot './mongraphe.txt' with lines linewidth 1.5\"");

  // Test de calcul du temps de vol et de l'altitude maximum
  // de la suite de Syracuse pour u0=4.563.281.
  int temps;
  int altitude;
  Analyse(4563281, &temps, &altitude);
  printf("Altitude max: %d\n", altitude);
  printf("Temps de vol: %d\n", temps);

  return 0;
}
