#pragma once

struct conteneurDico {
	unsigned int capacite;
	char** motDico;
};

void initialiser(conteneurDico& CD, unsigned int capa);

void detruire(conteneurDico& CD);

void ecrire(conteneurDico CD, unsigned int i, char* it);

void dico(conteneurDico& CD);