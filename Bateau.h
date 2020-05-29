/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : Bateau.h
 Auteur(s)   : Berney Alec
 Date        : 29.05.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef LABO_MOI_BATEAU_H
#define LABO_MOI_BATEAU_H

#include <inttypes.h>

typedef const char* Nom[20];
typedef enum TYPE_BATEAU { VOILIER, MOTEUR } TypeBateau;
typedef enum TYPE_BATEAU_MOTEUR { PECHE, PLAISANCE } TypeBateauMoteur;

typedef struct BateauMoteurPlaisance {
   uint8_t longueurBateau;
   Nom nomProprietaire;
} BateauMoteurPlaisance;

typedef struct BateauMoteurPeche {
   const uint8_t quantiteAutoriseePoissons; // En tonne
} BateauMoteurPeche;

typedef struct BateauVoilier {
   uint16_t surfaceVoilure; // En m^2
} BateauVoilier;

typedef struct BateauMoteur {
   uint16_t puissanceMoteur; // En CV(cheveaux)
   TypeBateauMoteur typeBateauMoteur;

   union {
      BateauMoteurPlaisance* bateauMoteurPlaisance;
      BateauMoteurPeche* bateauMoteurPeche;
   };
} BateauMoteur;

typedef struct Bateau {
   Nom nom;
   TypeBateau typeBateau;
   double taxeAnnuelle;

   union specificite {
      BateauMoteur* bateauMoteur;
      BateauVoilier* bateauVoilier;
   };
} Bateau;

void setTaxeAnnuelle(Bateau* b);

#endif //LABO_MOI_BATEAU_H
