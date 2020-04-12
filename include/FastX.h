#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifndef __FASTX_H__
#define __FASTX_H__

// se renseigner sur cassert 

class FastX {
protected:
    std::string entete;
    std::string seqbio;

    std::vector <std::string> errors;
public:
    FastX(
            const std::vector <std::string> errors,
            const std::string &entete = "",
            const std::string &seqbio = ""
    );

    std::string getSeqbio();

    std::string getHeader();

    void setHeader(std::string header);

    size_t getSeqbioLength();

    std::string getSeqComp();

    std::string getSeqRev();

    std::string getSeqRevComp();

    bool hasErrors() const;

    int countErrors() const;

    std::vector <std::string> getErrors() const;
};

#endif