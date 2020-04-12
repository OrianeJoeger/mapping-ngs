#include <iostream>
#include <string>

#include "../../include/parser/FastParserQ.h"
#include "../../include/FastQ.h"

using namespace std;

FastQ *FastParserQ::extract(istream *is) {
    char c;
    bool
            has_entete = false,
            has_seq = false,
            need_qualite = false;
    string
            entete = "",
            seq = "",
            qualite = "",
            tmp;

    vector <string> errors;

    while (!is->eof()) {
        c = is->get();

        if (c > ' ') {
            if (need_qualite) {
                // On attends la qualite.
                getline(*(is), tmp);
                qualite += c + tmp;

                // on la qualité, on peut stopper le parcours.
                break;
            } else if (c == '@') {
                // Entete de sequence
                if (has_entete || has_seq) {
                    throw "Fichier mal formatté";
                }

                has_entete = true;

                getline(*(is), entete);
            } else if (c == '+') {
                // Fin d'entete de sequence
                if (!has_entete || !has_seq) {
                    throw "Fichier mal formatté";
                }

                getline(*(is), tmp);

                need_qualite = true;
            } else if (has_entete) {
                // On a une entete, on charge la sequence.
                if (FastParserQ::isNucleic(c) || FastParserQ::isAmino(c)) {
                    has_seq = true;
                    seq += c;
                } else {
                    errors.push_back(
                            "Erreur : mauvais caractère rencontré a la position : " + to_string(is->tellg())
                    );
                    seq += 'N';
                }
            } else {
                throw "Erreur : en-tête mal formatée";
            }
        }
    }

    if (need_qualite && has_seq) {
        return new FastQ(errors, entete, seq, qualite);
    }

    if (has_entete || has_seq) {
        /*
        cerr << "H:" << entete << endl;
        cerr << "S:" << seq << endl;
        cerr << "Q:" << qualite << endl;
        */
        throw "Fichier mal formatée";
    }

    return NULL;
}
