#ifndef __FASTA_H__
#define __FASTA_H__

#include "FastX.h"
#include <string>


class FastA : public FastX {
public:
    FastA(const std::string &entete = "", const std::string &seqbio = "");

    virtual std::string getType();

    virtual void fromStream(std::istream &is);
};

#endif