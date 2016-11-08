/// FONCTION DE DEPLACEMENT DU CURSEUR
void gotoligcol( COORD *curseur , int lig, int col)
{
    curseur->X = curseur->X != lig ? lig+1 : curseur->X;
    curseur->Y = curseur->Y != col ? col+1 : curseur->Y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), *curseur );
}

/// FONCTION D'INITIALISATION DU PLATEAU
void startGame(int lon, int larg){
    ///-----------------------  INITIALISATION DU PLATEAU ----------------\\\

    t_plateau *plateau = setPlateau(lon, larg);
    afficher_plateau(plateau);

    ///------------------------ INITIALISATION DES CASES ------------------------------\\\


    ///------------------------ INITIALISATION DES EVENEMENTS -----------------------\\\

    initKeys(plateau);

}

void mainMenu(){
    /// PERSONNALISATION COULEUR
    system("color 3");


    /// MESSAGE DACCUEIL
    printf(" /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\--- DEMINEUR ---/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n\n\n\n");
    /// CHOIX
    printf("Veuillez choisir l'action:\n1 - Facile\n2 - Moyen\n3 - Difficile\n4 - Personnalisé\n\n");

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
                    startGame(8, 8);
                    break;
                case 2:
                    /// MOYEN
                    startGame(15, 15);
                    break;
                case 3:
                    /// DIFFICILE
                    startGame(20, 20);
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

                    startGame(dimensions[0], dimensions[1]);
                    break;
                default:
                    /// L'ENTIER N'EST NI 1 NI 2 NI 3, ON DEMADE DE LE RE-ENTRER
                    printf("Veuillez entrer un numéro valide\n");
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

void initKeys(t_plateau *plateau){
    ///ON INITIALISE LA CLE TAPE AU CLAVIER
    int key = 0;
    COORD *curPos = malloc(sizeof(COORD));
    gotoligcol(curPos, 0, 0);

    /// TANT QUE L'UTILISATEUR NE TAPE PAS Q
    while(key != 113){

        /// ON ECOUTE L'APPUI SUR UNE TOUCHE DU CLAVIER
        if(kbhit()){

            /// ON RECUPERE LE CODE DE CETTE TOUCHE
            key = getch();

            /// SWITCH POUR LE CODE DE LA TOUCHE
            switch(key){
                case 72:
                    /// TOUCHE FLECHE DU HAUT
                    if(curPos->Y > 1){
                        gotoligcol(curPos, curPos->X, (curPos->Y-3));
                    }
                    break;
                case 75:
                    ///TOUCHE FLECHE DE GAUCHE
                    if(curPos->X > 1){
                       gotoligcol(curPos, curPos->X-3, curPos->Y);
                    }
                    break;
                case 77:
                    ///TOUCHE FLECHE DE DROITE
                    if(curPos->X < plateau->col*2-1){
                        gotoligcol(curPos, curPos->X+1, curPos->Y);
                    }
                    break;
                case 80:
                    ///TOUCHE FLECHE DU BAS
                    if(curPos->Y < plateau->lig*2-1){
                       gotoligcol(curPos, curPos->X, curPos->Y+1);
                    }
                    break;

                case 32:
                    /// TOUCHE ESPACE - AJOUT D'UN DRAPEAU
                    break;

                case 13:
                    /// TOUCHE ENTREE - DECOUVERTE DE LA CASE
                    break;
            }
        }
    }
}
