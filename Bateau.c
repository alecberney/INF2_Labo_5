/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : Bateau.c
 Auteur(s)   : Berney Alec
 Date        : 29.05.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#include <stdlib.h>
#include "Bateau.h"

// ------------------ PUBLIC -----------------------

bool estMotorise(Bateau* b)
{
   return *getTypeBateau(b) == MOTORISE;
}

bool estAVoile(Bateau* b)
{
   return *getTypeBateau(b) == A_VOILE;
}

bool estUtilePeche(Bateau* b)
{
   if (estMotorise(b))
   {
      return *getUtiliteBateau(b) == PECHE;
   }
   return false;
}

bool estUtilePlaisance(Bateau* b)
{
   if (estMotorise(b))
   {
      return *getUtiliteBateau(b) == PLAISANCE;
   }
   return false;
}


// --------------  Getter / Setter ----------------

// Plaisance
void setLongueurBateau(Bateau* b, uint8_t nouvelleLongueur)
{
   if (estUtilePlaisance(b))
   {
      *getLongueurBateau(b) = nouvelleLongueur;
   }
}

uint8_t* getLongueurBateau(Bateau* b)
{
   if (estUtilePlaisance(b))
   {
      return &getUtilite(b)->plaisance->longueurBateau;
   }

   return NULL;
}

void setNomProprietaire(Bateau* b, Nom nouveauNom)
{
   if (estUtilePlaisance(b))
   {
      *getNomProprietaire(b) = nouveauNom;
   }
}

Nom* getNomProprietaire(Bateau* b)
{
   if (estUtilePlaisance(b))
   {
      return &getUtilite(b)->plaisance->nomProprietaire;
   }

   return NULL;
}


// Pêche
void setQuantiteAutoriseePoissons(Bateau* b, uint8_t nouvelleQuantiteEnTonne)
{
   if (estUtilePeche(b))
   {
      *getQuantiteAutoriseePoissons(b) = nouvelleQuantiteEnTonne;
   }
}

uint8_t* getQuantiteAutoriseePoissons(Bateau* b)
{
   if (estUtilePeche(b))
   {
      return &getUtilite(b)->peche->quantiteAutoriseePoissons;
   }

   return NULL;
}


// Bateau à voile
void setSurfaceVoilure(Bateau* b, uint16_t nouvelleSurface)
{
   if (estAVoile(b))
   {
      *getSurfaceVoilure(b) = nouvelleSurface;
   }
}

uint16_t* getSurfaceVoilure(Bateau* b)
{
   if (estAVoile(b))
   {
      return &getMotorisation(b)->voile->surfaceVoilure;
   }

   return NULL;
}


// Bateau à moteur
void setPuissanceMoteur(Bateau* b, uint16_t nouvellePuissanceEnCV)
{
   if (estMotorise(b))
   {
      *getPuissanceMoteur(b) = nouvellePuissanceEnCV;
   }
}

uint16_t* getPuissanceMoteur(Bateau* b)
{
   if (estMotorise(b))
   {
      return &getMotorisation(b)->moteur->puissanceMoteur;
   }

   return NULL;
}

void setUtiliteBateauMoteur(Bateau* b, UtiliteBateau nouvelleUtiliteBateau)
{
   if (estMotorise(b))
   {
      *getUtiliteBateau(b) = nouvelleUtiliteBateau;
   }
}

UtiliteBateau* getUtiliteBateau(Bateau* b)
{
   if (estMotorise(b))
   {
      return &getMotorisation(b)->moteur->utiliteBateau;
   }

   return NULL;
}

void setUtilite(Bateau* b, Utilite* nouvelleUtilite)
{
   if (estMotorise(b))
   {
      *getUtilite(b) = *nouvelleUtilite;
   }
}

Utilite* getUtilite(Bateau* b)
{
   if(estMotorise(b))
      return &getMotorisation(b)->moteur->utilite;

   return NULL;
}


// Bateau
void setNom(Bateau* b, Nom nouveauNom)
{
   *getNom(b) = nouveauNom;
}

Nom* getNom(Bateau* b)
{
   return &b->nom;
}

void setTypeBateau(Bateau* b, TypeBateau nouveauType)
{
   *getTypeBateau(b) = nouveauType;
}

TypeBateau* getTypeBateau(Bateau* b)
{
   return &b->typeBateau;
}

void setTaxeAnuelle(Bateau* b, double nouvelleTaxe)
{
   *getTaxeAnuelle(b) = nouvelleTaxe;
}

double* getTaxeAnuelle(Bateau* b)
{
   return &b->taxeAnnuelle;
}

void setMotorisation(Bateau* b, Motorisation* nouvelleMotorisation)
{
   *getMotorisation(b) = *nouvelleMotorisation;
}

Motorisation* getMotorisation(Bateau* b)
{
   return &b->motorisation;
}
