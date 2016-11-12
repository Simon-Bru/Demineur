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
void addFlag(t_case* cas) {
    cas->flag = 1;
}

/// FONCTION D'INCREMENTATION D'INDICE
void incrementIndice(t_case* cas){
    cas->indice++;
}

/// FONCTION DE DEFINITION DE BOMBE
void setBombe(t_case* cas){
    cas->indice = -1;
}

/// FONCTION DE DECOUVERTE DE CASE
/*
void seeCase(t_case* case_tab, COORD* pos){
    t_case* curCase = case_tab[(pos->X-1)/2][(pos->Y-1)/2];
    curCase->vu = 1;
    if(curCase->indice > 0){
        printf("%d", curCase->indice);
    }
    else {
        printf("boum");
    }
}*/

/// FONCTION D'INITIALISATION DES BOMBES ALEATOIRES
void initBombes(t_case*** case_tab[], int lon, int larg, int bombs){
    int i, x, y, indice, addX, addY;
    for(i = 0; i < bombs; i++){
        /// ON GENERE DEUX NOMBRES ENTRE 0 ET LA LONGUEUR/LARGEUR MAX
        x = rand()%lon;
        y = rand()%larg;

        /// ON REDEFINI L'INDICE DE LA CASE CORRESPONDANT AUX NOMBRES RANDOM
        setBombe(case_tab[x][y]);

        /// ON VERIFIE SI LA BOMBE N'EST PAS CONTRE UNE BORDURE
        int minX, minY, maxX, maxY;
        minX = x==0 ? 0 : -1;
        maxX = x==larg-1 ? 0 : 1;
        minY = y==0 ? 0 : -1;
        maxY = y==lon-1 ? 0 : 1;

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
