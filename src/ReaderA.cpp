#include <iostream>
#include <string>
#include <vector>

#include "../include/Reader.h"
#include "../include/ReaderA.h"
#include "../include/SeqA.h"

using namespace std;

ReaderA::ReaderA(istream *file_ptr) :
        Reader(file_ptr) {

}

string ReaderA::getFormat() const {
    return "FASTA";
}

SeqA *ReaderA::next() {
    char c;
    bool
            has_entete = false,
            has_seq = false;
    string
            entete = "",
            seq = "",
            tmp;

    vector <string> errors;

    while (!this->file_ptr->eof()) {
        c = this->file_ptr->get();

        if (c > ' ') {
            if (c == ';' || c == '>') {
                if (has_seq) {
                    this->file_ptr->seekg((int) this->file_ptr->tellg() - 1);

                    break;
                }

                has_entete = true;

                getline(*(this->file_ptr), tmp);
                entete += tmp;
            } else if (has_entete) {
                if (ReaderA::isNucleic(c) || ReaderA::isAmino(c)) {
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

    if (has_entete && has_seq) {
        return new SeqA(errors, entete, seq);
    }

    if (has_entete || has_seq) {
        throw "Fichier mal formatée";
    }

    return NULL;
}
