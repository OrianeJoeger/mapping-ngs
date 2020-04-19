#include <iostream>
#include <string>

#include "../include/Reader.h"
#include "../include/ReaderQ.h"
#include "../include/SeqQ.h"

using namespace std;

ReaderQ::ReaderQ(istream *is) :
        Reader(is) {

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
            qualite = "";

    while (!this->file_ptr->eof()) {
        c = this->file_ptr->get();

        if (c > ' ') {
            if (need_qualite) {
                // On attends la qualite.
                // read & append line
                do {
                    qualite += c;
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');

                // on la qualité, on peut stopper le parcours.
                break;
            } else if (c == '@') {
                // Entete de sequence
                if (has_entete || has_seq) {
                    throw "Fichier mal formatté";
                }

                has_entete = true;

                // read & append line
                do {
                    entete += c;
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            } else if (c == '+') {
                // Fin d'entete de sequence
                if (!has_entete || !has_seq) {
                    throw "Fichier mal formatté";
                }

                need_qualite = true;

                // move to next line
                while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            } else if (has_entete) {
                // On a une entete, on charge la sequence.
                has_seq = true;
                // read & append line
                do {
                    seq += c;
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            }
            // Sinon, on avait pas d'entete, et on attend pas ce caractere
            // On affiche une erreur.
            else {
                cerr << "Mauvais caratete rencontré : " << c << endl;
                // La ligne courante est corropu donc on la saute.
                while (!this->file_ptr->eof() && this->file_ptr->get() != '\n');
            }
        }
    }

    if (need_qualite && has_seq) {
        return new SeqQ(entete, seq, qualite);
    }

    // on a que l'entete, il manque donc la sequence, le fichier est mal formaté
    // on leve une erreur.
    if (has_entete) {
        throw "Fichier mal formatée";
    }

    return NULL;
}
