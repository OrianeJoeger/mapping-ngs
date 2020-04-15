#ifndef __SEQ_H__
#define __SEQ_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "EncodedSequence.h"
// se renseigner sur cassert 

class Seq {
protected:
    std::string entete;
    std::vector <std::string> errors;
    EncodedSequence seq;
public:
    Seq(
            const std::string &entete,
            const EncodedSequence &seq
    );

    Seq(
            const std::string &entete = "",
            const std::string &seqbio = ""
    );

    std::string getSeqbio();

    std::string getHeader();

    size_t getSeqbioLength();

    std::string getSeqComp();

    std::string getSeqRev();

    std::string getSeqRevComp();

    bool hasErrors() const;

    int countErrors() const;

    std::vector <std::string> *getErrors();

    virtual std::string toString(bool display_comp, bool display_rev);

    virtual std::string toString();
};

#endif