#include <iostream>
#include <string>
#include <vector>

#include "../include/Reader.h"
#include "../include/ReaderA.h"
#include "../include/SeqA.h"

using namespace std;

ReaderA::ReaderA(istream *is) :
        Reader(is) {

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

    // On parcours le fichier tanqu'on n'est pas arrivé a la fin.
    while (!this->file_ptr->eof()) {
        // on recupere le prochain caractere du fichier et on avance le curseur
        c = this->file_ptr->get();
        // on verifie que le caractere est visible
        if (c > ' ') {
            // c'est un ; ou > donc on ouvre l'entete
            if (c == ';' || c == '>') {
                // si on a deja la sequence, c'est que l'on arrive sur un nouvel entete de sequence
                if (has_seq) {
                    // on recule le curseur de fichier d'un caractere
                    this->file_ptr->seekg((int) this->file_ptr->tellg() - 1);

                    break;
                }

                // on enregistre que l'on a bien recuperer l'entete
                has_entete = true;

                // On lit la ligne de l'entete
                do {
                    entete.push_back(c);
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            }
            // Ce n'est pas un ";" ou ">", et on a recupere l'entete
            // on arrive donc sur la sequence
            else if (has_entete) {

                // on enregistre que l'on a bien recupere la sequence
                has_seq = true;

                // on lit toute la ligne et on l'ajoute à la sequence
                do {
                    seq.push_back(c);
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

    // on a l'entete, et la sequence, on peut retourner l'object de Sequence A
    if (has_entete && has_seq) {
        return new SeqA(entete, seq);
    }

    // on a que l'entete, il manque donc la sequence, le fichier est mal formaté
    // on leve une erreur.
    if (has_entete) {
        throw "Fichier mal formatée";
    }

    // on a ni l'un, ni l'un, on retourne null.
    return NULL;
}
