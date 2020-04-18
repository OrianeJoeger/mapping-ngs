#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "Seq.h"

class Reader {
protected:
    /**
     * Pointeur sur fichier, permet de lire le fichier
     *
     * @property
     */
    std::istream *file_ptr;

public:
    /**
     * Retourne si un charactere donnée est un nucléotide
     *
     * @param char c
     * @return bool
     */
    static bool isNucleic(char c);

    /**
     * Retourne si un charactere donnée est un acide aminé
     *
     * @param char c
     * @return bool
     */
    static bool isAmino(char c);

    /**
     * @constructor
     * @param file_ptr Pointeur sur fichier
     */
    Reader(std::istream *is);

    /**
     * Methode abstraite
     * Recupere la prochaine sequence dans le fichier
     *
     * @return Seq*
     */
    virtual Seq *next() = 0;

    /**
     * Methode abstraite
     * Retourne le format du fichier lu
     *
     * @return string
     */
    virtual std::string getFormat() const = 0;
};

#endif //CPP_FASTREADER_H