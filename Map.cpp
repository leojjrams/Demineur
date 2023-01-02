#include<iostream>
#include"Map.h"
using namespace std;

void initialiserMap(Map& m, unsigned int h, unsigned int l) {
	m.hauteur = h;
	m.largeur = l;
	m.Conteneur = new Case * [h];
	for (int i = 0; i < h; ++i) {
		m.Conteneur[i] = new Case[l];
		for (int j = 0; j < l; ++j) {
			m.Conteneur[i][j].EtatActuel = Masqué;
			m.Conteneur[i][j].TypeCase = Vide;
			m.Conteneur[i][j].x = j;
			m.Conteneur[i][j].y = i;
			m.Conteneur[i][j].nbMines = 0;
		}
	}
}

bool VidePossible(Map& m) {
	for (int i = 0; i < m.hauteur; ++i) {
		for (int j = 0; j < m.largeur; ++j) {
			if (m.Conteneur[i][j].TypeCase != Mine && m.Conteneur[i][j].EtatActuel != Démasqué && EstVideAutour(m.Conteneur[i][j], m) == 1) {
				return true;
			}
		}
	}
	return false;
}

bool EstVideAutour(Case c, Map& m) {
	int PosXTest, PosYTest;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			PosXTest = c.x + j;
			PosYTest = c.y + i;
			if (PosXTest >= 0 && PosYTest >= 0 && PosXTest < m.largeur && PosYTest < m.hauteur) {
				if (m.Conteneur[PosYTest][PosXTest].EtatActuel == Démasqué) {
					return false;
				}
			}
		}
	}
	return true;
}

void AjouterMines(Map& m, Probleme& p, unsigned int mines) {
	int PosX, PosY, compte = 0;
	unsigned int dimensions = m.hauteur * m.largeur;
	if (mines < dimensions) {
		p.PosMines = new int[mines];
		while (compte < mines) {
			PosX = rand() % m.largeur;
			PosY = rand() % m.hauteur;
			if (VidePossible(m) == 1) {
				if (m.Conteneur[PosY][PosX].TypeCase != Mine && m.Conteneur[PosY][PosX].EtatActuel != Démasqué && EstVideAutour(m.Conteneur[PosY][PosX], m) == 1) {
					m.Conteneur[PosY][PosX].TypeCase = Mine;
					p.PosMines[compte] = (PosX + 1) * (PosY + 1);
					++compte;
				}
			}
			else {
				if (m.Conteneur[PosY][PosX].TypeCase != Mine && m.Conteneur[PosY][PosX].EtatActuel != Démasqué) {
					m.Conteneur[PosY][PosX].TypeCase = Mine;
					p.PosMines[compte] = (PosX + 1) * (PosY + 1);
					++compte;
				}
			}
		}
	}
	else if (mines >= dimensions) {
		PosX = 0; PosY = 0;
		for (int i = 0; i < dimensions; ++i) {
			m.Conteneur[PosY][PosX].TypeCase = Mine;
			++PosX;
			++compte;
			if (compte % m.hauteur == 0) {
				++PosY;
				PosX -= m.hauteur;
			}
		}
	}
}

unsigned int CompterMines(Case c, Map& m) {
	unsigned int compte = 0;
	int PosXTest, PosYTest;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			PosXTest = c.x + j;
			PosYTest = c.y + i;
			if (PosXTest >= 0 && PosYTest >= 0 && PosXTest < m.largeur && PosYTest < m.hauteur) {
				if (m.Conteneur[PosYTest][PosXTest].TypeCase == Mine) {
					++compte;
				}
			}
		}
	}
	return compte;
}

void EnrMines(Map& m) {
	for (int i = 0; i < m.hauteur; ++i) {
		for (int j = 0; j < m.largeur; ++j) {
			if (m.Conteneur[i][j].TypeCase == Vide) {
				m.Conteneur[i][j].nbMines = CompterMines(m.Conteneur[i][j], m);
			}
		}
	}
}

