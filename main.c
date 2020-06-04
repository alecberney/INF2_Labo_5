/*
 -----------------------------------------------------------------------------------
 Laboratoire : 05
 Fichier     : main.c
 Auteur(s)   : Berney Alec, Quentin Forestier et Victoria Logan
 Date        : 03.06.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-gcc 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bateau.h"
#include "Port.h"
#include "Outils.h"

#define NB_BATEAUX_PORT 15

int main()
{
   Bateau* voile = creeBateauAVoile("Voilier", 199);
   Bateau* voile2 = creeBateauAVoile("Voilier2", 200);
   Bateau* voile3 = creeBateauAVoile("Voilier3", 210);
   Bateau* voile4 = creeBateauAVoile("Voilier4", 220);
   Bateau* voile5 = creeBateauAVoile("Voilier5", 230);
   Bateau* peche = creeBateauPeche("Peche", 10, 19);
   Bateau* peche2 = creeBateauPeche("Peche2", 15, 20);
   Bateau* peche3 = creeBateauPeche("Peche3", 20, 25);
   Bateau* peche4 = creeBateauPeche("Peche4", 25, 30);
   Bateau* peche5 = creeBateauPeche("Peche5", 30, 35);
   Bateau* plaisance = creeBateauPlaisance("Plaisance", 99, 32, "Proprio");
   Bateau* plaisance2 = creeBateauPlaisance("Plaisance2", 100, 35, "Proprio2");
   Bateau* plaisance3 = creeBateauPlaisance("Plaisance3", 110, 20, "Proprio3");
   Bateau* plaisance4 = creeBateauPlaisance("Plaisance4", 120, 30, "Proprio4");
   Bateau* plaisance5 = creeBateauPlaisance("Plaisance5", 130, 40, "Proprio5");

   Port* p = construitPort(NB_BATEAUX_PORT);
   ajouteBateau(p, voile);
   ajouteBateau(p, voile2);
   ajouteBateau(p, voile3);
   ajouteBateau(p, voile4);
   ajouteBateau(p, voile5);
   ajouteBateau(p, peche);
   ajouteBateau(p, peche2);
   ajouteBateau(p, peche3);
   ajouteBateau(p, peche4);
   ajouteBateau(p, peche5);
   ajouteBateau(p, plaisance);
   ajouteBateau(p, plaisance2);
   ajouteBateau(p, plaisance3);
   ajouteBateau(p, plaisance4);
   ajouteBateau(p, plaisance5);

   printf("Affiche tous les bateaux du port : \n");
   printf("===================================\n");
   afficherBateauxPort(p);

   printf("Affiche tous les calculs en rapport avec les taxes : \n");
   printf("=====================================================\n");
   afficherTaxesParType(p);

   detruitPortEtBateaux(p);

   return EXIT_SUCCESS;
}
