/// FONCTION CONSTRUCTEUR DE STRUCTURE CASE BASIQUE
t_case* setCase(int ind) {
    /// ALLOCATION DE LA MEMOIRE
    t_case* cas = malloc(sizeof(t_case));

    /// INITIALISATION DES ATTRIBUTS
    cas->indice = ind;
    cas->flag = 0;
    cas->vu = 0;

    return cas;
}

/// FONCTION D'AJOUT DE DRAPEAU
int addFlag(t_case* cas) {
    /// Si le drapeau est déjà attribué, on le supprime (0), sinon, on le rajoute (1)
    cas->flag = cas->flag ? 0 : 1;
    /// On retourne l'état du drapeau
    return cas->flag;
}

/// FONCTION D'INCREMENTATION D'INDICE
void incrementIndice(t_case* cas){
    if(cas->indice >= 0){
        cas->indice++;
    }
}

/// FONCTION DE DEFINITION DE BOMBE
void setBombe(t_case* cas){
    cas->indice = -1;
}

/// FONCTION DE VERIFICATION SI LA CASE EST BOMBE OU NON
int isBomb(t_case* cas){
    return cas->indice == -1;
}

/// FONCTION DE DECOUVERTE DE CASE
void printCase(t_case*** case_tab, COORD* pos, t_plateau* plateau, int* cases_restantes){
    /// On inverse x et y car la 1ere dimension représente les lignes->Ordonnées(Y) et la 2ème les colonnes->abscisses(X)
    t_case* cas = case_tab[pos->Y/2][pos->X/2];

    /// Si la case n'a pas encore été découverte et qu'elle n'a pas de drapeau
    if(!cas->vu && !cas->flag){

        /// On définit son attribut comme vu
        cas->vu = 1;

        /// On décremente le nombre de cases restantes de notre partie
        *cases_restantes = *cases_restantes-1;

        /// Si cette case n'est pas une bombe
        if(!isBomb(cas)){

            /// Si cette case est un zéro
            if(cas->indice == 0){
                /// On affiche un espace
                printf(" ");
                /// On découvre ses voisins grâce à la fonction dédiée
                decouvrirVoisins(case_tab, pos, plateau, cases_restantes);
            }
            else {
                /// Sinon, On affiche son indice
                printf("%d", cas->indice);
            }
        }
        else {
            /// Si c'est une bombe, on affiche une bombe
            char bomb = 207;
            printf("%c", bomb);
            placer_curseur(pos, pos->X-1, pos->Y);
        }
    }
}

/// FONCTION DE DECOUVERTE DES VOISINS D'UN ZERO
int decouvrirVoisins (t_case*** case_tab, COORD* pos, t_plateau* plateau, int* cases_restantes){
    int i, j, minX, maxX, minY, maxY, curX, curY, x, y;
    /// On stocke les coordonnées de la position initiale
    curX = pos->X;
    curY = pos->Y;

    /// Selon la position du curseur, on définit les bornes des boucles qui vont permettre
    /// de parcourir le contour de la case courante
    minX = curX/2==0 ? 0 : -1;
    maxX = curX/2==plateau->col-1 ? 0 : 1;
    minY = curY/2==0 ? 0 : -1;
    maxY = curY/2==plateau->lig-1 ? 0 : 1;

    /// On initialise les boucles selon les bornes définies
    for(i=minX; i <= maxX; i++){
        for(j=minY; j <= maxY; j++){
            /// On vérifie que la case ne soit pas celle dont on découvre les voisins
            if(!(i == 0 && j == 0)){
                /// On définit les indices de la case selon la position courante et le passage dans la boucle
                y = curY/2+j;
                x = curX/2+i;

                /// On stocke cette case
                t_case* curCase = case_tab[y][x];
                /// Si celle-ci n'est pas une bombe et n'est pas encore découverte
                if(!isBomb(curCase) && !curCase->vu){
                    /// On déplace le curseur dans la case en question
                    placer_curseur(pos, curX+(i*2), curY+(j*2));
                    /// On affiche son indice grâce à la fonction destinée, qui va permettre la découverte récursive
                    /// Si la case en question est un zéro
                    printCase(case_tab, pos, plateau, cases_restantes);
                }
            }
        }
    }
}

