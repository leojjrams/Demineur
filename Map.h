#ifndef _MAP_
#define _MAP_

#include"Case.h"
#include"Probleme.h"

struct Map {
	unsigned int hauteur;
	unsigned int largeur;
	Case** Conteneur;
};

void initialiserMap(Map& m, unsigned int h, unsigned int l);
bool VidePossible(Map& m);
bool EstVideAutour(Case c, Map& m);
void AjouterMines(Map& m, Probleme& p, unsigned int mines);
unsigned int CompterMines(Case c, Map& m);
void EnrMines(Map& m);
void afficher(Map& m, Probleme& p);
void ViderAutour(Case& c, Map& m);
void CasesVidesAutour(Case& c, unsigned int compte, CasesVides& v, Map& m);
void Vider(Map& m, Case& c, CasesVides& v);
bool ExisteCasesVides(Map& m);
bool ExisteCases(Map& m);
void DemasquerMines(Map& m, Probleme& p);
void detruireMap(Map& m);
#endif