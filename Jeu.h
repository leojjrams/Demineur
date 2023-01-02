#ifndef _JEU_
#define _JEU_
#include"Map.h"

typedef enum Statut { Terminé, En_Cours };

void Commencer(Map& m, Probleme& p);
bool Gagne(Map& m, Probleme& p);
bool Perdu(Map& m, Probleme& p);
void instruction(Map& m, Probleme& p);

#endif