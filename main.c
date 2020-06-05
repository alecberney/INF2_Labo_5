/*
 -------------------------------------------------------------------------------
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
 -------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include "Bateau.h"
#include "Outils.h"

#define NB_BATEAUX_PORT 12

int main()
{
   Bateau* voilier1 = creeBateauAVoile("Voilier1", 199);
   Bateau* voilier2 = creeBateauAVoile("Voilier2", 200);
   Bateau* voilier3 = creeBateauAVoile("Voilier3", 210);

   Bateau* peche1 =  creeBateauPeche("Peche1", 10, 19);
   Bateau* peche2 =  creeBateauPeche("Peche2", 15, 20);
   Bateau* peche3 =  creeBateauPeche("Peche3", 20, 25);
   Bateau* peche4 =  creeBateauPeche("Peche4", 25, 30);

   Bateau* plaisance1 =  creeBateauPlaisance("Plaisance1",  99, 32, "Proprietaire1");
   Bateau* plaisance2 =  creeBateauPlaisance("Plaisance2", 100, 35, "Proprietaire2");
   Bateau* plaisance3 =  creeBateauPlaisance("Plaisance3", 110, 20, "Proprietaire3");
   Bateau* plaisance4 =  creeBateauPlaisance("Plaisance4", 120, 30, "Proprietaire4");
   Bateau* plaisance5 =  creeBateauPlaisance("Plaisance5", 130, 40, "Proprietaire5");

   Bateau* port[NB_BATEAUX_PORT] =
           {
                 voilier1, voilier2, voilier3,
                 peche1, peche2, peche3, peche4,
                 plaisance1, plaisance2, plaisance3, plaisance4, plaisance5
           };


   printf("Affiche tous les bateaux du port : \n");
   printf("===================================\n");
   afficherBateauxPort((const Bateau**) port, NB_BATEAUX_PORT);

   printf("Affiche tous les calculs en rapport avec les taxes : \n");
   printf("=====================================================\n");
   afficherTaxesParType((const Bateau**) port, NB_BATEAUX_PORT);


   return EXIT_SUCCESS;
}
