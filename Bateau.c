/*
 -----------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Bateau.c
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Définir les fonctions utiles à la gestion d'un Bateau, dont la struct
               a été précédemment prototypées dans Bateau.h.

 Remarque(s) : -

 Compilateur : MinGW-gcc 6.3.0
 -----------------------------------------------------------------------------------
 */
#include <stdlib.h>
#include "Bateau.h"

// ------------------ PUBLIC -----------------------

// Cree un bateau a peche en utilisant l'allocation dynamique
// ATTENTION : Nécessite une destruction via la fonction detruitBateau
Bateau* creeBateauPeche(Nom nomBateau, uint16_t puissanceMoteur,
                        uint8_t quantiteAutoriseePoissons)
{
   Peche*  p = (Peche*)  malloc(sizeof( Peche));
   Moteur* m = (Moteur*) malloc(sizeof(Moteur));
   Bateau* b = (Bateau*) malloc(sizeof(Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, MOTORISE);

   setMoteur(b, m);

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
   Moteur*    m = (Moteur*)    malloc(sizeof(   Moteur));
   Bateau*    b = (Bateau*)    malloc(sizeof(   Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, MOTORISE);

   setMoteur(b, m);

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
   Voile*  v = (Voile*)  malloc(sizeof( Voile));
   Bateau* b = (Bateau*) malloc(sizeof(Bateau));

   setNom(b, nomBateau);

   setTypeBateau(b, A_VOILE);

   setVoile(b, v);

   setSurfaceVoilure(b, surfaceVoilure);

   return b;
}

void detruitBateau(Bateau* b)
{
   if (estAVoile(b))
   {
      free((Voile*) getVoile(b));
   }
   else if (estMotorise(b))
   {
      if (estUtilePeche(b))
      {
         free((Peche*) getPeche(b));
      }
      else if (estUtilePlaisance(b))
      {
         free((Plaisance*) getPlaisance(b));
      }
      free((Moteur*) getMoteur(b));
   }

   free(b);
}

bool estMotorise(const Bateau* b)
{
   return *getTypeBateau(b) == MOTORISE;
}

bool estAVoile(const Bateau* b)
{
   return *getTypeBateau(b) == A_VOILE;
}

bool estUtilePeche(const Bateau* b)
{
   if (estMotorise(b))
   {
      return *getUtiliteBateau(b) == PECHE;
   }
   return false;
}

bool estUtilePlaisance(const Bateau* b)
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
      b->motorisation.moteur->utilite.plaisance->longueurBateau = nouvelleLongueur;
   }
}

const uint8_t* getLongueurBateau(const Bateau* b)
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
      b->motorisation.moteur->utilite.plaisance->nomProprietaire = nouveauNom;
   }
}

const Nom* getNomProprietaire(const Bateau* b)
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
      b->motorisation.moteur->utilite.peche->quantiteAutoriseePoissons
                                                   = nouvelleQuantiteEnTonne;
   }
}

const uint8_t* getQuantiteAutoriseePoissons(const Bateau* b)
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
      b->motorisation.voile->surfaceVoilure = nouvelleSurface;
   }
}

const uint16_t* getSurfaceVoilure(const Bateau* b)
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
      b->motorisation.moteur->puissanceMoteur = nouvellePuissanceEnCV;
   }
}

const uint16_t* getPuissanceMoteur(const Bateau* b)
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
      b->motorisation.moteur->utiliteBateau = nouvelleUtiliteBateau;
   }
}

const UtiliteBateau* getUtiliteBateau(const Bateau* b)
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
      b->motorisation.moteur->utilite.peche = p;
   }
}

const Peche* getPeche(const Bateau* b)
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
      b->motorisation.moteur->utilite.plaisance = p;
   }
}

const Plaisance* getPlaisance(const Bateau* b)
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
   b->nom = nouveauNom;
}

const Nom* getNom(const Bateau* b)
{
   return &b->nom;
}

void setTypeBateau(Bateau* b, TypeBateau nouveauType)
{
   b->typeBateau = nouveauType;
}

const TypeBateau* getTypeBateau(const Bateau* b)
{
   return &b->typeBateau;
}


void setMoteur(Bateau* b, Moteur* m)
{
   if (estMotorise(b))
   {
      b->motorisation.moteur = m;
   }
}

const Moteur* getMoteur(const Bateau* b)
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

const Voile* getVoile(const Bateau* b)
{
   if (!estAVoile(b))
   { return NULL; }

   return b->motorisation.voile;
}

