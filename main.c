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
    /// Initialisation de la graine utilis�e lors de l'appel � rand() afin de g�n�rer un nombre al�atoire en fonction du temps
    srand(time(0));

    mainMenu();
}
