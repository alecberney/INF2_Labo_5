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

// ------------------ PROTOTYPE --------------------

void setTaxeAnnuelle(Bateau* b, double nouvelleTaxe);

// ------------------ PUBLIC -----------------------

// Cree un bateau a peche en utilisant l'allocation dynamique
// ATTENTION : Nécessite une destruction via la fonction detruitBateau
Bateau* creeBateauPeche(Nom nomBateau, uint16_t puissanceMoteur,
                        uint8_t quantiteAutoriseePoissons)
{
   Peche* p = (Peche*) malloc(sizeof(Peche));
   Moteur* m = (Moteur*) malloc(sizeof(Moteur));
   Bateau* b = (Bateau*) malloc(sizeof(Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, MOTORISE);

   setMoteur(b, m);

   setTaxeAnnuelle(b, 0); // A REVOIR

   setPuissanceMoteur(b, puissanceMoteur);

   setUtiliteBateauMoteur(b, PECHE);

   setPeche(b, p);

   setQuantiteAutoriseePoissons(b, quantiteAutoriseePoissons);

   return b;
}

// Cree un bateau de plaisance en utilisant l'allocation dynamique
// ATTENTION : Nécessite une destruction via la fonction detruitBateau
Bateau* creeBateauPlaisance(Nom nomBateau, uint16_t puissanceMoteur,
                            uint8_t longueurBateau, Nom nomProprietaire)
{
   Plaisance* p = (Plaisance*) malloc(sizeof(Plaisance));
   Moteur* m = (Moteur*) malloc(sizeof(Moteur));
   Bateau* b = (Bateau*) malloc(sizeof(Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, MOTORISE);

   setMoteur(b, m);

   setTaxeAnnuelle(b, 0); // A REVOIR

   setPuissanceMoteur(b, puissanceMoteur);

   setUtiliteBateauMoteur(b, PLAISANCE);

   setPlaisance(b, p);

   setLongueurBateau(b, longueurBateau);

   setNomProprietaire(b, nomProprietaire);

   return b;
}

// Cree un bateau a voile en utilisant l'allocation dynamique
// ATTENTION : Nécessite une destruction via la fonction detruitBateau
Bateau* creeBateauAVoile(Nom nomBateau, uint16_t surfaceVoilure)
{
   Voile* v = (Voile*) malloc(sizeof(Voile));
   Bateau* b = (Bateau*) malloc(sizeof(Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, A_VOILE);

   setVoile(b, v);

   setTaxeAnnuelle(b, 0); // A REVOIR

   setSurfaceVoilure(b, surfaceVoilure);

   return b;
}

void detruitBateau(Bateau* b)
{
   if (estAVoile(b))
   {
      free(getVoile(b));
   } else if (estMotorise(b))
   {
      if(estUtilePeche(b))
      {
         free(getPeche(b));
      }else if(estUtilePlaisance(b))
      {
         free(getPlaisance(b));
      }
      free(getMoteur(b));
   }

   free(b);
}

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
      return &getPlaisance(b)->longueurBateau;
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
      return &getPlaisance(b)->nomProprietaire;
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
      return &getPeche(b)->quantiteAutoriseePoissons;
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
      return &getVoile(b)->surfaceVoilure;
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
      return &getMoteur(b)->puissanceMoteur;
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
      return &getMoteur(b)->utiliteBateau;
   }

   return NULL;
}

void setPeche(Bateau* b, Peche* p)
{
   if (estUtilePeche(b))
   {
      getMoteur(b)->utilite.peche = p;
   }
}

Peche* getPeche(Bateau* b)
{
   if (estUtilePeche(b))
   {
      return getMoteur(b)->utilite.peche;
   }

   return NULL;
}

void setPlaisance(Bateau* b, Plaisance* p)
{
   if (estUtilePlaisance(b))
   {
      getMoteur(b)->utilite.plaisance = p;
   }
}

Plaisance* getPlaisance(Bateau* b)
{
   if (estUtilePlaisance(b))
   {
      return getMoteur(b)->utilite.plaisance;
   }

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

double* getTaxeAnnuelle(Bateau* b)
{
   return &b->taxeAnnuelle;
}

void setMoteur(Bateau* b, Moteur* m)
{
   if (estMotorise(b))
   {
      b->motorisation.moteur = m;
   }
}

Moteur* getMoteur(Bateau* b)
{
   if (!estMotorise(b))
   { return NULL; }

   return b->motorisation.moteur;
}

void setVoile(Bateau* b, Voile* v)
{
   if (estAVoile(b))
   {
      b->motorisation.voile = v;
   }
}

Voile* getVoile(Bateau* b)
{
   if (!estAVoile(b))
   { return NULL; }

   return b->motorisation.voile;
}

// --------------- PRIVE ------------------

void setTaxeAnnuelle(Bateau* b, double nouvelleTaxe)
{
   *getTaxeAnnuelle(b) = nouvelleTaxe;
}
