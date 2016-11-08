#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

/// FONCTION DE DEPLACEMENT DU CURSEUR
void gotoligcol( COORD *curseur , int lig, int col);

///FONCTION DE DEMARRAGE DU JEU
void mainMenu();

///FONCTION DE DEMMARRAGE DE LA PARTIE
void startGame(int lon, int larg);

/// FONCTION D'INITIALISATION DES EVENEMENTS A L'APPUI DES TOUCHES
void initKeys(t_plateau *plateau);

#include "jeu.c"
#endif // JEU_H_INCLUDED