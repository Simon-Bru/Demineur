#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "case.h"
#include "plateau.h"
#include "jeu.h"

/// MENU PRINCIPAL
int main()
{
    /// Initialisation de la graine utilisée lors de l'appel à rand() afin de générer un nombre aléatoire en fonction du temps
    srand(time(0));

    mainMenu();
}
