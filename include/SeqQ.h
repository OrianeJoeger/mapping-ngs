#ifndef __SeqA_Q__
#define __SeqA_Q__

#include "Seq.h"
#include <string>

class SeqQ : public Seq {
private:
    std::string qualite;
public:
    SeqQ(
            const std::vector <std::string> errors,
            const std::string &entete = "",
            const std::string &seqbio = "",
            const std::string &qualite = ""
    );

    std::string getQualite();

    virtual std::string toString(bool display_comp, bool display_rev);
};

#endif
