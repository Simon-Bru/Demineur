#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "plateau.h"
#include "case.h"
#include "jeu.h"

/// MENU PRINCIPAL
int main()
{
    system("mode con LINES=50 COLS=160");
    /// Initialisation de la graine utilisée lors de l'appel à rand() afin de générer un nombre aléatoire en fonction du temps
    srand(time(NULL));

    mainMenu();
}
