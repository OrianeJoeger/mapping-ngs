#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifndef __SEQ_H__
#define __SEQ_H__

// se renseigner sur cassert 

class Seq {
protected:
    std::string entete;
    std::string seqbio;

    std::vector <std::string> errors;
public:
    Seq(
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