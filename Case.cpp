#include<iostream>
#include"Case.h"

void initialiserTab(CasesVides& v, unsigned int capa, unsigned int ext) {
	v.capacite = capa;
	v.Extension = ext;
	v.nbCases = 0;
	v.tab = new Case[capa];
}

void detruireTab(CasesVides& v) {
	delete[] v.tab;
	v.nbCases = 0;
	v.capacite = 1;
}

void ajouter(CasesVides& v, unsigned int indice, Case it) {
	if (indice >= v.capacite) {
		int newTaille = (indice + 1) * v.Extension;
		Case* newT = new Case[newTaille];
		for (int j = 0; j < v.capacite; ++j) {
			newT[j] = v.tab[j];
		}
		delete[] v.tab;
		v.tab = newT;
		v.capacite = newTaille;
	}
	v.tab[indice] = it;
	++v.nbCases;
}