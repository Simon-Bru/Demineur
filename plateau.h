#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

///-----------------------------------------  STRUCURE PLATEAU  -----------------------------------------------------\\\

typedef struct plateau
{
    int lig;
    int col;
}t_plateau;

/// Fonction constructeur de la structure plateau
t_plateau* setPlateau(int longueur, int largeur);

/// Fonction d'affichage du plateau
void afficher_plateau(t_plateau *P);

#include "plateau.c"
#endif // PLATEAU_H_INCLUDED
