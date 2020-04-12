#include <iostream>
#include <string>
#include <vector>

#include "../include/Reader.h"
#include "../include/ReaderQ.h"
#include "../include/SeqQ.h"

using namespace std;

ReaderQ::ReaderQ(istream *file_ptr) :
        Reader(file_ptr) {

}

string ReaderQ::getFormat() const {
    return "FASTQ";
}

SeqQ *ReaderQ::next() {
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

    while (!this->file_ptr->eof()) {
        c = this->file_ptr->get();

        if (c > ' ') {
            if (need_qualite) {
                // On attends la qualite.
                getline(*(this->file_ptr), tmp);
                qualite += c + tmp;

                // on la qualité, on peut stopper le parcours.
                break;
            } else if (c == '@') {
                // Entete de sequence
                if (has_entete || has_seq) {
                    throw "Fichier mal formatté";
                }

                has_entete = true;

                getline(*(this->file_ptr), entete);
            } else if (c == '+') {
                // Fin d'entete de sequence
                if (!has_entete || !has_seq) {
                    throw "Fichier mal formatté";
                }

                getline(*(this->file_ptr), tmp);

                need_qualite = true;
            } else if (has_entete) {
                // On a une entete, on charge la sequence.
                if (ReaderQ::isNucleic(c) || ReaderQ::isAmino(c)) {
                    has_seq = true;
                    seq += c;
                } else {
                    seq += 'N';
                    errors.push_back(
                            "[POS: " + to_string(seq.size()) + "] Wrong character."
                    );
                }
            } else {
                throw "Erreur : en-tête mal formatée";
            }
        }
    }

    if (need_qualite && has_seq) {
        return new SeqQ(errors, entete, seq, qualite);
    }

    if (has_entete || has_seq) {
        throw "Fichier mal formatée";
    }

    return NULL;
}
