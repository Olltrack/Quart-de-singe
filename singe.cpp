#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<climits>
using namespace std;

#include"Joueur.h"
#include"CDico.h"
#pragma warning(disable:4996)

/**

* ================================================================================================================

* Auteurs  = HIEGEL Oleg et NGUYEN Phuong

* Fichier = SAEc++.cpp

* Description = Jeu du singe

* Date : 06/01/2023

* ================================================================================================================

*/

/**
 * @brief Initialise les joueurs en fonction des arguments de la ligne de commande
 *
 * @param jo Structure Joueur à initialiser
 * @param je Structure Jeu à initialiser
 * @param argv Arguments de la ligne de commande
 */
void init_joueur(Joueur& jo, Jeu& je, char* argv[]) {
    if (strlen(argv[1]) < 2)
    {
        cout << "Il faut au moins 2 joueurs";
        return;
    }
    je.nbj = strlen(argv[1]) - 1;
    initialiser(je, je.nbj);
    for (int i = 0; i <= je.nbj; ++i) {
        if (argv[1][i] == 'H')
            je.joueurs[i].humain = true;
        else if (argv[1][i] == 'R')
            je.joueurs[i].humain = false;
        cout << je.joueurs[i].humain << endl;
        ecrire(je, i, jo, argv[1]);
    }
}


void indice_plus(const Jeu& jeu, int* num) {
    if (*num < jeu.nbj)
        *num += 1;
    else
        *num = 0;
}


/**
 * @brief Vérifie si le mot de jeu existe dans le dictionnaire
 *
 * @param jeu Le jeu en cours.
 * @param CD Structure conteneurDico
 * @param abd Etat du jeu
 * @return int 1 si le mot existe, 0 sinon
 */
int verif_mot(const Jeu& jeu, const conteneurDico& CD, int* abd) {
    int x = 0;
    for (int i = 1; i < CD.capacite - 1; ++i) {
        if (strlen(CD.motDico[i]) > 2 && strcmp(CD.motDico[i], jeu.mot) == 0) {
            x = 1;
            *abd = 3;
        }

    }
    return x;
}

/**
* @brief Fait passer le numéro de joueur au joueur précédent
* @param jeu Le jeu en cours.
* @param num Numéro du joueur actuel
*/
void joueur_precedent(const Jeu& jeu, int* num) {
    if (*num < 1)
        *num = jeu.nbj;
    else
        *num -= 1;
}



/**
* @brief Fait passer le numéro de joueur au joueur suivant
* @param jeu Le jeu en cours.
* @param num Numéro du joueur actuel
*/
void joueur_suivant(const Jeu& jeu, int* num) {
    if (*num < jeu.nbj)
        *num += 1;
    else
        *num = 0;
}


/**
* @brief Fonction qui prend en entrée un objet de type Jeu et un objet de type conteneurDico,
* et renvoie un caractère.
* La fonction parcourt les mots du dictionnaire et
* retourne le prochain caractère du premier mot commençant par les mêmes lettres que jeu.mot.
* Si aucun mot ne convient, la fonction retourne '?'.
* @param jeu Le jeu en cours.
* @param CD un objet de type conteneurDico contenant le dictionnaire
* @param lettre un caractère qui n'est pas utilisé par la fonction et est là uniquement pour respecter la signature de la fonction
* @return le prochain caractère du premier mot du dictionnaire commençant par les mêmes lettres que jeu.mot, ou '?' si aucun mot ne convient
*/
char bot(const Jeu& jeu, const conteneurDico& CD, char lettre) {
    int l = strlen(jeu.mot);
    for (int i = 1; i < CD.capacite - 1; ++i) {
        if (strncmp(CD.motDico[i], jeu.mot, l) == 0) {
            if (strlen(CD.motDico[i]) > l) {
                return CD.motDico[i][l];
            }
        }
    }

    return '?';
}


/**
 * @brief Trouve un mot dans le dictionnaire qui commence par les mêmes lettres que jeu.mot et le stocke dans la chaîne de caractères question.
 *
 * @param jeu Le jeu en cours.
 * @param CD Le dictionnaire.
 * @param question La chaîne de caractères qui va contenir le mot trouvé.
 */
void bot_question(const Jeu& jeu, const conteneurDico& CD, char* question) {
    int l = strlen(jeu.mot);
    for (int i = 1; i < CD.capacite - 1; ++i) {
        if (strncmp(CD.motDico[i], jeu.mot, l) == 0) {
            if (strlen(CD.motDico[i]) > l) {
                strcpy(question, CD.motDico[i]);
                return;
            }
        }
    }
    strcpy(question, "!");
}


