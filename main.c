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
    /// Initialisation de la graine utilis�e lors de l'appel � rand() afin de g�n�rer un nombre al�atoire en fonction du temps
    srand(time(NULL));

    mainMenu();
}
