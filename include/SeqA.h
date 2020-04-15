#ifndef __SEQA_H__
#define __SEQA_H__

#include "Seq.h"
#include <string>


class SeqA : public Seq {
public:
    SeqA(
            const std::string &entete,
            const EncodedSequence &seq
    );
    SeqA(
            const std::string &entete = "",
            const std::string &seqbio = ""
    );
};

#endif