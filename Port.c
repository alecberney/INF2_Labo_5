/*
 -----------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Port.c
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 But         : Définir des fonctions utiles à la gestion d'un Port.

 Remarque(s) : -

 Compilateur : MinGW-gcc 6.3.0
 -----------------------------------------------------------------------------------
 */

#include "Port.h"
#include <stdlib.h>
#include <string.h>

Port* construitPort(uint16_t capacite)
{
   Port* p = (Port*) malloc(sizeof(Port));

   p->taille = 0;
   p->capacite = capacite;

   p->bateaux = (Bateau**) malloc(sizeof(Bateau*) * capacite);

   return p;
}

void detruitPortEtBateaux(Port* p)
{
   for (uint16_t i = 0; i < p->taille; ++i)
   {
      detruitBateau(p->bateaux[i]);
   }
   free(p);
}

int trouveBateau(const Port* p, const Bateau* b)
{
   for (uint16_t i = 0; i < p->taille; ++i)
   {
      if (p->bateaux[i] == b)
      {
         return i;
      }
   }
   return -1;
}

void ajouteBateau(Port* p, Bateau* b)
{
   if (p->taille < p->capacite)
   {
      p->bateaux[p->taille] = b;
   }
   else
   {
      p->capacite *= 2;
      Bateau** tmp = p->bateaux;

      p->bateaux = realloc(p->bateaux, sizeof(Bateau*) * p->capacite);

      memcpy(p->bateaux, tmp, sizeof(Bateau*) * p->taille);
      p->bateaux[p->taille] = b;

   }
   ++p->taille;
}

void supprimeBateau(Port* p, const Bateau* b)
{
   int index = trouveBateau(p, b);
   if (index != -1)
   {
      // Ecrase le pointeur à l'index trouvé par
      // le pointeur du dernier bateau du tableau
      p->bateaux[index] = p->bateaux[p->taille - 1];
      p->bateaux[p->taille - 1] = NULL;
      --p->taille;
   }
}

double calculTaxeAnnuelle(const Bateau* b)
{
   double resultat = 0.0;

   if (estUtilePlaisance(b))
   {
      resultat += TAXE_BASE_BATEAU_MOTEUR;
      if (*getPuissanceMoteur(b) < PUISSANCE_MOTEUR_TAXE_SUPP)
      {
         resultat += TAXE_SPECIFIQUE_MIN_PLAISANCE;
      }
      else
      {
         resultat += TAXE_SPECIFIQUE_MAX_PLAISANCE(*getLongueurBateau(b));
      }
   }
   else if (estUtilePeche(b))
   {
      resultat += TAXE_BASE_BATEAU_MOTEUR;
      if (*getQuantiteAutoriseePoissons(b) < TONNES_POISSONS_TAXE_SUPP)
      {
         resultat += TAXE_SPECIFIQUE_MIN_PECHE;
      }
      else
      {
         resultat += TAXE_SPECIFIQUE_MAX_PECHE;
      }
   }
   else if (estAVoile(b))
   {
      resultat += TAXE_BASE_VOILIER;
      if (*getSurfaceVoilure(b) < TAILLE_VOILURE_TAXE_SUPP)
      {
         resultat += TAXE_SPECIFIQUE_MIN_VOILIER;
      }
      else
      {
         resultat += TAXE_SPECIFIQUE_MAX_VOILIER;
      }
   }
   return resultat;
}
