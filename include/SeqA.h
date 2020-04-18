#ifndef __SEQA_H__
#define __SEQA_H__

#include <string>

#include "Seq.h"
#include "EncodedSequence.h"

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