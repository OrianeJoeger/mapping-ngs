#ifndef __SeqA_Q__
#define __SeqA_Q__

#include <string>

#include "Seq.h"
#include "EncodedSequence.h"

class SeqQ : public Seq {
private:
    /**
     * Qualite de la sequence
     *
     * @property
     */
    std::string qualite;
public:
    SeqQ(
            const std::string &entete,
            const EncodedSequence &seq,
            const std::string &qualite = ""
    );

    SeqQ(
            const std::string &entete = "",
            const std::string &seqbio = "",
            const std::string &qualite = ""
    );

    /**
     * Retourne la qualite de la sequence
     *
     * @property
     */
    std::string getQualite();

    /**
     * Surchage de la methode toString(bool, bool) de la classe mere
     * Retourne la sequence au format string avec l'entete et la qualité
     *
     * @property
     */
    virtual std::string toString(bool display_comp, bool display_rev);
};

#endif
