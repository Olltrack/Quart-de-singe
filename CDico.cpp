#include<iostream>
#include<fstream>
#include<iomanip>
#include"CDico.h"
using namespace std;
#pragma warning(disable:4996)

void initialiser(conteneurDico& CD, unsigned int capa) {
	CD.capacite = capa;
	CD.motDico = new char* [capa];
}

void detruire(conteneurDico& CD) {
	delete[] CD.motDico;
	CD.motDico = NULL;
}

void ecrire(conteneurDico CD, unsigned int i, char* it) {
	char* pakistan = { 0 };
	pakistan = new char[26] ;
	strcpy(pakistan, it);
	CD.motDico[i] = pakistan;
}

/**
* @brief Charge le dictionnaire dans un conteneur de mots
* @param CD Un objet de type conteneurDico qui représente le dictionnaire
*/
void dico(conteneurDico& CD) {
    ifstream in("ods4.txt");
    if (!in) {
        cerr << "le dictionnaire n'a pu etre ouvert" << endl;
        exit(2);
    }
    int nb = 0;
    const int MAX = 26;
    char s[MAX];
    in >> setw(MAX) >> s;
    while (in) {
        ++nb; // ça s'est bien passé, on le compte
        in >> setw(MAX) >> s; // on essaye de lire le mot suivant
    }
    initialiser(CD, nb);
    in.clear();
    in.seekg(0);
    int i = 0;
    while (in >> setw(MAX) >> s) {
        ecrire(CD, i, s);
        ++i;

    }
    in.close();
}