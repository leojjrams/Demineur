#include<iostream>
#include"Probleme.h"
#include"Texte.h"

void initialiserProb(Probleme& p, unsigned int capa, unsigned int ext) {
	p.capacite = capa;
	p.Extension = ext;
	p.Historique = NULL;
	p.Historique = new Texte[capa];
	p.nbrcoups = 0;
}

void ecrire(Probleme& p, unsigned int indice, Texte it) {
	if (indice >= p.capacite) {
		int newTaille = indice * p.Extension;
		Texte* newT = new Texte[newTaille];
		for (int j = 0; j < p.capacite; ++j) {
			newT[j] = p.Historique[j];
		}
		delete[] p.Historique;
		p.Historique = newT;
		p.capacite = newTaille;
	}
	p.Historique[indice] = it;
	++p.nbrcoups;
}

void detruireProb(Probleme& p) {
	if (p.nbrcoups > 0) {
		delete[] p.PosMines;
		p.PosMines = NULL;
	}
	delete[] p.Historique;
	p.Historique = NULL;
}