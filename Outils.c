/*
 -------------------------------------------------------------------------------
 Laboratoire : N°5 - Port, Bateaux et Taxes
 Fichier     : Outils.c
 Auteur(s)   : Alec Berney, Quentin Forestier, Victoria Logan
 Date        : 29.05.2020

 Compilateur : MinGW-gcc 6.3.0
 -------------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <stdio.h>
#include "Outils.h"

const char* TYPE_BATEAU_AFFICHAGE[2] = {"Voilier", "Motorise"};
const char* UTILITE_BATEAU_AFFICHAGE[2] = {"Peche", "Plaisance"};
const char* TOUS_TYPES_BATEAU_AFFICHAGE[NB_TYPE_BATEAUX] = {"Voilier",
                                                            "Motorise Peche",
                                                            "Motorise Plaisance"};

uint16_t* getNbBateauxParType(const Bateau** port, size_t taille)
{
   uint16_t* tabNbBateaux = calloc(NB_TYPE_BATEAUX, sizeof(uint16_t));

   for (size_t i = 0; i < taille; ++i)
   {

      if (estUtilePlaisance(port[i]))
      {
         ++tabNbBateaux[BATEAU_PLAISANCE];
      }
      else if (estUtilePeche(port[i]))
      {
         ++tabNbBateaux[BATEAU_PECHE];
      }
      else
      {
         ++tabNbBateaux[VOILIER];
      }
   }

   return tabNbBateaux;
}

void getTabTaxesParBateaux(const Bateau** port,
                           size_t taille,
                           double* tabTaxesPlaisance,
                           double* tabTaxesPeche,
                           double* tabTaxesVoilier)
{
   size_t nbPlaisance = 0, nbPeche = 0, nbVoilier = 0;
   for (size_t i = 0; i < taille; ++i)
   {
      const Bateau* b = port[i];
      if (estUtilePeche(b))
      {
         tabTaxesPeche[nbPeche] = calculTaxeAnnuelle(b);
         ++nbPeche;
      }
      else if (estUtilePlaisance(b))
      {
         tabTaxesPlaisance[nbPlaisance] = calculTaxeAnnuelle(b);
         ++nbPlaisance;
      }
      else
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

double calculTaxeAnnuelle(const Bateau* b)
{
   double resultat = 0.0;

   if(estUtilePlaisance(b))
   {
      resultat += TAXE_BASE_BATEAU_MOTEUR;
      if(*getPuissanceMoteur(b) < PUISSANCE_MOTEUR_TAXE_SUPP)
      {
         resultat += TAXE_SPECIFIQUE_MIN_PLAISANCE;
      }
      else
      {
         resultat += TAXE_SPECIFIQUE_MAX_PLAISANCE(*getLongueurBateau(b));
      }
   }

   else if(estUtilePeche(b))
   {
      resultat += TAXE_BASE_BATEAU_MOTEUR;
      if(*getQuantiteAutoriseePoissons(b) < TONNES_POISSONS_TAXE_SUPP)
      {
         resultat += TAXE_SPECIFIQUE_MIN_PECHE;
      }
      else
      {
         resultat += TAXE_SPECIFIQUE_MAX_PECHE;
      }
   }
   else if(estAVoile(b))
   {
      resultat += TAXE_BASE_VOILIER;
      if(*getSurfaceVoilure(b) < TAILE_VOILURE_TAXE_SUPP)
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


double* calculerMoyenneTaxesAnnuellesParType(const Bateau** port, size_t taille)
{
   double* tabMoyennesTaxeParType = calloc(NB_TYPE_BATEAUX, sizeof(double));
   tabMoyennesTaxeParType = calculerSommeTotaleTaxesAnnuellesParType(port, taille);

   size_t nbBateauxPlaisanceDansPort = 0,
          nbBateauxPecheDansPort     = 0,
          nbBateauxVoilierDansPort   = 0;

   for (size_t i = 0; i < taille; ++i)
   {
      if (estMotorise(port[i]))
      {
         if (estUtilePlaisance(port[i]))
         {
            ++nbBateauxPlaisanceDansPort;
         }
         else
         {
            ++nbBateauxPecheDansPort;
         }

      }
      else
      {
         ++nbBateauxVoilierDansPort;
      }
   }

   tabMoyennesTaxeParType[BATEAU_PLAISANCE] /= nbBateauxPlaisanceDansPort;
   tabMoyennesTaxeParType[BATEAU_PECHE]     /= nbBateauxPecheDansPort;
   tabMoyennesTaxeParType[VOILIER]          /= nbBateauxVoilierDansPort;

   return tabMoyennesTaxeParType;
}

double* calculerMedianeTaxesAnnuellesParType(const Bateau** port, size_t taille)
{
   double* tabMedianTaxesParType = malloc(NB_TYPE_BATEAUX * sizeof(double));

   uint16_t* tmp = getNbBateauxParType(port, taille);

   size_t nbPlaisance = tmp[BATEAU_PLAISANCE];
   size_t nbPeche     = tmp[BATEAU_PECHE];
   size_t nbVoilier   = tmp[VOILIER];

   double tabTaxesPlaisance[nbPlaisance];
   double tabTaxesPeche[nbPeche];
   double tabTaxesVoilier[nbVoilier];

   getTabTaxesParBateaux(port, taille, tabTaxesPlaisance,
                         tabTaxesPeche, tabTaxesVoilier);

   qsort(tabTaxesPlaisance, nbPlaisance, sizeof(double), cmpfunc);
   qsort(    tabTaxesPeche,     nbPeche, sizeof(double), cmpfunc);
   qsort(  tabTaxesVoilier,   nbVoilier, sizeof(double), cmpfunc);

   tabMedianTaxesParType[VOILIER]          = tabTaxesVoilier[(nbVoilier + 1) / 2 - 1];
   tabMedianTaxesParType[BATEAU_PECHE]     = tabTaxesPeche[(nbPeche + 1) / 2 - 1];
   tabMedianTaxesParType[BATEAU_PLAISANCE] = tabTaxesPlaisance[(nbPlaisance + 1) / 2 - 1];

   return tabMedianTaxesParType;
}

double* calculerSommeTotaleTaxesAnnuellesParType(const Bateau** port, size_t taille)
{
   double* tabSommesTaxeParType = calloc(NB_TYPE_BATEAUX, sizeof(double));

   for (size_t i = 0; i < taille; ++i)
   {

      if (estUtilePlaisance(port[i]))
      {
         tabSommesTaxeParType[BATEAU_PLAISANCE] += calculTaxeAnnuelle(port[i]);
      }
      else if (estUtilePeche(port[i]))
      {
         tabSommesTaxeParType[BATEAU_PECHE] += calculTaxeAnnuelle(port[i]);
      }
      else
      {
         tabSommesTaxeParType[VOILIER] += calculTaxeAnnuelle(port[i]);
      }
   }
   return tabSommesTaxeParType;
}

void afficherTaxesParType(const Bateau** port, size_t taille)
{
   // taxesParType[i] : i = 0 <-> voilier, i = 1 <-> peche, i = 2 <-> plaisance
   double* tabTaxesParType = calloc(NB_TYPE_BATEAUX, sizeof(double));

   printf("SOMME TOTALE des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerSommeTotaleTaxesAnnuellesParType(port, taille);
   afficherTabTaxesParType(tabTaxesParType);

   printf("MONTANT MOYEN des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerMoyenneTaxesAnnuellesParType(port, taille);
   afficherTabTaxesParType(tabTaxesParType);

   printf("MONTANT MEDIAN des taxes annuelles dues par type de bateau : \n");
   tabTaxesParType = calculerMedianeTaxesAnnuellesParType(port, taille);
   afficherTabTaxesParType(tabTaxesParType);
}


void afficherBateauxPort(const Bateau** port, size_t taille)
{
   for (size_t i = 0; i < taille; ++i)
   {
      afficherBateau(port[i]);
      printf("\n");
   }
}

void afficherBateau(const Bateau* b)
{
   printf("Nom                 : %s \n", *getNom(b));
   printf("Type de bateau      : %s \n", TYPE_BATEAU_AFFICHAGE[*getTypeBateau(b)]);

   if (estMotorise(b))
   {
      printf("Puissance du moteur : %d [CV] \n", *getPuissanceMoteur(b));
      printf("Utilite du bateau   : %s \n",
              UTILITE_BATEAU_AFFICHAGE[*getUtiliteBateau(b)]);

      if (estUtilePlaisance(b))
      {
         printf("Longueur du bateau  : %d [m^2] \n", *getLongueurBateau(b));
         printf("Nom du proprietaire : %s \n", *getNomProprietaire(b));
      }
      else
      {
         printf("Quantite maximum de peche autorisee : %d [tonnes] \n",
                 *getQuantiteAutoriseePoissons(b));
      }
   }
   else
   {
      printf("Surface de la voilure : %d [m^2] \n", *getSurfaceVoilure(b));
   }
}

void afficherTabTaxesParType(double* tabTaxesParType)
{
   for (size_t i = 0; i < NB_TYPE_BATEAUX; ++i)
   {
      printf("%-19s : %g \n", TOUS_TYPES_BATEAU_AFFICHAGE[i], tabTaxesParType[i]);
   }
   printf("\n");
}