/// FONCTION D'INITIALISATION DES BOMBES ALEATOIRES
void initBombes(t_case*** case_tab[], int lon, int larg, int bombs){
    int i, x, y, indice, addX, addY;
    for(i = 0; i < bombs; i++){
        /// ON GENERE DEUX NOMBRES ENTRE 0 ET LA LONGUEUR/LARGEUR MAX
        x = rand()%lon;
        y = rand()%larg;
        while(isBomb(case_tab[x][y])){
            x = rand()%lon;
            y = rand()%larg;
        }


        /// ON REDEFINI L'INDICE DE LA CASE CORRESPONDANT AUX NOMBRES RANDOM
        setBombe(case_tab[x][y]);

        /// ON VERIFIE SI LA BOMBE N'EST PAS CONTRE UNE BORDURE
        int minX, minY, maxX, maxY;
        minX = x==0 ? 0 : -1;
        maxX = x==lon-1 ? 0 : 1;
        minY = y==0 ? 0 : -1;
        maxY = y==larg-1 ? 0 : 1;

        /// ON PARCOURT CHAQUE VOISINS DE LA BOMBE ACTUELLE
        /// ON PARCOURT LES ABSCISSES DE GAUCHES A DROITE
        for(addX=minX; addX <= maxX; addX++){
            /// ON PARCOURT LES ORDONNEES DE BAS EN HAUT
            for(addY=minY; addY <= maxY; addY++){
                /// ON RAJOUTE 1 A L'INDICE DE LA CASE VOISINE
                if(!(addX == 0 && addY == 0))
                    incrementIndice(case_tab[x+addX][y+addY]);
            }
        }
    }
}

/// FONCTION D'INITIALISATION DE LA MATRICE DE CASES AVEC L'INDICE 0
void initCases(t_case*** case_tab[], int lon, int larg){
    int i, j;
    /// PARCOURS DE LA MATRICE
    for(i=0; i < lon; i++){
        /// ON INITIALISE LE TABLEAU EN ALLOUANT LA MEMOIRE NECESSAIRE
        case_tab[i] = malloc(larg*sizeof(**case_tab));

        for(j=0; j < larg; j++){
            /// DEFINITION DE LA CASE
            case_tab[i][j] = setCase(0);
        }
    }
}

/// FONCTION DE CREATION DE LA MATRICE DE CASES D'UNE TAILLE DEFINIE
t_case*** getCases(int lon, int larg, int bombs) {
    t_case*** case_tab = malloc(lon*sizeof(*case_tab));

    ///ON INITIALISE TOUT D'ABORD TOUTES LES CASES DE LA MATRICE A 0
    initCases(case_tab, lon, larg);

    /// ON INITIALISE LES BOMBES ALEATOIREMENT ET ON INCREMENTE L'INDICE DE LEUR VOISIN
    initBombes(case_tab, lon, larg, bombs);

    return case_tab;
}

/// FONCTION DE REVELATION DE LA GRILLE POUR LA FIN DE PARTIE
void revelerGrille(t_case*** case_tab, COORD* curPos, t_plateau* plateau, int* cases_restantes){
    int i, j;
    for(i=1; i<plateau->lig*2; i=i+2){
        for(j=1; j<plateau->col*2; j=j+2){
            if(*cases_restantes > 0){
                placer_curseur(curPos, j, i);
                /// Si la case avait un drapeau
                if(case_tab[curPos->Y/2][curPos->X/2]->flag){
                    /// SI elle contenait une bombe on affiche un v pour valid
                    if(isBomb(case_tab[curPos->Y/2][curPos->X/2]))
                        printf("v");
                    else
                        printf("%c", 158);
                }
                else {
                    printCase(case_tab, curPos, plateau, cases_restantes);
                }
            }
            else {
                break;
            }
        }
    }
}

