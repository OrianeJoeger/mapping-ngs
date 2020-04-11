#include <iostream>
#include <string>

#include "../include/FastQ.h"

using namespace std;

FastQ::FastQ(const string &entete, const string &seqbio, const string &qualite) :
        FastX(entete, seqbio),
        qualite(qualite) {

}

string FastQ::getType() {
    return "FASTQ";
}

void FastQ::fromStream(istream &is) {
    char c, old_c = '\n';
    bool ok = is.good();
    entete = seqbio = "";
    //suppression des lignes vides
    while (ok && !is.eof()) {
        if (old_c == '\n') {
            c = is.peek();
            ok = (c != '@');
        }
        if (ok) {
            c = is.get();
            if (c > ' ') {
                throw "Erreur : en-tête mal formatée";
            }
            old_c = c;
        }
    }
    getline(is, entete);
    ok = is.good();
    while (ok && !is.eof()) {
        if (old_c >= '\n') {
            c = is.peek();
            ok = (c != '+');
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
    ok = is.good();
    while (ok && !is.eof()) {
        if (old_c >= '\n') {
            c = is.peek();
        }
    }

    //récupérer l'en-tête

    //lire la séquence jusqu'à fin de fichier ou nouvelle séquence
}

void FastQ::toStream(ostream &os) {}