void question(Jeu& jeu, conteneurDico& CD, int *num, float* qds, int* abd) {
    
    char question[26] = "";
    cout << jeu.joueurs[*num].nomj << ", saisir le mot > ";
    if (jeu.joueurs[*num].humain == true)
        cin >> question;
    else {
        bot_question(jeu, CD, question);
        cout << question << endl;
    }

    for (int i = 0; i < strlen(jeu.mot); ++i) {
        if (jeu.mot[i] != question[i]) {
            cout << "le mot " << question << " ne commence pas par les lettres attendues, le joueur " << jeu.joueurs[*num].nomj << " prend un quart de singe" << endl;
            jeu.joueurs[*num].quart_de_singe += *qds;
            return;
        }
    }
    strcpy(jeu.mot, question);
    if (verif_mot(jeu, CD, &*abd) == 0) {
        cout << "le mot " << jeu.mot << " n'existe pas, le joueur " << jeu.joueurs[*num].nomj << " prend un quart de singe" << endl;
        jeu.joueurs[*num].quart_de_singe += *qds;
        return;
    }
    else if (verif_mot(jeu, CD, &*abd) == 1) {
        joueur_suivant(jeu, *&num);
        cout << "le mot " << jeu.mot << " existe, le joueur " << jeu.joueurs[*num].nomj << " prend un quart de singe" << endl;
        jeu.joueurs[*num].quart_de_singe += *qds;
        return;
    }
}

/**
* @brief Initialise le score de chaque joueur à 0
* @param jeu Le jeu en cours.
*/
void init_score(Jeu& jeu) {
    for (int i = 0; i <= jeu.nbj; ++i) {
        jeu.joueurs[i].quart_de_singe = 0;
        if (jeu.joueurs[i].quart_de_singe < 0) {
            jeu.joueurs[i].quart_de_singe = 0;
        }
        if (jeu.joueurs[i].quart_de_singe > 1) {
            jeu.joueurs[i].quart_de_singe = 0;
        }
    }
}

/**
* @brief Vérifie si aucun joueur n'a atteint 1 quart de singe
* @param jeu Le jeu en cours
* @return int Retourne 0 si au moins un joueur a atteint 1 quart de singe, 1 sinon
*/
int verif_score(Jeu& jeu) {
    for (int i = 0; i <= jeu.nbj; ++i) {
        if (jeu.joueurs[i].quart_de_singe == 1)
            return(0);
    }
    return(1);
}

int main(int argc, char* argv[]) //crée tableau de charactères, argc : nb de char/éléments, char** argv : chaine de char
{
    Joueur joueur;
    Jeu jeu = { NULL };
    conteneurDico CD;
    init_joueur(joueur, jeu, argv);
    init_score(jeu);
    dico(CD);
    int num = 0;
    float qds = 0.25;
    do {
        int abd = 0;
        do {
            cout << jeu.joueurs[num].nomj << ", (" << jeu.mot << ") > ";
            char lettre = { 0 };
            if (jeu.joueurs[num].humain == true) {
                cin >> lettre;
                cin.ignore(INT_MAX, '\n');
                lettre = toupper(lettre);
            }
            else {
                lettre = bot(jeu, CD, lettre);
                cout << lettre << endl;
            }

            if (lettre == '!') {
                abd = 1;
                break;
            }
            else if (lettre == '?') {
                abd = 2;
                break;
            }
            else {
                jeu.mot[strlen(jeu.mot)] = lettre;
                if (verif_mot(jeu, CD, &abd) == 1) {
                    abd = 3;
                    break;
                }
            }
            indice_plus(jeu, &num);
        } while (abd == 0 || verif_mot(jeu, CD, &abd) == 0); //prochain tour jusqu'à ce qu'un mot du dictionnaire ou un caractère spécial soit entré
        if (abd == 1) { //!
            cout << "le joueur " << jeu.joueurs[num].nomj << " abandonne la manche et prend un quart de singe" << endl;
            jeu.joueurs[num].quart_de_singe += 0.25;
        }
        else if (abd == 2) { //?
            joueur_precedent(jeu, &num);
            question(jeu, CD, &num, &qds, &abd);
        }
        else if (abd == 3) { //si le mot existe
            cout << "le mot " << jeu.mot << " existe, le joueur " << jeu.joueurs[num].nomj << " prend un quart de singe" << endl;
            jeu.joueurs[num].quart_de_singe += qds;
        }
        //affichage du score
        for (int j = 0; j < jeu.nbj + 1; ++j) {
            cout << jeu.joueurs[j].nomj << " : " << jeu.joueurs[j].quart_de_singe;
            if ( j < jeu.nbj ) {
                cout << "; ";
            }
        }
        //désallouer le mot
        int longueur = strlen(jeu.mot);
        for (int i = 0; i <= longueur; i++) {
            jeu.mot[i] = '\0';
        }
        cout << endl;
    } while ((verif_score(jeu) == 1));
    cout << "La partie est finie";
    return 0;
}