void afficher(Map& m, Probleme& p) {
	unsigned int compteur = 0, indice = 0;
	cout << p.lignes << " " << p.colonnes << endl;
	while (indice < m.hauteur) {
		if (compteur % 2 == 0) {
			for (int j = 0; j < m.largeur; ++j) {
				cout << " ---";
			}
			cout << " " << endl;
		}
		else {
			for (int j = 0; j < m.largeur; ++j) {
				switch (m.Conteneur[indice][j].EtatActuel) {
				case Masqué:
					cout << "| . ";
					break;
				case Drapeau:
					cout << "| x ";
					break;
				case Démasqué:
					if (m.Conteneur[indice][j].TypeCase == Mine) {
						cout << "| m ";
					}
					else {
						if (m.Conteneur[indice][j].nbMines == 0) {
							cout << "|   ";
						}
						else {
							cout << "| " << m.Conteneur[indice][j].nbMines << " ";
						}
					}
					break;
				}
			}
			cout << "|" << endl;
			++indice;
		}
		++compteur;
	}
	for (int j = 0; j < m.largeur; ++j) {
		cout << " ---";
	}
	cout << " " << endl;
}

void ViderAutour(Case& c, Map& m) {
	int PosXTest, PosYTest;
	c.EtatActuel = Démasqué;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			PosXTest = c.x + j;
			PosYTest = c.y + i;
			if (PosXTest >= 0 && PosYTest >= 0 && PosXTest < m.largeur && PosYTest < m.hauteur) {
				if (m.Conteneur[PosYTest][PosXTest].nbMines > 0) {
					m.Conteneur[PosYTest][PosXTest].EtatActuel = Démasqué;
				}
			}
		}
	}
}

void CasesVidesAutour(Case& c, unsigned int compte, CasesVides& v, Map& m) {
	int PosXTest, PosYTest;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			PosXTest = c.x + j;
			PosYTest = c.y + i;
			if (PosXTest >= 0 && PosYTest >= 0 && PosXTest < m.largeur && PosYTest < m.hauteur) {
				if (m.Conteneur[PosYTest][PosXTest].TypeCase == Vide && m.Conteneur[PosYTest][PosXTest].nbMines == 0 && m.Conteneur[PosYTest][PosXTest].EtatActuel == Masqué) {
					m.Conteneur[PosYTest][PosXTest].EtatActuel = Démasqué;
					ajouter(v, v.nbCases, m.Conteneur[PosYTest][PosXTest]);
				}
			}
		}
	}
}

void Vider(Map& m, Case& c, CasesVides& v) {
	int compte = -1;
	do {
		++compte;
		CasesVidesAutour(c, compte, v, m);
		c = v.tab[compte];
		if (v.nbCases == 1) {
			break;
		}
	} while (compte < v.nbCases);
	for (int i = 0; i < v.nbCases; ++i) {
		c = v.tab[i];
		if (v.tab[i].nbMines == 0) {
			ViderAutour(c, m);
		}
	}
}

bool ExisteCasesVides(Map& m) {
	for (int i = 0; i < m.hauteur; ++i) {
		for (int j = 0; j < m.largeur; ++j) {
			if (m.Conteneur[i][j].TypeCase == Vide && m.Conteneur[i][j].nbMines == 0) {
				return true;
			}
		}
	}
	return false;
}

bool ExisteCases(Map& m) {
	for (int i = 0; i < m.hauteur; ++i) {
		for (int j = 0; j < m.largeur; ++j) {
			if (m.Conteneur[i][j].TypeCase == Vide) {
				return true;
			}
		}
	}
	return false;
}

void DemasquerMines(Map& m, Probleme& p) {
	for (int i = 0; i < p.lignes; ++i) {
		for (int j = 0; j < p.colonnes; ++j) {
			if (m.Conteneur[i][j].TypeCase == Mine) {
				m.Conteneur[i][j].EtatActuel = Démasqué;
			}
		}
	}
}

void detruireMap(Map& m) {
	delete[] m.Conteneur;
	m.Conteneur = NULL;
	m.hauteur = NULL;
	m.largeur = NULL;
}