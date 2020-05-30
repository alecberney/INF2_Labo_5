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
#include <stdbool.h>

typedef char* Nom;


// Utilite du bateau à moteur
typedef struct
{
   uint8_t longueurBateau; // en m
   Nom nomProprietaire;

} Plaisance;

typedef struct
{
   uint8_t quantiteAutoriseePoissons; // En tonne

} Peche;

typedef enum UTILITE_BATEAU
{
   PECHE, PLAISANCE
} UtiliteBateau;

typedef union
{
   Plaisance* plaisance;
   Peche* peche;

} Utilite;


// Motorisation du bateau
typedef struct Voile
{
   uint16_t surfaceVoilure; // En m^2

} Voile;

typedef struct Moteur
{
   uint16_t puissanceMoteur; // En CV(cheveaux)
   UtiliteBateau utiliteBateau;
   Utilite utilite;

} Moteur;

typedef enum TYPE_BATEAU
{
   A_VOILE, MOTORISE
} TypeBateau;

typedef union
{
   Moteur* moteur;
   Voile* voile;

} Motorisation;


typedef struct Bateau
{
   Nom nom;
   TypeBateau typeBateau;
   double taxeAnnuelle; // CONSTANT
   Motorisation motorisation;

} Bateau;

// ------------------ PUBLIC -----------------------

Bateau* creeBateauPeche(Nom nomBateau, uint16_t puissanceMoteur,
                        uint8_t quantiteAutoriseePoissons);

Bateau* creeBateauPlaisance(Nom nomBateau, uint16_t puissanceMoteur,
                            uint8_t longueurBateau, Nom nomProprietaire);

Bateau* creeBateauAVoile(Nom nomBateau, uint16_t surfaceVoilure);

void detruitBateau(Bateau* b);

bool estMotorise(Bateau* b);

bool estAVoile(Bateau* b);

bool estUtilePeche(Bateau* b);

bool estUtilePlaisance(Bateau* b);

// --------------  Getter / Setter ----------------

// Plaisance
void setLongueurBateau(Bateau* b, uint8_t nouvelleLongueur);

uint8_t* getLongueurBateau(Bateau* b);

void setNomProprietaire(Bateau* b, Nom nouveauNom);

Nom* getNomProprietaire(Bateau* b);


// Pêche
void setQuantiteAutoriseePoissons(Bateau* b, uint8_t nouvelleQuantiteEnTonne);

uint8_t* getQuantiteAutoriseePoissons(Bateau* b);


// Bateau à voile
void setSurfaceVoilure(Bateau* b, uint16_t nouvelleSurface);

uint16_t* getSurfaceVoilure(Bateau* b);


// Bateau à moteur
void setPuissanceMoteur(Bateau* b, uint16_t nouvellePuissanceEnCV);

uint16_t* getPuissanceMoteur(Bateau* b);

void setUtiliteBateauMoteur(Bateau* b, UtiliteBateau nouvelleUtiliteBateau);

UtiliteBateau* getUtiliteBateau(Bateau* b);

void setPeche(Bateau* b, Peche* p);

Peche* getPeche(Bateau* b);

void setPlaisance(Bateau* b, Plaisance* p);

Plaisance* getPlaisance(Bateau* b);


// Bateau
void setNom(Bateau* b, Nom nouveauNom);

Nom* getNom(Bateau* b);

void setTypeBateau(Bateau* b, TypeBateau nouveauType);

TypeBateau* getTypeBateau(Bateau* b);

double* getTaxeAnnuelle(Bateau* b);

void setMoteur(Bateau* b, Moteur* m);

Moteur* getMoteur(Bateau* b);

void setVoile(Bateau* b, Voile* v);

Voile* getVoile(Bateau* b);




#endif //LABO_MOI_BATEAU_H
