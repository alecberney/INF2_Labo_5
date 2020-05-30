#include <stdio.h>
#include "Bateau.h"

int main()
{
   Bateau* voile = creeBateauAVoile("Voilier", 12);
   Bateau* peche = creeBateauPeche("Peche", 10, 10);
   Bateau* plaisance = creeBateauPlaisance("Plaisance", 25, 32, "Proprio");

   printf("%d\n", *getSurfaceVoilure(voile));
   printf("%d\n", *getQuantiteAutoriseePoissons(peche));
   printf("%s\n", *getNomProprietaire(plaisance));

   detruitBateau(voile);
   detruitBateau(peche);
   detruitBateau(plaisance);

   return 0;
}
