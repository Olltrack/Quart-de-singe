#include <iostream>
#include <cassert>
#include<cstdlib>
#include<cstring>
using namespace std;
#include"Joueur.h"
#pragma warning(disable:4996)

void initialiser(Jeu& j, unsigned int capa) {
    
    j.nbj = capa;
    j.joueurs = new Joueur[capa];
}

void detruire(Jeu& j) {
    delete[] j.joueurs;
    j.joueurs = NULL;
}


void ecrire(Jeu& je, unsigned int i, Joueur& jo, char* caract�res) {

    char pakistan[30] = "";
    sprintf(pakistan, "%d", i + 1);
    pakistan[strlen(pakistan)] = caract�res[i];
    strcpy(je.joueurs[i].nomj, pakistan);

}