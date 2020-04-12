#include <iostream>
#include <string>
#include <fstream>

#ifndef __FASTX_H__
#define __FASTX_H__

// se renseigner sur cassert 

class FastX {
protected:
    std::string entete;
    std::string seqbio;
public:
    FastX(const std::string &entete = "", const std::string &seqbio = "");

    std::string getSeqbio();

    std::string getHeader();

    void setHeader(std::string header);

    size_t getSeqbioLength();

    std::string getSeqComp();

    std::string getSeqRev();

    std::string getSeqRevComp();
};

#endif