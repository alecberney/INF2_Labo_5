/*
 -------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Bateau.h
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Définir différentes structures servant à modéliser trois types
               de Bateau (bateau de plaisance, bateau de pêche, voilier), et
               des fonctions utiles à la gestion de ces Bateau.

 Remarque(s) : -

 Compilateur : MinGW-gcc 6.3.0
 -------------------------------------------------------------------------------
 */

#ifndef LABO_MOI_BATEAU_H
#define LABO_MOI_BATEAU_H

#include <inttypes.h>
#include <stdbool.h>

// ------------------ PUBLIC -----------------------

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

typedef enum UTILITE_BATEAU {PECHE, PLAISANCE} UtiliteBateau;

typedef union
{
   Plaisance* plaisance;
   Peche*     peche;

} Utilite;


// Motorisation du bateau
typedef struct
{
   uint16_t surfaceVoilure; // En m^2

} Voile;

typedef struct
{
   uint16_t      puissanceMoteur; // En CV(cheveaux)
   UtiliteBateau utiliteBateau;
   Utilite       utilite;

} Moteur;

typedef enum TYPE_BATEAU {A_VOILE, MOTORISE} TypeBateau;

typedef union
{
   Moteur* moteur;
   Voile*  voile;

} Motorisation;


typedef struct
{
   Nom          nom;
   TypeBateau   typeBateau;
   Motorisation motorisation;

} Bateau;

// ------------------ Fonctions publics -----------------------

Bateau* creeBateauPeche(Nom nomBateau, uint16_t puissanceMoteur,
                        uint8_t quantiteAutoriseePoissons);

Bateau* creeBateauPlaisance(Nom nomBateau, uint16_t puissanceMoteur,
                            uint8_t longueurBateau, Nom nomProprietaire);

Bateau* creeBateauAVoile(Nom nomBateau, uint16_t surfaceVoilure);

void detruitBateau(Bateau* b);

bool estMotorise(const Bateau* b);

bool estAVoile(const Bateau* b);

bool estUtilePeche(const Bateau* b);

bool estUtilePlaisance(const Bateau* b);

// --------------  Getter / Setter ----------------

// Plaisance
void setLongueurBateau(Bateau* b, uint8_t nouvelleLongueur);

const uint8_t* getLongueurBateau(const Bateau* b);

void setNomProprietaire(Bateau* b, Nom nouveauNom);

const Nom* getNomProprietaire(const Bateau* b);


// Pêche
void setQuantiteAutoriseePoissons(Bateau* b, uint8_t nouvelleQuantiteEnTonne);

const uint8_t* getQuantiteAutoriseePoissons(const Bateau* b);


// Bateau à voile
void setSurfaceVoilure(Bateau* b, uint16_t nouvelleSurface);

const uint16_t* getSurfaceVoilure(const Bateau* b);


// Bateau à moteur
void setPuissanceMoteur(Bateau* b, uint16_t nouvellePuissanceEnCV);

const uint16_t* getPuissanceMoteur(const Bateau* b);

void setUtiliteBateauMoteur(Bateau* b, UtiliteBateau nouvelleUtiliteBateau);

const UtiliteBateau* getUtiliteBateau(const Bateau* b);

void setPeche(Bateau* b, Peche* p);

const Peche* getPeche(const Bateau* b);

void setPlaisance(Bateau* b, Plaisance* p);

const Plaisance* getPlaisance(const Bateau* b);


// Bateau
void setNom(Bateau* b, Nom nouveauNom);

const Nom* getNom(const Bateau* b);

void setTypeBateau(Bateau* b, TypeBateau nouveauType);

const TypeBateau* getTypeBateau(const Bateau* b);

void setMoteur(Bateau* b, Moteur* m);

const Moteur* getMoteur(const Bateau* b);

void setVoile(Bateau* b, Voile* v);

const Voile* getVoile(const Bateau* b);

#endif //LABO_MOI_BATEAU_H
