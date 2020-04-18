#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <iostream>
#include <string>
#include <vector>

#include "Reader.h"
#include "Seq.h"

using namespace std;

class FastFile {

private:
    /**
     * Données sur les sequences
     *
     * @property
     */
    vector<Seq *> data;
    /**
     * Format du fichier detecte
     *
     * @property
     */
    string format;

protected:
    /**
     * Detecte le type fichier et retourne le Reader approprié
     *
     * @param istream* is Pointeur sur input_stream
     *
     * @return Reader
     */
    static Reader *getReader(istream *is);

public:
    /**
     * @constructor
     * @param char* file
     */
    FastFile(char *file);

    /**
     * Affiche le format du fichier
     */
    void printFormat();

    /**
     * Affiche le nombre de sequence
     */
    void printDataSize();

    /**
     * Affiche les sequences
     *
     * @param bool only_seq_with_error Affiche les sequences avec erreurs uniquement
     * @param bool comp Affiche les complements des sequences
     * @param bool rev Affiche les reverses des sequences
     */
    void printData(bool only_seq_with_error, bool comp, bool rev);

    /**
     * Affiche les erreurs
     */
    void printErrors();

    /**
     * Retourne les sequences
     *
     * @return
     */
    vector<Seq *> getData();
};

#endif //CPP_FASTFILE_H