/*
 -------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Outils.h
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Différentes fonctions utiles à différentes statistiques
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
 -------------------------------------------------------------------------------
 */

#ifndef INF2_LABO5_OUTILS_H
#define INF2_LABO5_OUTILS_H


#include <stdint.h>
#include "Bateau.h"

#define NB_TYPE_BATEAUX 3

#define TAXE_BASE_VOILIER 50.0
#define TAXE_BASE_BATEAU_MOTEUR 100.0

#define TAILE_VOILURE_TAXE_SUPP 200.0
#define TAXE_SPECIFIQUE_MAX_VOILIER 25.0
#define TAXE_SPECIFIQUE_MIN_VOILIER 0.0

#define TONNES_POISSONS_TAXE_SUPP 20.0
#define TAXE_SPECIFIQUE_MAX_PECHE 100.0
#define TAXE_SPECIFIQUE_MIN_PECHE 0.0

#define PUISSANCE_MOTEUR_TAXE_SUPP 100.0
#define TAXE_SPECIFIQUE_MAX_PLAISANCE(longueurEnM) ((longueurEnM) * 15.0)
#define TAXE_SPECIFIQUE_MIN_PLAISANCE 50.0

enum TypeBateau {VOILIER, BATEAU_PECHE, BATEAU_PLAISANCE};

extern const char* TYPE_BATEAU_AFFICHAGE[2];
extern const char* UTILITE_BATEAU_AFFICHAGE[2];
extern const char* TOUS_TYPES_BATEAU_AFFICHAGE[NB_TYPE_BATEAUX];

uint16_t* getNbBateauxParType(const Bateau** port, size_t taille);

void getTabTaxesParBateaux(const Bateau** port, size_t taille,
                           double* tabTaxesPlaisance, double* tabTaxesPeche,
                           double* tabTaxesVoilier);

// Fonction de comparaison pour le tri (qsort)
int cmpfunc(const void* a, const void* b);

double calculTaxeAnnuelle(const Bateau* b);

// Fonction qui remplit le tableau tab Taxes avec la moyenne des taxes annuelles, par type
double* calculerMoyenneTaxesAnnuellesParType(const Bateau** port, size_t taille);

// Fonction qui remplit le tableau tab Taxes avec la médiane des taxes annuelles, par type
double* calculerMedianeTaxesAnnuellesParType(const Bateau** port, size_t taille);

// Fonction qui remplit le tableau tab Taxes avec la somme des taxes annuelles, par type
double* calculerSommeTotaleTaxesAnnuellesParType(const Bateau** port, size_t taille);

void afficherTaxesParType(const Bateau** port, size_t taille);

void afficherBateauxPort(const Bateau** port, size_t taille);

void afficherBateau(const Bateau* b);

void afficherTabTaxesParType(double* tabTaxesParType);

#endif //INF2_LABO5_OUTILS_H
