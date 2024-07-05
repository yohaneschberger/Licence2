#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAILLE 10 //Taille d'une cellule 

void affiche_Surface(int** n1, unsigned int n, SDL_Surface* ecran, SDL_Surface* surface, SDL_Window* fenetre)
{
    SDL_Rect parti, pos;
 
    parti.y = 0;
    parti.w = parti.h = TAILLE-1;
 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            parti.x = n1[i][j] * TAILLE;
            pos.x = i * TAILLE-1;
            pos.y = j * TAILLE-1;
            SDL_BlitSurface(surface, &parti, ecran, &pos);
        }
    }
    SDL_UpdateWindowSurface(fenetre);
}

void generateTab(int** n1, unsigned int n, int choix) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            n1[i][j] = choix >= 0 ? choix : rand() % 2;
}

void copieTab(int** n1, int** n2, unsigned int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            n2[i][j] = n1[i][j];
 
}

void test(int** n1, int** n2, unsigned int n) {
    int nbr_voisine_vivante;
 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            nbr_voisine_vivante = 0;
            for(int k = -1; k < 2; k++)
                for(int l = -1; l < 2; l++)
                    if(((k != 0) || (l != 0)) && ((i != 0) || (k != (-1))) && ((i != n-1) || (k != 1)) && ((j != 0) || (l != (-1))) && ((j != n-1) || (l!= 1)))
                        nbr_voisine_vivante += n2[i+k][j+l];
 
            n1[i][j] = (n2[i][j] && (nbr_voisine_vivante == 2 || nbr_voisine_vivante == 3)) || (!n2[i][j] && (nbr_voisine_vivante == 3)) ? 1 : 0;
        }
    }
    copieTab(n1, n2, n);
}

