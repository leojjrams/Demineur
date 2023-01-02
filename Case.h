#ifndef _CASE_
#define _CASE_

typedef enum Etat { Drapeau, Masqué, Démasqué };
typedef enum Type { Mine, Vide };

struct Case {
	unsigned int x;
	unsigned int y;
	Etat EtatActuel;
	Type TypeCase;
	unsigned int nbMines;
};

struct CasesVides {
	unsigned int capacite;
	unsigned int Extension;
	unsigned int nbCases;
	Case* tab;
};

void initialiserTab(CasesVides& v, unsigned int capa, unsigned int ext);
void detruireTab(CasesVides& v);
void ajouter(CasesVides& v, unsigned int indice, Case it);

#endif