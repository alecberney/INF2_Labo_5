/*
 -----------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Outils.h
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Prototyper différentes fonctions utiles à différentes statistiques
               (somme, moyenne et médiane) de taxes sur les Bateau d'un Port,
               ainsi qu'à l'affichage de ces dernières, de Bateau et de Port.
               Pour se faire, les constantes globales stockant le type de Bateau
               (Voilier ou Motorise), l'utilité d'un bateau (Peche ou Plaisance),
               ainsi que tous les types de Bateau (Voilier, Motorise Peche,
               Motorise Plaisance) sont ici déclarées.

 Remarque(s) : - Si le tableau trié contient un nombre pair d'éléments, la médiane
                 est calculée en prenant l'élément d'indice égal à la partie entière
                 INFERIEURE de ((n+1)/2) -1.

 Compilateur : MinGW-gcc 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef INF2_LABO5_OUTILS_H
#define INF2_LABO5_OUTILS_H

#include "Port.h"

#define NB_TYPE_BATEAUX 3

enum TypeBateau {VOILIER, BATEAU_PECHE, BATEAU_PLAISANCE};

extern const char* TYPE_BATEAU_AFFICHAGE[2];
extern const char* UTILITE_BATEAU_AFFICHAGE[2];
extern const char* TOUS_TYPES_BATEAU_AFFICHAGE[NB_TYPE_BATEAUX];

uint16_t* getNbBateauxParType(const Port* p);

void getTabTaxesParBateaux(const Port* p, double* tabTaxesPlaisance, double* tabTaxesPeche, double* tabTaxesVoilier);

// Fonction de comparaison pour le tri (qsort)
int cmpfunc(const void* a, const void* b);

// Fonction qui remplit le tableau tab Taxes avec la moyenne des taxes annuelles, par type
double* calculerMoyenneTaxesAnnuellesParType(const Port* p);

// Fonction qui remplit le tableau tab Taxes avec la médiane des taxes annuelles, par type
double* calculerMedianeTaxesAnnuellesParType(const Port* p);

// Fonction qui remplit le tableau tab Taxes avec la somme des taxes annuelles, par type
double* calculerSommeTotaleTaxesAnnuellesParType(const Port* p);

void afficherTaxesParType(const Port* p);

void afficherBateauxPort(const Port* p);

void afficherBateau(const Bateau* b);

void afficherTabTaxesParType(double* tabTaxesParType);

#endif //INF2_LABO5_OUTILS_H
