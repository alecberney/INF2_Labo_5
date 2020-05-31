#include <stdio.h>
#include "Bateau.h"
#include "Port.h"

int main()
{
   Bateau* voile = creeBateauAVoile("Voilier", 199);
   Bateau* peche = creeBateauPeche("Peche", 10, 19);
   Bateau* plaisance = creeBateauPlaisance("Plaisance", 99, 32, "Proprio");

   Port* p = construitPort(2);
   ajouteBateau(p, voile);
   ajouteBateau(p, peche);
   ajouteBateau(p, plaisance);

   printf("%7.2f\n", calculTaxeAnnuelle(p->bateaux[0]));
   printf("%7.2f\n", calculTaxeAnnuelle(p->bateaux[1]));
   printf("%7.2f\n", calculTaxeAnnuelle(p->bateaux[2]));

   supprimeBateau(p, voile);

   detruitBateau(voile);
   detruitBateau(peche);
   detruitBateau(plaisance);

   return 0;
}
