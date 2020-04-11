//
// Created by Guillaume ALLEGRET on 11/04/2020.
//

#include <iostream>
#include <string>

#include "../include/FastReader.h"
#include "../include/FastX.h"
#include "../include/FastA.h"
#include "../include/FastQ.h"

using namespace std;

FastReader::FastReader(istream *file_ptr)
        : file_ptr(file_ptr), type(0) {
    char c;

    while (!this->file_ptr->eof() && (c = this->file_ptr->get()) > ' ') {
        if (c == ';' || c == '>') {
            this->type = FastReader::TYPE_FASTA;
        } else if (c == '@') {
            this->type = FastReader::TYPE_FASTQ;
        }

        break;
    }

    if (this->type == 0) {
        throw "Error unknown format type";
    }

    // rewind ptr
    this->file_ptr->seekg(0);
}

bool FastReader::isNucleic(char c) {
    return c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'U' || c == 'R' || c == 'Y' || c == 'S' || c == 'W' ||
           c == 'K' || c == 'M' || c == 'B' || c == 'D' || c == 'H' || c == 'V' || c == 'N' || c == '.' || c == '-';
}

bool FastReader::isAmino(char c) {
    return c == 'A' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' ||
           c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' ||
           c == 'V' || c == 'W' || c == 'Y';
}

FastA *FastReader::extractFastA() {
    char c;
    bool
            has_entete = false,
            has_seq = false;
    string
            entete = "",
            seq = "",
            tmp;

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
                if (FastReader::isNucleic(c) || FastReader::isAmino(c)) {
                    has_seq = true;
                    seq += c;
                } else {
                    cerr << "Erreur : mauvais caractère rencontré" << endl;
                    seq += 'N';
                }
            } else {
                throw "Erreur : en-tête mal formatée";
            }
        }
    }

    if (has_entete && has_seq) {
        return new FastA(entete, seq);
    }

    if (has_entete || has_seq) {
        throw "Fichier mal formatée";
    }

    return NULL;
}

FastQ *FastReader::extractFastQ() {

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
                if (FastReader::isNucleic(c) || FastReader::isAmino(c)) {
                    has_seq = true;
                    seq += c;
                } else {
                    cerr << "Erreur : mauvais caractère rencontré" << endl;
                    seq += 'N';
                }
            } else {
                throw "Erreur : en-tête mal formatée";
            }
        }
    }

    if (need_qualite && has_seq) {
        return new FastQ(entete, seq, qualite);
    }

    if (has_entete || has_seq) {
        cerr << "H:" << entete << endl;
        cerr << "S:" << seq << endl;
        cerr << "Q:" << qualite << endl;

        throw "Fichier mal formatée";
    }

    return NULL;
}

FastX *FastReader::next() {
    switch (this->type) {
        case FastReader::TYPE_FASTA:
            return this->extractFastA();

        case FastReader::TYPE_FASTQ:
            return this->extractFastQ();
    }

    return NULL;
}

string FastReader::getFormat() {
    switch (this->type) {
        case FastReader::TYPE_FASTA:
            return "FASTA";

        case FastReader::TYPE_FASTQ:
            return "FASTQ";
    }

    return NULL;
}