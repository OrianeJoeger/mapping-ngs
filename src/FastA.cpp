#include <iostream>
#include <string>

#include "../include/FastA.h"

using namespace std;

FastA::FastA(const string &entete, const string &seqbio) :
        FastX(entete, seqbio) {

}

string FastA::getType() {
    return "FASTA";
}

void FastA::fromStream(istream &is) {
    char c, old_c = '\n';
    bool ok = is.good();
    this->entete = seqbio = "";

    //suppression des lignes vides
    while (ok && !is.eof()) {
        if (old_c == '\n') {
            c = is.peek();     //peek regarde le caractere suivant par rapport au curseur
            ok = (c != '>') && (c != ';'); // on test que ok ne soit ni un > ni un ; (&&= ET)
        }
        if (ok) {
            c = is.get(); // on avance le curseur et on l'envoi le caractère sur le quelle on viens de passer
            if (c > ' ') {    // il sais que la valeur espace il faut aller le regarder dans le table ASCII
                throw "Erreur : en-tête mal formatée";
            }
            old_c = c;
        }
    }

    getline(is, this->entete);
    ok = is.good();
    while (ok && !is.eof()) {
        if (old_c >= '\n') {
            c = is.peek();
            ok = (c != '>') && (c != ';');
        }
        if (ok) {
            c = is.get();
            if (c > ' ') {
                if (isNucl(c) || isAA(c)) {
                    seqbio += c;
                } else {
                    cerr << "Erreur : mauvais caractère rencontré" << endl;
                    seqbio += 'N';
                }
            }
            old_c = c;
        }
    }
    //vérifier que la ligne en cours commence par un chevron/point-virgule

    //récupérer l'en-tête

    //lire la séquence jusqu'à fin de fichier ou nouvelle séquence
}
