/*
 -----------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Port.h
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Définir différentes structures servant à modéliser un Port contenant
               différents types de Bateau, et
               prototyper des fonctions utiles à la gestion d'un Port.
               Pour se faire, on définit également différentes macros qui servent
               à stocker les différentes valeurs constantes avec lesquelles nous
               travaillons ici.

 Remarque(s) : -

 Compilateur : MinGW-gcc 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef INF2_LABO5_PORT_H
#define INF2_LABO5_PORT_H

#include "Bateau.h"

#define TAXE_BASE_VOILIER 50.0
#define TAXE_BASE_BATEAU_MOTEUR 100.0

#define TAILLE_VOILURE_TAXE_SUPP 200.0
#define TAXE_SPECIFIQUE_MAX_VOILIER 25.0
#define TAXE_SPECIFIQUE_MIN_VOILIER 0.0

#define TONNES_POISSONS_TAXE_SUPP 20.0
#define TAXE_SPECIFIQUE_MAX_PECHE 100.0
#define TAXE_SPECIFIQUE_MIN_PECHE 0.0

#define PUISSANCE_MOTEUR_TAXE_SUPP 100.0
#define TAXE_SPECIFIQUE_MAX_PLAISANCE(longueurEnM) ((longueurEnM) * 15.0)
#define TAXE_SPECIFIQUE_MIN_PLAISANCE 50.0

typedef struct Port
{
   Bateau**  bateaux;
   uint16_t capacite;
   uint16_t   taille;
} Port;

Port* construitPort(uint16_t capacite);

// Détruit le port et tous les bateaux présents
void detruitPortEtBateaux(Port* p);

// Renvoie la position du bateau en cas de réussite
// Renvoie -1 si le bateau n'est pas le port.
int trouveBateau(const Port* p, const Bateau* b);

void ajouteBateau(Port* p, Bateau* b);

// L'ordre des bateaux dans le port peut-être modifié
void supprimeBateau(Port* p, const Bateau* b);

double calculTaxeAnnuelle(const Bateau* b);

#endif //INF2_LABO5_PORT_H
