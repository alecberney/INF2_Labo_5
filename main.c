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
void afficherTaxesParType(const Port* p, void (*f)(const Port* p, double* tabTaxesParType));

void assignerTaxesAnnuelles(const Port* p);

void calculerSommeTotaleTaxesAnnuellesParType(const Port* p, double* tabTaxesParType);
// important de passer un tableau constitué de sommes en paramètre pour tabTaxes
void calculerMoyenneTaxesAnnuellesParType(const Port* p, double* tabTaxesParType);
void calculerMedianeTaxesAnnuellesParType(const Port* p, double* tabTaxesParType);

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
   
   assignerTaxesAnnuelles(p);

   printf("SOMME TOTALE des taxes annuelles dues par type de bateau : \n");
   afficherTaxesParType(p, calculerSommeTotaleTaxesAnnuellesParType);
   
   printf("MONTANT MOYEN des taxes annuelles dues par type de bateau : \n");
   afficherTaxesParType(p, calculerMoyenneTaxesAnnuellesParType);
   
   printf("MONTANT MEDIAN des taxes annuelles dues par type de bateau : \n");
   afficherTaxesParType(p, calculerMedianeTaxesAnnuellesParType);
   
   supprimeBateau(p, voile);

   detruitBateau(voile);
   detruitBateau(peche);
   detruitBateau(plaisance);

   return EXIT_SUCCESS;
}

void assignerTaxesAnnuelles(const Port* p)
{
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
      *getTaxeAnnuelle(p->bateaux[i]) = calculTaxeAnnuelle(p->bateaux[i]);
}

void afficherTaxesParType(const Port* p, void (*f)(const Port* p, double* tabTaxesParType))
{
   // taxesParType[i] : i = 0 <-> voilier, i = 1 <-> peche, i = 2 <-> plaisance
   double tabTaxesParType[NB_TYPE_BATEAUX] = {0, 0, 0};
   
   f(p, tabTaxesParType); // rempli le tableau avec les bonnes valeurs, suivant ce qu'on veut calculer
   
   for(size_t i = 0; i < NB_TYPE_BATEAUX; ++i)
   {
      printf("%-19s : %g \n", TOUS_TYPES_BATEAU_AFFICHAGE[i], tabTaxesParType[i]);
   }
   printf("\n");
}

// Fonction qui remplit le tableau tab Taxes avec la somme des taxes annuelles, par type
void calculerSommeTotaleTaxesAnnuellesParType(const Port* p, double* tabTaxesParType)
{
   for(size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      if(estMotorise(p->bateaux[i]))
      {
         if(estUtilePlaisance(p->bateaux[i]))
         {
            tabTaxesParType[2] +=  *getTaxeAnnuelle(p->bateaux[i]);
         }
         else
         {
            tabTaxesParType[1] +=  *getTaxeAnnuelle(p->bateaux[i]);
         }
      }
      else
      {
         tabTaxesParType[0] +=  *getTaxeAnnuelle(p->bateaux[i]);
      }
   }
}

// Fonction qui remplit le tableau tab Taxes avec la moyenne des taxes annuelles, par type
void calculerMoyenneTaxesAnnuellesParType(const Port* p, double* tabTaxesParType)
{
   calculerSommeTotaleTaxesAnnuellesParType(p, tabTaxesParType);
   
   size_t nbBateauxPlaisanceDansPort = 0, nbBateauxPecheDansPort = 0, nbBateauxVoilierDansPort = 0;
   
   for (size_t i = 0; i < NB_BATEAUX_PORTS; ++i)
   {
      if(estMotorise(p->bateaux[i]))
      {
         if(estUtilePlaisance(p->bateaux[i]))
            ++nbBateauxPlaisanceDansPort;
         else
            ++nbBateauxPecheDansPort;
         
      } else {
         ++nbBateauxVoilierDansPort;
      }
   }
   
   tabTaxesParType[2] /= nbBateauxPlaisanceDansPort;
   tabTaxesParType[1] /= nbBateauxPecheDansPort;
   tabTaxesParType[0] /= nbBateauxVoilierDansPort;
   
}

int cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}

// Fonction qui remplit le tableau tab Taxes avec la médiane des taxes annuelles, par type
void calculerMedianeTaxesAnnuellesParType(const Port* p, double* tabTaxesParType)
{
   // qsort(p, NB_BATEAUX_PORTS, sizeof(Bateau), cmpfunc);
   
}

void afficherBateau(const Bateau* b)
{
   printf("Nom                 : %s \n", *getNom(b));
   printf("Type de bateau      : %s \n", TYPE_BATEAU_AFFICHAGE[*getTypeBateau(b)]);

   if(estMotorise(b))
   {
      printf("Puissance du moteur : %d [CV] \n", *getPuissanceMoteur(b));
      printf("Utilite du bateau   : %s \n", UTILITE_BATEAU_AFFICHAGE[*getUtiliteBateau(b)]);

      if(estUtilePlaisance(b))
      {
         printf("Longueur du bateau  : %d [m^2] \n", *getLongueurBateau(b));
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
