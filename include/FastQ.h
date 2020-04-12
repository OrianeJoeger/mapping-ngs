#ifndef __FASTA_Q__
#define __FASTA_Q__

#include "FastX.h"
#include <string>

class FastQ : public FastX {
private:
    std::string qualite;
public:
    FastQ(
            const std::vector <std::string> errors,
            const std::string &entete = "",
            const std::string &seqbio = "",
            const std::string &qualite = ""
    );

    std::string getQualite();
};

#endif
