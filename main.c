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

   Bateau* port[NB_BATEAUX_PORT] =
           {
                 creeBateauAVoile("Voilier1", 199),
                 creeBateauAVoile("Voilier2", 200),
                 creeBateauAVoile("Voilier3", 210),

                 creeBateauPeche("Peche1", 10, 19),
                 creeBateauPeche("Peche2", 15, 20),
                 creeBateauPeche("Peche3", 20, 25),
                 creeBateauPeche("Peche4", 25, 30),

                 creeBateauPlaisance("Plaisance1",  99, 32, "Proprietaire1"),
                 creeBateauPlaisance("Plaisance2", 100, 35, "Proprietaire2"),
                 creeBateauPlaisance("Plaisance3", 110, 20, "Proprietaire3"),
                 creeBateauPlaisance("Plaisance4", 120, 30, "Proprietaire4"),
                 creeBateauPlaisance("Plaisance5", 130, 40, "Proprietaire5")
           };


   printf("Affiche tous les bateaux du port : \n");
   printf("===================================\n");
   afficherBateauxPort((const Bateau**) port, NB_BATEAUX_PORT);

   printf("Affiche tous les calculs en rapport avec les taxes : \n");
   printf("=====================================================\n");
   afficherTaxesParType((const Bateau**) port, NB_BATEAUX_PORT);


   return EXIT_SUCCESS;
}
