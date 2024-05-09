#pragma once

enum {
    maxchar = 30
};


struct Joueur { //conteneur td
    char nomj[maxchar];
    double quart_de_singe;
    bool humain;
};

struct Jeu {
    unsigned int nbj;
    Joueur* joueurs;
    char mot[26];
};

void initialiser(Jeu& j, unsigned int capa);

void detruire(Jeu& j);

void ecrire(Jeu& je, unsigned int i, Joueur& jo, char* caractère);




