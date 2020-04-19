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

    // On parcours le fichier tanqu'on n'est pas arrivé a la fin.
    while (!this->file_ptr->eof()) {
        // on recupere le prochain caractere du fichier et on avance le curseur
        c = this->file_ptr->get();

        // on verifie que le caractere est visible
        if (c > ' ') {
            // on attends la qualite (on a donc deja l'entete et la sequence)
            if (need_qualite) {

                // On lit la ligne de qualite
                do {
                    qualite.push_back(c);
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');

                // on la qualité, on peut stopper le parcours.
                break;
            }
            // c'est un @ donc on ouvre l'entete
            else if (c == '@') {
                // Si on a deja l'entete, on ne doit pas avoir a nouveau un entete
                // le fichier est donc mal formaté
                if (has_entete) {
                    throw "Fichier mal formatté";
                }
                // Sinon
                // on enregistre que l'on a bien recuperer l'entete
                has_entete = true;

                // On lit la ligne de l'entete
                do {
                    entete.push_back(c);
                } while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            }
            // c'est un + donc on ferme l'entete
            else if (c == '+') {
                // Si on a pas l'entete ou pas la sequence, on ne doit pas avoir la fermeture de l'entete
                // le fichier est donc mal formaté
                if (!has_entete || !has_seq) {
                    throw "Fichier mal formatté";
                }

                // Sinon
                // On a bien l'entete, la sequence, la fermeture de l'entete, on attends donc la qualité
                need_qualite = true;

                // on saute la ligne
                while (!this->file_ptr->eof() && (c = this->file_ptr->get()) != '\n');
            }
            // Ce n'est pas un "@" ou "+", et on a recupere l'entete
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

    // On a la qualite, la sequence, on a forcément l'entete, on  peut retourner l'object de Sequence Q
    if (need_qualite && has_seq) {
        return new SeqQ(entete, seq, qualite);
    }

    // on a que l'entete, il manque donc la sequence, le fichier est mal formaté
    // on leve une erreur.
    if (has_entete) {
        throw "Fichier mal formatée";
    }

    // On rien recuperer, on retourne null
    return NULL;
}
