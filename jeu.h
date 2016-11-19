#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

///-----------------------------------------  STRUCURE PARTIE  -----------------------------------------------------\\\

typedef struct Partie {
    int bomb_nb;
    int case_restante;
}t_partie;

/// FONCTION CONSTRUCTRICE DE STRUCT PARTIE
t_partie* setPartie(int bombs, int cases);

/// FONCTION DE DEPLACEMENT DU POINTEUR DU CURSEUR DE POSITION COURANTE
void placer_curseur( COORD *curseur , int lig, int col);

/// FONCTION DE DEPLACEMENT DU CURSEUR
void gotoligcol(int lig, int col);

/// AFFICHAGE DES INSTRUCTIONS
void afficher_instructions(int bomb_nb);

/// FONCTION DE MISE A JOUR DU NOMBRE DE BOMBES
void maj_bombes(t_plateau* plateau, int bomb_nb);

///FONCTION DE DEMARRAGE DU JEU
void mainMenu();

///FONCTION DE DEMMARRAGE DE LA PARTIE
void startGame(int lon, int larg, int bomb_nb);

/// FONCTION D'INITIALISATION DES EVENEMENTS A L'APPUI DES TOUCHES
void initKeys(t_plateau *plateau, t_case*** case_tab, t_partie* partie);

#include "jeu.c"
#endif // JEU_H_INCLUDED
