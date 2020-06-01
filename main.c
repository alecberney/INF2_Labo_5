#include <stdio.h>
#include <stdlib.h>

#include "Bateau.h"
#include "Port.h"

#define NB_BATEAUX_PORTS 6
#define NB_TYPE_BATEAUX 3

const char* TYPE_BATEAU_AFFICHAGE[2] = {"Voilier", "Motorise"};
const char* UTILITE_BATEAU_AFFICHAGE[2] = {"Peche", "Plaisance"};
const char* TOUS_TYPES_BATEAU_AFFICHAGE[NB_TYPE_BATEAUX] = {"Voilier", "Motorise Peche", "Motorise Plaisance"};

void afficherBateau(const Bateau* b);
void afficherBateauxPort(const Port* p);
void afficherTaxesParType(const double* tab);

void taxeTotaleParType(const Port* p, double* tabTaxe);

void test(Port* p);

int main()
{
   Bateau* voile = creeBateauAVoile("Voilier", 199);
   Bateau* voile2 = creeBateauAVoile("Voilier2", 200);
   Bateau* peche = creeBateauPeche("Peche", 10, 19);
   Bateau* peche2 = creeBateauPeche("Peche2", 15, 20);
   Bateau* plaisance = creeBateauPlaisance("Plaisance", 99, 32, "Proprio");
   Bateau* plaisance2 = creeBateauPlaisance("Plaisance2", 100, 35, "Proprio2");

   Port* p = construitPort(NB_BATEAUX_PORTS);
   ajouteBateau(p, voile);
   ajouteBateau(p, voile2);
   ajouteBateau(p, peche);
   ajouteBateau(p, peche2);
   ajouteBateau(p, plaisance);
   ajouteBateau(p, plaisance2);

   afficherBateauxPort(p);

   // calcul des taxes annuelles et assignation aux bateaux
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      *getTaxeAnnuelle(p->bateaux[i]) = calculTaxeAnnuelle(p->bateaux[i]);
   }

   printf("Taxes par bateau : \n");
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      printf("%s : %g \n", *getNom(p->bateaux[i]), *getTaxeAnnuelle(p->bateaux[i]));
   }
   printf("\n");

   printf("Total des taxes par type de bateau : \n");
   // totaux[0] = voilier, 1 = peche, 2 = plaisance
   double totaux[NB_TYPE_BATEAUX] = {0, 0, 0};
   taxeTotaleParType(p, totaux);
   afficherTaxesParType(totaux);

   supprimeBateau(p, voile);

   detruitBateau(voile);
   detruitBateau(peche);
   detruitBateau(plaisance);

   return EXIT_SUCCESS;
}

void afficherTaxesParType(const double* tab)
{
   for(size_t i = 0; i < NB_TYPE_BATEAUX; ++i)
   {
      printf("%s : %g \n", TOUS_TYPES_BATEAU_AFFICHAGE[i], tab[i]);
   }
   printf("\n");
}

void taxeTotaleParType(const Port* p, double* tabTaxe)
{
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      if(estMotorise(p->bateaux[i]))
      {
         if(estUtilePlaisance(p->bateaux[i]))
         {
            tabTaxe[2] +=  *getTaxeAnnuelle(p->bateaux[i]);
         }
         else
         {
            tabTaxe[1] +=  *getTaxeAnnuelle(p->bateaux[i]);
         }
      }
      else
      {
         tabTaxe[0] +=  *getTaxeAnnuelle(p->bateaux[i]);
      }
   }
}

void afficherBateau(const Bateau* b)
{
   printf("Nom : %s \n", *getNom(b));
   printf("Type de bateau : %s \n", TYPE_BATEAU_AFFICHAGE[*getTypeBateau(b)]);

   if(estMotorise(b))
   {
      printf("Puissance du moteur : %d [CV] \n", *getPuissanceMoteur(b));
      printf("Utilite du bateau : %s \n", UTILITE_BATEAU_AFFICHAGE[*getUtiliteBateau(b)]);

      if(estUtilePlaisance(b))
      {
         printf("Longueur du bateau : %d [m^2] \n", *getLongueurBateau(b));
         printf("Nom du proprietaire : %s \n", *getNomProprietaire(b));
      }
      else
      {
         printf("Quantite maximum de peche autorisee : %d [tonnes] \n", *getQuantiteAutoriseePoissons(b));
      }
   }
   else
   {
      printf("Surface de la voilure : %d [m^2] \n", *getSurfaceVoilure(b));
   }
}

void afficherBateauxPort(const Port* p)
{
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      afficherBateau(p->bateaux[i]);
      printf("\n");
   }
}
