/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : Outils.h
 Auteur(s)   : Quentin Forestier
 Date        : 03.06.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef INF2_LABO5_OUTILS_H
#define INF2_LABO5_OUTILS_H

#include "Port.h"

#define NB_BATEAUX_PORTS 6
#define NB_TYPE_BATEAUX 3

enum TypeBateau {VOILIER, BATEAU_PECHE, BATEAU_PLAISANCE};


extern const char* TYPE_BATEAU_AFFICHAGE[2];

extern const char* UTILITE_BATEAU_AFFICHAGE[2];

extern const char* TOUS_TYPES_BATEAU_AFFICHAGE[NB_TYPE_BATEAUX];


uint16_t* getNbBateauxParType(const Port* p);

void getTabTaxesParBateaux(const Port* p, double* tabTaxesPlaisance, double* tabTaxesPeche, double* tabTaxesVoilier);


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
