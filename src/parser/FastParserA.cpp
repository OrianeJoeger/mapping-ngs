#include <iostream>
#include <string>
#include <vector>

#include "../../include/parser/FastParserA.h"
#include "../../include/FastX.h"
#include "../../include/FastA.h"

using namespace std;

FastA *FastParserA::extract(istream *is) {
    char c;
    bool
            has_entete = false,
            has_seq = false;
    string
            entete = "",
            seq = "",
            tmp;

    vector <string> errors;

    while (!is->eof()) {
        c = is->get();

        if (c > ' ') {
            if (c == ';' || c == '>') {
                if (has_seq) {
                    is->seekg((int) is->tellg() - 1);

                    break;
                }

                has_entete = true;

                getline(*(is), tmp);
                entete += tmp;
            } else if (has_entete) {
                if (FastParserA::isNucleic(c) || FastParserA::isAmino(c)) {
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

    if (has_entete && has_seq) {
        return new FastA(errors, entete, seq);
    }

    if (has_entete || has_seq) {
        throw "Fichier mal formatée";
    }

    return NULL;
}