int main(int argc, char **argv) {

    int debut = 1, n, tours;

    while(debut)
    {
        printf("Longueur du carré (entiers > 0) : ");
        scanf("%d", &n);
        printf("Nombres de tours : ");  // Demande de nombres de tours
        scanf("%d", &tours);
        /* on donne la valeur entière du nombre saisi
        (qui peut être un nombre décimal) à la variable temporaire */
        if((n == 0) || (n < 0)) // Si le nombre qui peut être décimal est égal à la valeur entière qu'on a enregistrée.
            printf("J'ai dit SUPERIEUR à 0\n");
        else
            debut = 0; // On quitte la boucle
        /* La boucle continue de s'exécuter tant que ce n'est pas le cas */
    }

    // Les dimensions de la fenetre (zone d'affichage) en pixels
    unsigned int frame_width  = TAILLE * n; // Largeur
    unsigned int frame_height = TAILLE * n; // Hauteur

    // Le nombre de colonnes (columns) et de lignes (rows) du jeu
    unsigned int columns = n;
    unsigned int rows    = n;

    // ces tailles son fonction des dimensions de la fenetre et du 
    // nombre de colonnes et de lignes
    unsigned int column_width = 0;
    unsigned int row_height   = 0;

    // Calcul des largeur de colonnes et hauteur de lignes en pixel
    column_width = frame_width / columns;
    row_height = frame_height / rows;

    printf("Taille de la grille                     : %d x %d\n", columns, rows);
    printf("Taille d'une cellule (largeur x hauteur): %dpx x %dpx\n", column_width, row_height);

    printf("\nLancement de l'interface graphique\n");

    SDL_Window* fenetre;
    SDL_Event event;
    int** n1 = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) n1[i] = (int*) calloc(n, sizeof(int));
    int** n2 = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) n2[i] = (int*) calloc(n, sizeof(int));

    srand(time(NULL));

    // Initialisation de la SDL
    if(SDL_VideoInit(NULL) < 0)
    {
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre
    // la fonction de creation renvoie NULL si la fenetre n'a pas pu etre cree
    fenetre = SDL_CreateWindow("Jeu de la vie" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , frame_width , frame_height , 0);
    
    // Si la fenetre n'a pas pu etre cree, le programme ne peut continuer
    if(fenetre == NULL)
    {
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        return EXIT_FAILURE;
    }


    SDL_Surface *ecran = SDL_GetWindowSurface(fenetre);
    SDL_Surface *surface = SDL_GetWindowSurface(fenetre);  
    SDL_Rect parti;
    int i;
 
    parti.h = parti.w = TAILLE;
    parti.y = 0;
 
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, TAILLE * n, TAILLE * n, 32, 0, 0, 0, 0);

    if(surface == NULL)
    {
        printf("Erreur de creation de l'allocation d'une surface : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    for(i = 0; i < 2; i++)
    {
        parti.x = i * TAILLE;
        SDL_FillRect(surface, &parti, ~(0xffffff * i));
    }

    generateTab(n1, n, 0);
    copieTab(n1, n2, n);

    int continuer = 1, delay = 50, delay1 = 0, etat = 0;

    while(continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONUP :
                if(!etat && event.button.button == SDL_BUTTON_LEFT)
                {
                    n1[event.button.x / TAILLE][event.button.y / TAILLE] ^= 1;
                    n2[event.button.x / TAILLE][event.button.y / TAILLE] ^= 1;
                }
                case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE :
                        etat ^= 1;
                        break;
                    case SDLK_ESCAPE :
                        return 0;
                        break;
                    case SDLK_KP_1 :
                        if(!etat)
                        {
                            generateTab(n1, n, 1);
                            copieTab(n1, n2, n);
                        }
                        break;
                    case SDLK_KP_0 :
                        if(!etat)
                        {
                            generateTab(n1, n, 0);
                            copieTab(n1, n2, n);
                        }
                        break;
                    case SDLK_KP_2 :
                        if(!etat)
                        {
                            generateTab(n1, n, -1);
                            copieTab(n1, n2, n);
                        }
                        break;
                    default :
                    ;
                    break;
                }
                break;
                default :
                ;
                break;
            }
        }
        if(etat) {
            test(n1, n2, n);
        }
        affiche_Surface(n1, n, ecran, surface, fenetre);
        SDL_Delay(etat ? delay : delay1);
    }
        
        // C'est la version qui marche pour un nombres de tours précis 
        // mais etant donne que normalement le projet est déja rendu, je l'ai mis en commentaire
        // pour que vous puissiez voir la raison de pourquoi ça ne marchait pas durant le dernier TP
    /*while(tours != 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONUP :
                if(!etat && event.button.button == SDL_BUTTON_LEFT)
                {
                    n1[event.button.x / TAILLE][event.button.y / TAILLE] ^= 1;
                    n2[event.button.x / TAILLE][event.button.y / TAILLE] ^= 1;
                }
                case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE :
                        etat ^= 1;
                        break;
                    case SDLK_ESCAPE :
                        return 0;
                        break;
                    case SDLK_KP_1 :
                        if(!etat)
                        {
                            generateTab(n1, n, 1);
                            copieTab(n1, n2, n);
                        }
                        break;
                    case SDLK_KP_0 :
                        if(!etat)
                        {
                            generateTab(n1, n, 0);
                            copieTab(n1, n2, n);
                        }
                        break;
                    case SDLK_KP_2 :
                        if(!etat)
                        {
                            generateTab(n1, n, -1);
                            copieTab(n1, n2, n);
                        }
                        break;
                    default :
                    ;
                    break;
                }
                break;
                default :
                ;
                break;
            }
        }
        if(etat) {
            test(n1, n2, n);
            tours--;                                    // L'erreur idiote se trouve ici on avait pas mis tours--; dans le if mais en dehors
        }
        affiche_Surface(n1, n, ecran, surface, fenetre);
        SDL_Delay(etat ? delay : delay1);
    }

    SDL_Delay(5000);*/
    
    
    SDL_FreeSurface(surface);
    SDL_FreeSurface(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit(); // On quitte la SDL
    free(n1);
    free(n2);

    return EXIT_SUCCESS;
}
