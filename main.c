/*
 -----------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : main.c
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Tester les différents éléments implémentés pour modéliser un Port
               contenant plusieurs Bateaux de différents types, selon lesquels
               sont dues des taxes annuelles.

 Remarque(s) : - Le but de ce laboratoire est de pratiquer l'allocation dynamique,
                 les structures, les unions et les types énumérés.

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
   Bateau* voile1 = creeBateauAVoile("Voilier1", 199);
   Bateau* voile2 = creeBateauAVoile("Voilier2", 200);
   Bateau* voile3 = creeBateauAVoile("Voilier3", 210);

   Bateau* peche1 = creeBateauPeche("Peche1", 10, 19);
   Bateau* peche2 = creeBateauPeche("Peche2", 15, 20);
   Bateau* peche3 = creeBateauPeche("Peche3", 20, 25);
   Bateau* peche4 = creeBateauPeche("Peche4", 25, 30);

   Bateau* plaisance1 = creeBateauPlaisance("Plaisance1",  99, 32, "Proprietaire1");
   Bateau* plaisance2 = creeBateauPlaisance("Plaisance2", 100, 35, "Proprietaire2");
   Bateau* plaisance3 = creeBateauPlaisance("Plaisance3", 110, 20, "Proprietaire3");
   Bateau* plaisance4 = creeBateauPlaisance("Plaisance4", 120, 30, "Proprietaire4");
   Bateau* plaisance5 = creeBateauPlaisance("Plaisance5", 130, 40, "Proprietaire5");

   Port* p = construitPort(NB_BATEAUX_PORT);

   ajouteBateau(p,     voile1);
   ajouteBateau(p,     peche1);
   ajouteBateau(p,     voile2);
   ajouteBateau(p, plaisance1);
   ajouteBateau(p, plaisance2);
   ajouteBateau(p,     peche2);
   ajouteBateau(p, plaisance3);
   ajouteBateau(p,     peche4);
   ajouteBateau(p,     voile3);
   ajouteBateau(p, plaisance4);
   ajouteBateau(p,     peche3);
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
