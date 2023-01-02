#include<iostream>
#include"Jeu.h"
#pragma warning(disable:4996)
using namespace std;

void Commencer(Map& m, Probleme& p) {
	CasesVides v;
	int DebutX, DebutY;
	Case c;
	unsigned int compte = 0;
	if (ExisteCasesVides(m) == 1) {
		do {
			DebutX = rand() % p.colonnes;
			DebutY = rand() % p.lignes;
			c = m.Conteneur[DebutY][DebutX];
			++compte;
		} while (c.nbMines > 0 || c.TypeCase != Vide);
		Vider(m, m.Conteneur[DebutY][DebutX], v);
	}
	else {
		if (ExisteCases(m) == 1) {
			do {
				DebutX = rand() % p.colonnes;
				DebutY = rand() % p.lignes;
				c = m.Conteneur[DebutY][DebutX];
			} while (c.TypeCase != Vide);
			m.Conteneur[DebutY][DebutX].EtatActuel = Démasqué;
		}
		else {
			DebutX = rand() % p.colonnes;
			DebutY = rand() % p.lignes;
			c = m.Conteneur[DebutY][DebutX];
			m.Conteneur[DebutY][DebutX].EtatActuel = Démasqué;
		}
	}
}

bool Gagne(Map& m, Probleme& p) {
	unsigned int nbDemasque = 0;
	unsigned int objectif = (p.lignes * p.colonnes) - p.nbMines;
	for (int i = 0; i < p.lignes; ++i) {
		for (int j = 0; j < p.colonnes; ++j) {
			if (m.Conteneur[i][j].TypeCase == Vide && m.Conteneur[i][j].EtatActuel == Démasqué) {
				++nbDemasque;
			}
		}
	}
	if (nbDemasque == objectif) {
		return true;
	}
	return false;
}

bool Perdu(Map& m, Probleme& p) {
	for (int i = 0; i < p.lignes; ++i) {
		for (int j = 0; j < p.colonnes; ++j) {
			if ((m.Conteneur[i][j].EtatActuel == Démasqué && m.Conteneur[i][j].TypeCase == Mine) || (m.Conteneur[i][j].TypeCase == Vide && m.Conteneur[i][j].EtatActuel == Drapeau)) {
				return true;
			}
		}
	}
	return false;
}

void instruction(Map& m, Probleme& p) {
	int choix, saisie2, saisie3;
	CasesVides v;
	Texte saisie1;
	Statut StatutDuJeu = En_Cours;
	unsigned int nbCoups = 0, nbProb = 0, compteur = 0;
	char commande;
	while (StatutDuJeu == En_Cours) {
		cin >> choix;
		switch (choix) {
		case 1:
			cin >> saisie1.Contenu >> saisie2 >> saisie3;
			int hauteur;
			sscanf(saisie1.Contenu, "%d", &hauteur);
			p.lignes = hauteur;
			p.colonnes = saisie2;
			p.nbMines = saisie3;
			if (nbProb > 0) {
				detruireMap(m);
				detruireProb(p);
			}
			initialiserMap(m, p.lignes, p.colonnes);
			initialiserProb(p, 1, 2);
			initialiserTab(v, 1, 2);
			++nbProb;
			nbCoups = 0;
			break;
		case 2:
			afficher(m, p);
			break;
		case 3:
			if (Perdu(m, p) == 1) {
				cout << "game not won" << endl;
			}
			else {
				if (Gagne(m, p) == 1) {
					cout << "game won" << endl;
					DemasquerMines(m, p);
					afficher(m, p);
					StatutDuJeu = Terminé;
				}
				else {
					cout << "game not won" << endl;
				}
			}
			break;
		case 4:
			if (Perdu(m, p) == 1) {
				cout << "game lost" << endl;
				DemasquerMines(m, p);
				afficher(m, p);
				StatutDuJeu = Terminé;
			}
			else {
				cout << "game not lost" << endl;
			}
			break;
		case 5:
			cin >> saisie1.Contenu;
			int PosX, PosY = 0;
			sscanf(saisie1.Contenu, "%c %d", &commande, &PosX);
			int nblignes = p.lignes;
			if (PosX > (p.lignes * p.colonnes) - 1) {
				PosX = p.colonnes - 1;
				PosY = p.lignes - 1;
			}
			else {
				while (PosX - nblignes >= 0) {
					PosX -= p.lignes;
					++PosY;
				}
			}
			if (commande == 'D') {
				m.Conteneur[PosY][PosX].EtatActuel = Démasqué;
				if (nbCoups == 0) {
					AjouterMines(m, p, p.nbMines);
					EnrMines(m);
				}
				if (m.Conteneur[PosY][PosX].TypeCase == Vide && m.Conteneur[PosY][PosX].nbMines == 0) {
					ajouter(v, v.nbCases, m.Conteneur[PosY][PosX]);
					Vider(m, m.Conteneur[PosY][PosX], v);
				}
				++nbCoups;
				ecrire(p, compteur, saisie1);
				++compteur;
			}
			else if (commande == 'M') {
				if (m.Conteneur[PosY][PosX].EtatActuel == Masqué) {
					m.Conteneur[PosY][PosX].EtatActuel = Drapeau;
				}
				else if (m.Conteneur[PosY][PosX].EtatActuel == Drapeau) {
					m.Conteneur[PosY][PosX].EtatActuel = Masqué;
				}
				ecrire(p, compteur, saisie1);
				++compteur;
			}
			break;
		}
	}
}