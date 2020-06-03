/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : Outils.c
 Auteur(s)   : Quentin Forestier
 Date        : 03.06.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <stdio.h>
#include "Outils.h"

uint16_t* getNbBateauxParType(const Port* p)
{
   uint16_t* tabNbBateaux = calloc(NB_TYPE_BATEAUX, sizeof(uint16_t));

   for (size_t i = 0; i < p->taille; ++i)
   {

      if (estUtilePlaisance(p->bateaux[i]))
      {
         ++tabNbBateaux[2];
      } else if (estUtilePeche(p->bateaux[i]))
      {
         ++tabNbBateaux[1];
      } else
      {
         ++tabNbBateaux[0];
      }
   }

   return tabNbBateaux;
}

void getTabTaxesParBateaux(const Port* p, double* tabTaxesPlaisance, double* tabTaxesPeche, double* tabTaxesVoilier)
{
   size_t nbPlaisance = 0, nbPeche = 0, nbVoilier = 0;
   for (size_t i = 0; i < p->taille; ++i)
   {
      Bateau* b = p->bateaux[i];
      if (estUtilePeche(b))
      {
         tabTaxesPeche[nbPeche] = calculTaxeAnnuelle(b);
         ++nbPeche;
      } else if (estUtilePlaisance(b))
      {
         tabTaxesPlaisance[nbPlaisance] = calculTaxeAnnuelle(b);
         ++nbPlaisance;
      } else
      {
         tabTaxesVoilier[nbVoilier] = calculTaxeAnnuelle(b);
         ++nbVoilier;
      }
   }
}

int cmpfunc(const void* a, const void* b)
{
   return ((int) (*(double*) a - *(double*) b));
}


double* calculerMoyenneTaxesAnnuellesParType(const Port* p)
{
   double* tabMoyennesTaxeParType = calloc(NB_TYPE_BATEAUX, sizeof(double));
   tabMoyennesTaxeParType = calculerSommeTotaleTaxesAnnuellesParType(p);

   size_t nbBateauxPlaisanceDansPort = 0, nbBateauxPecheDansPort = 0, nbBateauxVoilierDansPort = 0;

   for (size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      if (estMotorise(p->bateaux[i]))
      {
         if (estUtilePlaisance(p->bateaux[i]))
         {
            ++nbBateauxPlaisanceDansPort;
         } else
         {
            ++nbBateauxPecheDansPort;
         }

      } else
      {
         ++nbBateauxVoilierDansPort;
      }
   }

   tabMoyennesTaxeParType[2] /= nbBateauxPlaisanceDansPort;
   tabMoyennesTaxeParType[1] /= nbBateauxPecheDansPort;
   tabMoyennesTaxeParType[0] /= nbBateauxVoilierDansPort;

   return tabMoyennesTaxeParType;
}

double* calculerMedianeTaxesAnnuellesParType(const Port* p)
{
   // besoin ni de la somme, ni de la moyenne, construire un tableau de chaque sorte ?
   // qsort(p, NB_BATEAUX_PORTS, sizeof(Bateau), cmpfunc);

   double* tabMedianTaxesParType = malloc(NB_TYPE_BATEAUX * sizeof(double));

   uint16_t* tmp = getNbBateauxParType(p);

   size_t nbPlaisance = tmp[2];
   size_t nbPeche = tmp[1];
   size_t nbVoilier = tmp[0];

   double tabTaxesPlaisance[nbPlaisance];
   double tabTaxesPeche[nbPeche];
   double tabTaxesVoilier[nbVoilier];

   getTabTaxesParBateaux(p, tabTaxesPlaisance, tabTaxesPeche, tabTaxesVoilier);

   qsort(tabTaxesPlaisance, nbPlaisance, sizeof(double), cmpfunc);
   qsort(tabTaxesPeche, nbPeche, sizeof(double), cmpfunc);
   qsort(tabTaxesVoilier, nbVoilier, sizeof(double), cmpfunc);

   tabMedianTaxesParType[0] = tabTaxesVoilier[(nbVoilier + 1) / 2 - 1];
   tabMedianTaxesParType[1] = tabTaxesPeche[(nbPeche + 1) / 2 - 1];
   tabMedianTaxesParType[2] = tabTaxesPlaisance[(nbPlaisance + 1) / 2 - 1];

   return tabMedianTaxesParType;

}

double* calculerSommeTotaleTaxesAnnuellesParType(const Port* p)
{
   double* tabSommesTaxeParType = calloc(NB_TYPE_BATEAUX, sizeof(double));

   for (size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {

      if (estUtilePlaisance(p->bateaux[i]))
      {
         tabSommesTaxeParType[2] += calculTaxeAnnuelle(p->bateaux[i]);
      } else if (estUtilePeche(p->bateaux[i]))
      {
         tabSommesTaxeParType[1] += calculTaxeAnnuelle(p->bateaux[i]);                                    // CONSTANTES
      } else
      {
         tabSommesTaxeParType[0] += calculTaxeAnnuelle(p->bateaux[i]);
      }
   }

   return tabSommesTaxeParType;
}

void afficherTaxesParType(const Port* p)
{
   // taxesParType[i] : i = 0 <-> voilier, i = 1 <-> peche, i = 2 <-> plaisance
   double* tabTaxesParType = calloc(NB_TYPE_BATEAUX, sizeof(double));

   printf("SOMME TOTALE des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerSommeTotaleTaxesAnnuellesParType(p);
   afficherTabTaxesParType(tabTaxesParType);

   printf("MONTANT MOYEN des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerMoyenneTaxesAnnuellesParType(p);
   afficherTabTaxesParType(tabTaxesParType);

   printf("MONTANT MEDIAN des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerMedianeTaxesAnnuellesParType(p);
   afficherTabTaxesParType(tabTaxesParType);
}


void afficherBateauxPort(const Port* p)
{
   for (size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      afficherBateau(p->bateaux[i]);
      printf("\n");
   }
}

void afficherBateau(const Bateau* b)
{
   printf("Nom                 : %s \n", *getNom(b));
   printf("Type de bateau      : %s \n", "Test");//TYPE_BATEAU_AFFICHAGE[*getTypeBateau(b)]);

   if (estMotorise(b))
   {
      printf("Puissance du moteur : %d [CV] \n", *getPuissanceMoteur(b));
      printf("Utilite du bateau   : %s \n", "Test2");//UTILITE_BATEAU_AFFICHAGE[*getUtiliteBateau(b)]);

      if (estUtilePlaisance(b))
      {
         printf("Longueur du bateau  : %d [m^2] \n", *getLongueurBateau(b));
         printf("Nom du proprietaire : %s \n", *getNomProprietaire(b));
      } else
      {
         printf("Quantite maximum de peche autorisee : %d [tonnes] \n", *getQuantiteAutoriseePoissons(b));
      }
   } else
   {
      printf("Surface de la voilure : %d [m^2] \n", *getSurfaceVoilure(b));
   }
}

void afficherTabTaxesParType(double* tabTaxesParType)
{
   for (size_t i = 0; i < NB_TYPE_BATEAUX; ++i)
   {
      printf("%-19s : %g \n", "Test3", tabTaxesParType[i]);//TOUS_TYPES_BATEAU_AFFICHAGE[i], tabTaxesParType[i]);
   }
   printf("\n");
}


