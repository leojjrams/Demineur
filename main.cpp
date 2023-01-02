#include<iostream>
#include"Map.h"
#include"Jeu.h"

int main() {
	Map m;
	Probleme p;
	srand(time(NULL));
	instruction(m, p);
	return 0;
}