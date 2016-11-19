#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

///-----------------------------------------  STRUCURE CASE -----------------------------------------------------\\\

typedef struct Case
{
    int indice;
    int flag;
    int vu;
}t_case;

/// Fonction constructeur de structure case
t_case* setCase(int ind);

/// FONCTION D'AJOUT DE DRAPEAU
int addFlag(t_case* cas);

/// FONCTION D'INCREMENTATION D'INDICE
void incrementIndice(t_case* cas);

/// FONCTION DE DEFINITION DE BOMBE (remplacement de l'indice par -1)
void setBombe(t_case* cas);

/// FONCTION DE VERIFICATION SI LA CASE EST BOMBE OU NON
int isBomb(t_case* cas);

/// FONCTION DE DECOUVERTE DE CASE
void printCase(t_case*** case_tab, COORD* pos, t_plateau* plateau, int* cases_restantes);

/// FONCTION DE DECOUVERTE DES VOISINS D'UN ZERO
int decouvrirVoisins (t_case*** case_tab, COORD* pos, t_plateau* plateau, int* cases_restantes);

/// FONCTION D'INITIALISATION DES BOMBES ALEATOIRES
void initBombes(t_case*** case_tab[], int lon, int larg, int bombs);

/// FONCTION D'INITIALISATION DE LA MATRICE DE CASES AVEC L'INDICE 0
void initCases(t_case*** case_tab[], int lon, int larg);

/// FONCTION DE CREATION DE LA MATRICE DE CASES DE LONGUEUR ET DE LARGEUR PASSEES EN PARAMETRES
t_case*** getCases(int lon, int larg, int bombs);



#include "case.c"

#endif // CASE_H_INCLUDED
