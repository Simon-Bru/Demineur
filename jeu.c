/// FONCTION CONSTRUCTRICE DE STRUCT PARTIE
t_partie* setPartie(int bombs, int cases){
    t_partie* partie = (t_partie*)malloc(sizeof(t_partie));

    partie->bomb_nb = bombs;
    partie->cases_restante = cases;
    return partie;
}

/// FONCTION DE DEPLACEMENT DU CURSEUR
void placer_curseur( COORD *curseur , int lig, int col)
{
    curseur->X = lig;
    curseur->Y = col;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), *curseur );
}

/// FONCTION DE DEPLACEMENT DU CURSEUR
void gotoligcol(int lig, int col){
    COORD pos;
    pos.X = lig;
    pos.Y = col;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

/// AFFICHAGE DES INSTRUCTIONS
void afficher_instructions(int bomb_nb){
    //COORD *pos;
    //gotoligcol(pos, 0, 8);
    printf("BOMBES TOTALES: %d\n", bomb_nb);

    printf("\nDeplacez vous avec les fleches directionnelles, \nAppuyez sur espace pour placer un drapeau \nEt sur Entree pour decouvrir la case.\n");
}

/// FONCTION DE MISE A JOUR DU NOMBRE DE BOMBES
void maj_bombes(t_plateau* plateau, int bomb_nb){

    gotoligcol(16, plateau->lig*2+1);
    printf("        ");
    gotoligcol(16, plateau->lig*2+1);
    printf("%d", bomb_nb);
}

/// FONCTION D'INITIALISATION DU PLATEAU
void startGame(int lon, int larg, int bomb_nb){
    ///-----------------------  INITIALISATION DE LA PARTIE ----------------\\\

    t_partie* partie = setPartie(bomb_nb, lon*larg);

    ///-----------------------  INITIALISATION DU PLATEAU ----------------\\\

    t_plateau *plateau = setPlateau(lon, larg);
    afficher_plateau(plateau);
    afficher_instructions(bomb_nb);

    ///------------------------ INITIALISATION DES CASES ------------------------------\\\
    //Création de la matrice de cases
    t_case*** case_tab = getCases(lon, larg, bomb_nb);


    /// Boucle permettant la vérification des cases
    /*int i,j;
    for(i=0; i<plateau->col; i++){
        for(j=0; j<plateau->lig; j++){
            if(case_tab[i][j]->indice == -1)
                printf("B ");
            else
                printf("%d ", case_tab[i][j]->indice);
        }
        printf("\n");
    }*/

    ///------------------------ INITIALISATION DES EVENEMENTS -----------------------\\\

    initKeys(plateau, case_tab, partie);

}

void mainMenu(){
    /// PERSONNALISATION COULEUR
    system("color 3");


    /// MESSAGE DACCUEIL
    printf(" /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\--- DEMINEUR ---/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n\n\n\n");
    /// CHOIX
    printf("Veuillez choisir l'action:\n1 - Facile\n2 - Moyen\n3 - Difficile\n4 - Personnalise\n\n");

    char entree[2];
    int choix = 0;
    int i, dimensions[2], mines;
    while(choix == 0){
        printf("No de choix:");
        choix = 0;

        /// ON RECUPERE L'ENTREE COMME UNE CHAINE DEPUIS LE CHAMPS DE LA CONSOLE
        fgets(entree, sizeof(choix), stdin);
        /// ON LE CONVERTI EN ENTIER GRACE A UNE FONCTION DEDIEE
        sscanf(entree, "%d", &choix);

        /// SI CHOIX EST BIEN UN ENTIER
        if(choix != 0){

            /// ON REALISE LACTION CORRESPONDANT AU NUMERO ENTRE
            switch(choix){
                case 1:
                    /// DEBUT D'UNE PARTIE EN FACILE
                    startGame(8, 8, 10);
                    break;
                case 2:
                    /// MOYEN
                    startGame(15, 15, 45);
                    break;
                case 3:
                    /// DIFFICILE
                    startGame(20, 20, 80);
                    break;
                case 4:
                    ///PERSONNALISE
                    printf("Personnalisation du plateau et du nombre de mines\n");
                    for(i=0; i<3; i++){
                        choix = 0;

                        switch(i){
                            case 0:
                                printf("\nEntrez la longueur du plateau choisie: ");
                                break;
                            case 1:
                                printf("\nEntrez la largeur du plateau choisie: ");
                                break;
                            case 2:
                                printf("\nEntrez le nombre de mines choisi: ");
                                break;
                        }

                        while(choix==0){
                            /// ON RECUPERE L'ENTREE COMME UNE CHAINE DEPUIS LE CHAMPS DE LA CONSOLE
                            fgets(entree, sizeof(choix), stdin);
                            /// ON LE CONVERTI EN ENTIER GRACE A UNE FONCTION DEDIEE
                            sscanf(entree, "%d", &choix);
                            if(i < 2){
                               if(choix > 5 && choix < 100){
                                    dimensions[i] = choix;
                                }
                                else {
                                    choix = 0;
                                    printf("Veuillez entrer un nombre entre 5 et 100: ");
                                }
                            }
                            else {
                                if(choix > 5 && choix < ((dimensions[0]*dimensions[1])-5)){
                                    mines = choix;
                                }
                                else {
                                    choix = 0;
                                    printf("Veuillez entrer un nombre entre 5 et %d: ", (dimensions[0]*dimensions[1])-5);

                                }
                            }
                        }
                    }

                    startGame(dimensions[0], dimensions[1], mines);
                    break;
                default:
                    /// L'ENTIER N'EST NI 1 NI 2 NI 3, ON DEMADE DE LE RE-ENTRER
                    printf("Veuillez entrer un numero valide\n");
                    choix = 0;
                    break;
            }
        }
        else {
            /// L'ENTREE N'EST PAS UN ENTIER, ON DEMANDE DE LE RE-ENTRER
            printf("Veuillez entrer un numéro valide\n");
        }
    }
}

void initKeys(t_plateau *plateau, t_case*** case_tab, t_partie* partie){
    ///ON INITIALISE LA CLE TAPE AU CLAVIER
    int key = 0;
    COORD *curPos = malloc(sizeof(COORD));
    placer_curseur(curPos, 1, 1);

    ///On initialise une variable compteur de drapeaux
    int cp_flags = 0;

    /// On initialise des entiers utilisés pour stocker la position actuelle lors d'affichages
    int posX, posY;

    /// On crée une variable pour la case sur laquelle l'utilisateur est positionné
    t_case* curCase = case_tab[0][0];

    /// On initialise un booleen pour la fin de la partie
    int fini = 0;

     while(key != 113 && !fini){

        ///On vérifie que toutes les cases ne sont pas découvertes
        if(partie->cases_restante == partie->bomb_nb){
            printf("VICTOIRE");
            fini = 1;
        }

        /// ON ECOUTE L'APPUI SUR UNE TOUCHE DU CLAVIER
        if(kbhit()){
            /// ON REDEFINI LA CASE COURANTE
            curCase = case_tab[curPos->Y/2][curPos->X/2];

            /// ON RECUPERE LE CODE DE CETTE TOUCHE
            key = getch();

            /// SWITCH POUR LE CODE DE LA TOUCHE
            switch(key){
                case 72:
                    /// TOUCHE FLECHE DU HAUT
                    if(curPos->Y > 1){
                        placer_curseur(curPos, curPos->X, (curPos->Y-2));
                    }
                    break;
                case 75:
                    ///TOUCHE FLECHE DE GAUCHE
                    if(curPos->X > 1){
                       placer_curseur(curPos, curPos->X-2, curPos->Y);
                    }
                    break;
                case 77:
                    ///TOUCHE FLECHE DE DROITE
                    if(curPos->X < plateau->col*2-1){
                        placer_curseur(curPos, curPos->X+2, curPos->Y);
                    }
                    break;
                case 80:
                    ///TOUCHE FLECHE DU BAS
                    if(curPos->Y < plateau->lig*2-1){
                       placer_curseur(curPos, curPos->X, curPos->Y+2);
                    }
                    break;

                case 32:
                    /// TOUCHE ESPACE - AJOUT D'UN DRAPEAU
                    /// On vérifie que la case n'est pas découverte et que tous les drapeaux ne sont pas placés
                    if(curCase->vu == 0 && partie->bomb_nb-cp_flags > 0 || curCase->vu == 0 && curCase->flag){
                        /// On ajoute un drapeau à la case courante
                        int flagged = addFlag(curCase);
                        /// Selon le résultat de retour, on affiche le drapeau ou un espace
                        char flag = flagged ? 207 : 0;
                        printf("%c", flag);

                        /// On incrémente ou décrémente le compteur de drapeaux
                        cp_flags = flagged ? cp_flags+1 : cp_flags-1;
                        /// On met a jour le nombre de bombes affiché
                        maj_bombes(plateau, partie->bomb_nb-cp_flags);

                        /// On se replace sur la case courante
                        placer_curseur(curPos, curPos->X, curPos->Y);
                    }
                    break;

                case 13:
                    /// TOUCHE ENTREE - DECOUVERTE DE LA CASE

                    /// On stocke les coordonnées initiales de la position du curseur
                    posX = curPos->X;
                    posY = curPos->Y;

                    /// Si cette case n'est pas une bombe
                    if(!isBomb(curCase)){
                        /// On appelle la fonction d'affichage qui gère également l'affichage des voisins d'une case vide
                        printCase(case_tab, curPos, plateau, &partie->cases_restante);
                    }
                    else {
                        /// Sinon on affiche la défaite
                        //printf("DEFAITE");
                        fini = 1;
                        /// On révèle la grille
                        revelerGrille(case_tab, plateau, &partie->cases_restante);
                    }

                    /// On place le curseur à sa position initiale
                    placer_curseur(curPos, posX, posY);

                    break;
            }
        }
    }
}
