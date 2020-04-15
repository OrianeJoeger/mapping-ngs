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
            seq = "";

    vector <string> errors;

    while (!this->file_ptr->eof()) {
        c = this->file_ptr->get();
        if (c > ' ') {
            if (c == ';' || c == '>') {
                if (has_seq) {
                    // we already have a seq, so this is a new header :
                    // we move back file cursor, and we stop while
                    this->file_ptr->seekg((int) this->file_ptr->tellg() - 1);

                    break;
                }

                has_entete = true;

                // read & append line
                do {
                    entete += c;
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            } else if (has_entete) {
                has_seq = true;
                do {
                    seq += c;
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            } else {
                cerr << "Wrong character" << endl;
                // move cursor to next line
                while (!this->file_ptr->eof() && this->file_ptr->get() != '\n');
            }
        }
    }

    if (has_entete && has_seq) {
        return new SeqA(entete, seq);
    }

    if (has_entete || has_seq) {
        throw "Fichier mal formatée";
    }

    return NULL;
}
