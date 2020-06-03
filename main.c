/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : main.c
 Auteur(s)   : Quentin Forestier
 Date        : 03.06.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bateau.h"
#include "Port.h"
#include "Outils.h"

int main()
{
   Bateau* voile = creeBateauAVoile("Voilier", 199);
   Bateau* voile2 = creeBateauAVoile("Voilier2", 200);
   Bateau* peche = creeBateauPeche("Peche", 10, 19);
   Bateau* peche2 = creeBateauPeche("Peche2", 15, 20);
   Bateau* plaisance = creeBateauPlaisance("Plaisance", 99, 32, "Proprio");
   Bateau* plaisance2 = creeBateauPlaisance("Plaisance2", 100, 35, "Proprio2");

   Port* p = construitPort(NB_BATEAUX_PORTS);
   ajouteBateau(p, voile);
   ajouteBateau(p, voile2);
   ajouteBateau(p, peche);
   ajouteBateau(p, peche2);
   ajouteBateau(p, plaisance);
   ajouteBateau(p, plaisance2);

   afficherBateauxPort(p);
   afficherTaxesParType(p);

   detruitPortEtBateaux(p);

   return EXIT_SUCCESS;
}
