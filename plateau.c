
///Constructeur pour le plateau. INITIALISATION DES ATTRIBUTS
t_plateau* setPlateau( int longueur, int largeur)
{
    ///INITIALISATION POINTEUR
    t_plateau *ptr_plateau;
    ///ALLOCATION DYNAMIQUE DE LA VARIABLE EN DEFINISSANT LE POINTEUR GRACE AU MALLOC
    ptr_plateau = malloc(sizeof(t_plateau));

    ///INITIALISATION DES ATTRIBUTS
    ptr_plateau->lig = longueur;
    ptr_plateau->col = largeur;
    ///ON RETOURNE LE POINTEUR ALLOUE
    return ptr_plateau;
}

/// FONCTION D'AFFICHAGE DU PLATEAU
void afficher_plateau(t_plateau *P){
    ///On efface le contenu de la console
    system("cls");
    int i, j;
    char lig, col;
    /*char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /// INDEXATION DES ABSCISSES GRACE A DES LETTRES
    printf(" ");
    for(i=0; i<P->col; i++){
        printf(" %c", alphabet[i]);
    }
    printf("\n");*/

    /// ON REALISE LA MEME TACHE AUTANT DE FOIS QU'IL Y A DE LIGNES DANS LE PLATEAU
    for(i=0; i<=P->lig*2; i++){
        /*///INDEXATION DES ORDONNEES
        if(i%2 == 0)
            printf(" ");
        else
            printf("%d", i/2+1);*/

        /// ON AFFICHE AUTANT DE CHARACTERE LIGNE POUR LE LA LARGEUR DU PLATEAU
        for(j=0; j <= P->col*2; j++){

            if(i==0){
                /// ON DETERMINE LE CARACTERE A UTILISE EN FONCTION DE LA PARITE DE J
                char charLig = j%2 == 0 ? 203 : 205;
                /// ANGLE HAUT GAUCHE
                lig = j == 0 ? 201 : charLig;
                /// ANGLE HAUT DROITE
                lig = j == (P->col*2) ? 187 : lig;
            }
            else if(i==P->lig*2){
                /// ON DETERMINE LE CARACTERE A UTILISE EN FONCTION DE LA PARITE DE J
                /// CARACTERE LIGNE AVEC BARRE VERTICALE OU CARACTERE LIGNE
                char charLig = j%2 == 0 ? 202 : 205;
                /// ANGLE BAS GAUCHE SI PREMIER PASSAGE DANS BOUCLE
                lig = j == 0 ? 200 : charLig;
                /// ANGLE BAS DROITE SI DERNIER PASSAGE DANS BOUCLE
                lig = j == (P->col*2) ? 188 : lig;
            }
            else {
                if(i%2 == 0){
                    /// SELON LA PARITE DE J: LIGNE VERTICALE OU CROIX
                    lig = j%2 == 0 ? 206 : 205;
                    ///PREMIER CARACTERE
                    lig = j == 0 ? 204 : lig;
                    /// DERNIER CARACTERE
                    lig = j == P->col*2 ? 185 : lig;
                }
                else {
                    /// LIGNE VERTICALE OU ESPACE
                    lig = j%2 == 0 ? 186 : 219;
                }
            }
            /// ON AFFICHE LE CARACTERE DETERMINE
            printf("%c", lig);
        }
        /// ON VA A LA LIGNE
        printf("\n");

    }
}
