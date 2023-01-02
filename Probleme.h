#ifndef _PROBLEME_
#define _PROBLEME_

#include<iostream>
#include"Texte.h"

struct Probleme {
	unsigned int lignes;
	unsigned int colonnes;
	unsigned int nbMines;
	int* PosMines;
	Texte* Historique;
	unsigned int capacite;
	unsigned int Extension;
	unsigned int nbrcoups;
};

void initialiserProb(Probleme& p, unsigned int capa, unsigned int ext);
void ecrire(Probleme& p, unsigned int indice, Texte it);
void detruireProb(Probleme& p);

#endif